//
// Created by akaring on 24-4-11.
//

#include "Canvas.h"

#include <iostream>

#include <imgui/imgui_impl_glfw.h>
#include <imgui/imgui_impl_opengl3.h>
#include <glad/glad.h>

Canvas::Canvas(int width, int height)
{
    SCR_WIDTH = width;
    SCR_HEIGHT = height;
    // set camera
    camera = std::make_shared<Camera>();
    camera->set_perspective(glm::radians(60.0f), (float) width / (float) height, 0.01f, 100.0f);

    // init GLFW, create window
    glfwInit();
    window = glfwCreateWindow(width, height, "BanaRender", nullptr, nullptr);
    if (!window) {
        glfwTerminate();
    }

    glfwSetWindowUserPointer(window, this);

    // register GLFW callbacks
    glfwSetWindowSizeCallback(window, window_size_event);
    glfwSetKeyCallback(window, key_event);
    glfwSetMouseButtonCallback(window, mouse_button_event);
    glfwSetCursorPosCallback(window, cursor_event);
    glfwSetScrollCallback(window, scroll_event);

    // intialize OpenGL environment
    glfwMakeContextCurrent(window);

    // glad: load all OpenGL function pointers
    // ---------------------------------------
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "Failed to initialize GLAD" << std::endl;
    }

    // init ImGui
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO &io = ImGui::GetIO();
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard; // Enable Keyboard Controls
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad; // Enable Gamepad Controls

    // Setup Platform/Renderer backends
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    // Second param install_callback=true will install GLFW callbacks and chain to existing ones.
    ImGui_ImplOpenGL3_Init();
}

Canvas::~Canvas()
{
    // shut down
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    glfwDestroyWindow(window);
    glfwTerminate();
}

void Canvas::draw_ui()
{
    // Start the Dear ImGui frame
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    // Render Side Bar
    draw_side_bar();
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

    glfwSwapBuffers(window);
    glfwPollEvents();
}

void Canvas::draw_side_bar()
{
    ImGui::Begin("Side Bar",
                 nullptr,
                 ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize
                     | ImGuiWindowFlags_AlwaysAutoResize);

    // fps
    ImGui::Separator();
    ImGui::Text("fps: %.1f (%.2f ms/frame)", ImGui::GetIO().Framerate, 1000.0f / ImGui::GetIO().Framerate);

    // clear Color
    ImGui::Separator();
    ImGui::Text("clear color");
    ImGui::ColorEdit4("clear color", (float *) &this->clear_color, ImGuiColorEditFlags_NoLabel);

    // reset camera
    ImGui::Separator();
    ImGui::Text("camera:");
    ImGui::SameLine();
    if (ImGui::Button("reset")) {
        camera->reset_camera();
    }

    ImGui::SetWindowPos(ImVec2(SCR_WIDTH - ImGui::GetWindowWidth(), 0));
    ImGui::End();
}

glm::dvec2 Canvas::cursor_pos() const
{
    glm::dvec2 pos;
    glfwGetCursorPos(window, &pos.x, &pos.y);
    return pos;
}

glm::vec3 Canvas::trackball_to_sphere(const glm::vec2 &p,   // click point (screen coordinates)
                                      const double width,   // window width
                                      const double height,  // window height
                                      const double radius)  // trackball radius
{
    // normalized display coordinates
    double x_val =  (2.0*p.x - width )/width;
    double y_val = -(2.0*p.y - height)/height;
    double norm2 = x_val*x_val + y_val*y_val;
    return {x_val, y_val, (norm2 < 0.5*radius) ? sqrt(radius - norm2) : 0.5*radius/sqrt(norm2)};
}

void Canvas::trackball_to_rotations(const glm::vec3 &p0,    // input sphere point #1
                                    const glm::vec3 &p1,    // input sphere point #2
                                    glm::vec3 &axis,        // output rotation axis
                                    double &angle,          // output rotation angle (degrees)
                                    const double radius)    // trackball radius
{
    axis = cross(p0, p1);
    if (glm::length(axis) < 1e-7) axis = glm::vec3(1, 0, 0);
    axis = normalize(axis);
    double t = distance(p0, p1) * 0.5 / radius;
    t = glm::clamp(t, -1.0, 1.0);
    angle = 2.0 * asin(t);
    angle = glm::degrees(angle);
}

void Canvas::window_size_event(GLFWwindow *w, int width, int height)
{
}

void Canvas::key_event(GLFWwindow *w, int key, int unused, int action, int modif)
{
}

void Canvas::mouse_button_event(GLFWwindow *w, int butt, int action, int modif)
{

    Canvas *v = static_cast<Canvas *>(glfwGetWindowUserPointer(w));

    if (action == GLFW_RELEASE) {
        v->trackball.mouse_pressed = false;
    } else {
        assert(action == GLFW_PRESS);

        glm::dvec2 click = v->cursor_pos();

        if(butt==GLFW_MOUSE_BUTTON_LEFT)
        {
            v->trackball.mouse_pressed = true;
            v->trackball.last_click_2d = click;
            v->trackball.last_click_3d = v->trackball_to_sphere(click, v->SCR_WIDTH, v->SCR_HEIGHT);
        }
    }
}

void Canvas::cursor_event(GLFWwindow *w, double x_pos, double y_pos)
{
    auto *v = static_cast<Canvas *>(glfwGetWindowUserPointer(w));

    // mouse move + left click => rotate
    if(glfwGetMouseButton(w,GLFW_MOUSE_BUTTON_LEFT)==GLFW_PRESS)
    {
        glm::vec2 click_2d(x_pos, y_pos);
        glm::vec3 click_3d = v->trackball_to_sphere(click_2d, v->SCR_WIDTH, v->SCR_HEIGHT);
        if(v->trackball.mouse_pressed)
        {
            glm::vec3  axis;
            double angle;
            v->trackball_to_rotations(v->trackball.last_click_3d, click_3d, axis, angle);
            v->camera->rotate(angle,axis);
        }
        v->trackball.last_click_2d = click_2d;
        v->trackball.last_click_3d = click_3d;
    }
    // mouse move + right click => translate
    else if(glfwGetMouseButton(w,GLFW_MOUSE_BUTTON_RIGHT)==GLFW_PRESS) {
        glm::vec2 click_2d(x_pos, y_pos);
        if (v->trackball.last_click_2d != glm::vec2(FLT_MAX)) {
            glm::vec2 delta = (v->trackball.last_click_2d - click_2d);
            delta = normalize(delta);
            delta *= v->camera->get_radius() * 0.01;
            v->camera->translate(glm::vec3(-delta.x, delta.y, 0));
        }
        v->trackball.last_click_2d = click_2d;
    }
}

void Canvas::scroll_event(GLFWwindow *w, double x_off, double y_off)
{
    auto *v = static_cast<Canvas *>(glfwGetWindowUserPointer(w));

    v->camera->zoom(y_off);

}

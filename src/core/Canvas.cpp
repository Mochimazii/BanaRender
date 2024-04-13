//
// Created by akaring on 24-4-11.
//

#include "Canvas.h"

#include <iostream>

#include <imgui/imgui_impl_glfw.h>
#include <imgui/imgui_impl_opengl3.h>
#include <glad/glad.h>

Canvas::Canvas(int width, int height) {
    SCR_WIDTH = width;
    SCR_HEIGHT = height;
    // set camera


    // init GLFW, create window
    glfwInit();
    window = glfwCreateWindow(width, height, "BanaRender", NULL, NULL);
    if (!window) {
        glfwTerminate();
    }

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

Canvas::~Canvas() {
    // shut down
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    glfwDestroyWindow(window);
    glfwTerminate();
}

void Canvas::draw_ui() {
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

void Canvas::draw_side_bar() {
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

    ImGui::SetWindowPos(ImVec2(SCR_WIDTH - ImGui::GetWindowWidth(), 0));
    ImGui::End();
}

int Canvas::launch() {
    while (!glfwWindowShouldClose(window)) {
        draw_ui();

        glfwPollEvents();
    }
    return EXIT_SUCCESS;
}

void Canvas::window_size_event(GLFWwindow *w, int width, int height) {
}

void Canvas::key_event(GLFWwindow *w, int key, int unused, int action, int modif) {
}

void Canvas::mouse_button_event(GLFWwindow *w, int butt, int action, int modif) {
}

void Canvas::cursor_event(GLFWwindow *w, double x_pos, double y_pos) {
}

void Canvas::scroll_event(GLFWwindow *w, double x_off, double y_off) {
}

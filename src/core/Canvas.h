//
// Created by akaring on 24-4-11.
//

#ifndef CANVAS_H
#define CANVAS_H
#include <memory>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "camera.h"

struct Trackball
{
    glm::vec2 last_click_2d = glm::vec2(FLT_MAX);
    glm::vec3 last_click_3d = glm::vec3(FLT_MAX);
    bool  mouse_pressed = false;
};

class Canvas {
public:
    GLFWwindow *window;
    unsigned int SCR_WIDTH;
    unsigned int SCR_HEIGHT;

    glm::vec4 clear_color = {0.f, 0.f, 0.f, 0.f};


    //::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::

    std::shared_ptr<Camera> camera;
    Trackball               trackball;

    //::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::

    explicit Canvas(int width = 1000, int height = 800);
    ~Canvas();

    //::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::

    void draw_ui();
    void draw_side_bar();

    //::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::

    glm::dvec2 cursor_pos() const;

    //::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::

    glm::vec3 trackball_to_sphere(const glm::vec2 &p, const double width, const double height, const double radius = 0.5);
    void trackball_to_rotations(const glm::vec3 &p0, const glm::vec3 &p1, glm::vec3  &axis, double &angle, const double radius = 0.5);

    //::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::

    // internal event handlers
    static void window_size_event (GLFWwindow *w, int    width, int    height);
    static void key_event         (GLFWwindow *w, int    key,   int    unused, int action, int modif);
    static void mouse_button_event(GLFWwindow *w, int    butt,  int    action, int modif);
    static void cursor_event      (GLFWwindow *w, double x_pos, double y_pos);
    static void scroll_event      (GLFWwindow *w, double x_off, double y_off);

};



#endif //CANVAS_H

//
// Created by akaring on 24-4-11.
//

#ifndef CANVAS_H
#define CANVAS_H
#include <memory>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "camera.h"

class Canvas {
public:
    GLFWwindow *window;
    unsigned int SCR_WIDTH;
    unsigned int SCR_HEIGHT;
    std::shared_ptr<Camera> camera;
    glm::vec4 clear_color = {0.f, 0.f, 0.f, 0.f};

    //::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::

    explicit Canvas(int width = 1000, int height = 800);
    ~Canvas();

    //::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::

    void draw_ui();
    void draw_side_bar();

    //::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::

    int launch();

    //::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::

    // internal event handlers
    static void window_size_event (GLFWwindow *w, int    width, int    height);
    static void key_event         (GLFWwindow *w, int    key,   int    unused, int action, int modif);
    static void mouse_button_event(GLFWwindow *w, int    butt,  int    action, int modif);
    static void cursor_event      (GLFWwindow *w, double x_pos, double y_pos);
    static void scroll_event      (GLFWwindow *w, double x_off, double y_off);

};



#endif //CANVAS_H

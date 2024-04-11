//
// Created by akaring on 24-4-11.
//

#ifndef CANVAS_H
#define CANVAS_H
#include <camera.h>
#include <memory>
#include <GLFW/glfw3.h>

class Canvas {
public:
    GLFWwindow *window;
    std::shared_ptr<Camera> camera;
    glm::vec4 clear_color = {0.f, 0.f, 0.f, 0.f};

    //::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::

    Canvas(int width, int height);
    ~Canvas();

    //::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::

    int launch();

    //::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::

    void draw();
    void draw_side_bar();

    //::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::

    // internal event handlers
    static void window_size_event (GLFWwindow *w, int    width, int    height);
    static void key_event         (GLFWwindow *w, int    key,   int    unused, int action, int modif);
    static void mouse_button_event(GLFWwindow *w, int    butt,  int    action, int modif);
    static void cursor_event      (GLFWwindow *w, double x_pos, double y_pos);
    static void scroll_event      (GLFWwindow *w, double x_off, double y_off);

};



#endif //CANVAS_H

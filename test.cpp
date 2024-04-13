#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/gtc/type_ptr.hpp>
#include <cinolib/gl/glcanvas.h>

#include "core/Canvas.h"


int main()
{
    Canvas canvas;

    while (!glfwWindowShouldClose(canvas.window))
    {
        glClearColor(canvas.clear_color[0], canvas.clear_color[1], canvas.clear_color[2], canvas.clear_color[3]);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glEnable(GL_DEPTH_TEST);

        canvas.draw_ui();
    }

    return 0;
}


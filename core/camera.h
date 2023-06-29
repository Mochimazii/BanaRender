//
// Created by akaring on 2023/6/28.
//

#ifndef BANARENDER_CAMERA_H
#define BANARENDER_CAMERA_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Camera {
public:
    glm::vec3 eye;
    glm::vec3 target;
    glm::vec3 upVec;

    Camera(glm::vec3 eye,
           glm::vec3 target = glm::vec3(0, 0, 0),
           glm::vec3 upVec = glm::vec3(0, 1, 0)):eye(eye),target(target),upVec(upVec){}

    glm::vec3 get_arcball_vector(double x, double y);
};


#endif //BANARENDER_CAMERA_H

//
// Created by akaring on 2023/6/28.
//

#include <iostream>
#include "glm/gtx/string_cast.hpp"
#include "camera.h"

glm::mat4 Camera::get_view_matrix() {

    return glm::lookAt(eye, target, upVec);
}

void Camera::restricted_rotate(float x_offset, float y_offset) {
    glm::vec3 from_target = eye - target;
    float radius = glm::length(from_target);

    float phi = atan2(from_target[0], from_target[2]);
    float theta = acos(from_target[1] / radius);

    float factor = 1.5 * M_PI;
    // for mouse left button
    phi	  += x_offset * factor;
    theta += y_offset * factor;
    if (theta > M_PI) theta = M_PI - EPSILON * 100;
    if (theta < 0)  theta = EPSILON * 100;

    this->eye[0] = this->target[0] + radius * sin(phi) * sin(theta);
    this->eye[1] = this->target[1] + radius * cos(theta);
    this->eye[2] = this->target[2] + radius * sin(theta) * cos(phi);

    updateCameraAttr();
}

void Camera::arcball_rotate(glm::vec3 va, glm::vec3 vb) {
    float angle = acos(fmin(1.0f, glm::dot(va, vb)));
    glm::vec3 axis_in_camera_coord = glm::normalize(glm::cross(va, vb));
    glm::vec3 axis_in_world_coord = glm::inverse(glm::mat3(get_view_matrix())) * axis_in_camera_coord;

    glm::quat rotatoMat = glm::quat(cos(angle/2),
                          axis_in_world_coord.x * sin(angle/2),
                          axis_in_world_coord.y * sin(angle/2),
                          axis_in_world_coord.z * sin(angle/2));

    this->eye = rotatoMat * this->eye;
    this->upVec = rotatoMat * this->upVec;
}

void Camera::updateCameraAttr() {
    glm::vec3 refUp(0.0f, 1.0f, 0.0f);
    glm::vec3 front = glm::normalize(this->target - this->eye);
    if (fabs(front.x) < EPSILON && fabs(front.z) < EPSILON){
        if (front.y > 0) refUp = {0, 0, 1};
        else refUp = {0, 0, -1};
    }
    glm::vec3 right = glm::normalize(glm::cross(front, refUp));
    this->upVec = glm::normalize(glm::cross(right, front));
}








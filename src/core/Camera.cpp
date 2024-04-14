//
// Created by akaring on 2023/6/28.
//

#include <iostream>
#include <glm/gtx/quaternion.hpp>
#include "camera.h"

Camera::Camera() {
    reset_camera();
}

void Camera::reset_camera()
{
    eye_ = init_eye_;
    center_ = init_center_;
    up_ = init_up_;

    model_mat = glm::mat4(1.f);

    glm::vec3 dir = eye_ - center_;
    radius_ = glm::length(dir);
}

void Camera::set_perspective(float fov, float aspect, float near, float far)
{
    this->fov_ = fov;
    this->aspect_ = aspect;
    this->near_ = near;
    this->far_ = far;
}

void Camera::zoom(double delta)
{
    radius_ += delta * 0.2;
    radius_ = glm::clamp(radius_, 1., 1e3);

    auto eye_dir = glm::normalize(eye_ - center_);
    eye_ = center_ + eye_dir * (float)radius_;
}

void Camera::rotate(double deg, glm::vec3 axis)
{
    double half_rad = glm::radians(deg) / 2;
    glm::quat rotatoMat = glm::quat(cos(half_rad),
                          axis.x * sin(half_rad),
                          axis.y * sin(half_rad),
                          axis.z * sin(half_rad));
    // Ðý×ª eye ºÍ upVec
    model_mat = glm::toMat4(rotatoMat) * model_mat;
}

void Camera::translate(glm::vec3 delta)
{
    auto trans_mat = glm::translate(glm::mat4(1.f), delta);
    model_mat = trans_mat * model_mat;
}

glm::mat4 Camera::model_matrix() const
{
    return this->model_mat;
}

glm::mat4 Camera::view_matrix() const
{
    return glm::lookAt(eye_, center_, up_);
}

glm::mat4 Camera::projection_matrix() const
{
    return glm::perspective(fov_, aspect_, near_, far_);
}

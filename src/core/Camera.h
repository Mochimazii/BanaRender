//
// Created by akaring on 2023/6/28.
//

#ifndef BANARENDER_CAMERA_H
#define BANARENDER_CAMERA_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "macro.h"

static constexpr glm::vec3 init_eye_(-1.5, 3, 3);
static constexpr glm::vec3 init_center_(0, 0, 0);
static constexpr glm::vec3 init_up_(0, 1, 0);

class Camera {
public:
    Camera();
    void reset_camera();
    void set_perspective(float fov, float aspect, float near, float far);

    //::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::

    void zoom(double delta);
    void rotate(double deg, glm::vec3 axis);
    void translate(glm::vec3 delta);

    //::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::

    glm::mat4 model_matrix() const;
    glm::mat4 view_matrix() const;
    glm::mat4 projection_matrix() const;

    //::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::

    float get_fov() const {
        return fov_;
    }

    float get_aspect() const {
        return aspect_;
    }

    float get_near() const {
        return near_;
    }

    float get_far() const {
        return far_;
    }

    glm::vec3 get_eye() const {
        return eye_;
    }

    glm::vec3 get_center() const {
        return center_;
    }

    glm::vec3 get_up() const {
        return up_;
    }

    double get_radius() const {
        return radius_;
    }

private:
    float fov_{glm::radians(60.f)};
    float aspect_{1.0f};
    float near_{0.01f};
    float far_{100.f};

    glm::vec3 eye_{};
    glm::vec3 center_{};
    glm::vec3 up_{};

    double radius_{1.};

    glm::mat4 model_mat{glm::mat4(1.f)};

};


#endif //BANARENDER_CAMERA_H

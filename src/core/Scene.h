//
// Created by akaring on 24-4-11.
//

#ifndef SCENE_H
#define SCENE_H

#include <memory>
#include <vector>

class Model {
};

class Light {

};

class Scene {
public:
    std::shared_ptr<Model> model;
    std::shared_ptr<Light> light;
};



#endif //SCENE_H

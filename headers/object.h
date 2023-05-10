#include "../glm/glm.hpp"
#include "../glm/vec3.hpp"
#include "shared.h"

#pragma once

class Material;
//the class that all objects in the scene inherit from
class Object {
    public: 
        glm::vec3 position;
        Material* material;

        virtual RayHit intersect(Ray& in) = 0;
};
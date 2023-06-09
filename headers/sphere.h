#include "../glm/glm.hpp"
#include "../glm/vec3.hpp"
#include "shared.h"
#include "Object.h"

#pragma once

class Material;

class Sphere : public Object {
    public: 
        float radius;

        //default constructor - unit sphere at origin
        Sphere();
        //constructor that takes a position
        Sphere(glm::vec3 position);
        //full constructor takes a position and radius
        Sphere(glm::vec3 position, float radius, Material* material);
        //full constructor takes position floats and radius
        Sphere(float x, float y, float z, float radius, Material* material);

        //the ray-primitive intersection function for this sphere
        RayHit intersect(Ray& ray) override;
};

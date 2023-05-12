#include "../headers/sphere.h"
#include "../headers/lambertian.h"
#include <iostream>
//default constructor - unit sphere at origin
Sphere::Sphere() {
    position = glm::vec3(0.);
    radius = 1.;
    this->material = new Lambertian(glm::vec3(.5, .5, .5));
}
//constructor that takes a position
Sphere::Sphere(glm::vec3 position) {
    this->position = position;
    this->material = new Lambertian(glm::vec3(.5, .5, .5));
}
//full constructor takes a position and radius
Sphere::Sphere(glm::vec3 position, float radius, Material* material) {
    this->position = position; this->radius = radius;
    this->material = material;
}

//full constructor takes position floats and radius
Sphere::Sphere(float x, float y, float z, float radius, Material* material) {
    position = glm::vec3(x, y, z);
    this->position = position; this->radius = radius;
    this->material = material;
}

//ray-sphere intersection function
RayHit Sphere::intersect(Ray& ray) {
    RayHit returned; returned.bHit = false;
    returned.material = this->material;

    float t0, t1; 

    //find coefficients of quadratic equation
    glm::vec3 L = ray.origin - position;
    float a = glm::dot(ray.direction, ray.direction);
    float b = 2 * glm::dot(ray.direction, L);
    float c = glm::dot(L, L) - radius * radius;

    //solve quadratic equation
    float discr = b * b - 4 * a * c;
    if (discr < 0) {
        return returned;
    }
    else if (discr == 0) {
        t0 = -.5 * b / a;
        t1 = t0;
    } else {
        float q = (b > 0) ?
            -.5 * (b + sqrt(discr)) :
            -.5 * (b - sqrt(discr));
        
        t0 = q / a; t1 = c / q;
    }

    //ensure that first hit is closest hit
    if (t0 > t1) {
        float temp = t0; t0 = t1; t1 = temp;
    }

    //check if the sphere is behind us
    if (t0 < 0) {
        if (t1 < 0) {
            return returned;
        }
        returned.bHit = true;
        returned.hitNormal = glm::normalize((ray.origin + ray.direction * t1) - position);
        returned.distance = t1;
        return returned;
    }
    //else the sphere is in front of us
    returned.bHit = true;
    returned.hitNormal = glm::normalize((ray.origin + ray.direction * t0) - position);
    returned.distance = t0;
    return returned;
}
#include "../headers/lambertian.h"
#include "../headers/shared.h"
#include <iostream>

Lambertian::Lambertian(glm::vec3 color) {
    this->color = color;
}

//generates a random sample about a hemisphere
//https://pbr-book.org/3ed-2018/Monte_Carlo_Integration/2D_Sampling_with_Multidimensional_Transformations 
glm::vec3 uniformSampleHemisphere() {
    float r1 = frand1(); float r2 = frand1();
    float r = std::sqrt(std::max(0.f, 1.f - r1 * r1));
    float phi = 2 * PI * r2;
    return glm::vec3(r * std::cos(phi), r * std::sin(phi), r1);
}

void Lambertian::sample_f(glm::vec3 wo, glm::vec3& wi, float& pdf, glm::vec3& brdf) {
    wi = uniformSampleHemisphere();
    pdf = 1. / (2. * PI);
    brdf = color / PI;
}


/*
class Lambertian : Material {
    public: 
        glm::vec3 color;

        Lambertian(glm::vec3 color);

        void sample_f(
            glm::vec3 wo, glm::vec3& wi,
            float& pdf, glm::vec3& brdf
        );
};*/
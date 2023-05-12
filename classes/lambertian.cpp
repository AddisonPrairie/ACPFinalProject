#include "../headers/lambertian.h"
#include "../headers/shared.h"
#include "../glm/vec2.hpp"
#include <iostream>

Lambertian::Lambertian(){
    this->color = glm::vec3(0, 0, 0);
}

Lambertian::Lambertian(glm::vec3 color) {
    this->color = color;
}

void Lambertian::setColor(glm::vec3 color){
    this->color = color;
}

void Lambertian::setColor(float a, float b, float c){
    this->color = glm::vec3(a, b, c);
}

//generates a random sample about a hemisphere
//https://pbr-book.org/3ed-2018/Monte_Carlo_Integration/2D_Sampling_with_Multidimensional_Transformations 
glm::vec3 uniformSampleHemisphere() {
    float r1 = frand1(); float r2 = frand1();
    float r = std::sqrt(std::max(0.f, 1.f - r1 * r1));
    float phi = 2.f * PI * r2;
    return glm::vec3(r * std::cos(phi), r * std::sin(phi), r1);
}

//generates a random sample in a disc
//https://pbr-book.org/3ed-2018/Monte_Carlo_Integration/2D_Sampling_with_Multidimensional_Transformations#ConcentricSampleDisk
glm::vec2 sampleDisk() {
    float r1 = 2.f * frand1() - 1.f; float r2 = 2.f * frand1() - 1.f;
    if (r1 == 0.f && r2 == 0.f) return glm::vec2(0.);

    float theta, r;

    if (std::abs(r1) > std::abs(r2)) {
        r = r1; theta = (r2 / r1) * PI / 4.f;
    } else {
        r = r2; theta = PI / 2.f - (PI / 4.f) * (r1 / r2);
    }
    return r * glm::vec2(std::cos(theta), std::sin(theta));
}

//generates a random cosine weighted sample
//https://pbr-book.org/3ed-2018/Monte_Carlo_Integration/2D_Sampling_with_Multidimensional_Transformations#ConcentricSampleDisk
glm::vec3 cosineSampleHemisphere() {
    glm::vec2 r = sampleDisk();
    float z = std::sqrt(std::max(0.f, 1.f - r.x * r.x - r.y * r.y));
    return glm::vec3(r.x, r.y, z);
}

void Lambertian::sample_f(glm::vec3 wo, glm::vec3& wi, float& pdf, glm::vec3& brdf) {
    #if 1
    wi = cosineSampleHemisphere();
    pdf = std::max(fabs(wi.z / PI), .001f);
    #else
    wi = uniformSampleHemisphere();
    pdf = 1. / (2. * PI);
    #endif
    brdf = color / PI;
}

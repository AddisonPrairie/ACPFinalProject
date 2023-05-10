#include "../glm/glm.hpp"
#include "../glm/vec3.hpp"

#include "material.h"

#pragma once

class Emissive : public Material {
    public:
        glm::vec3 color;

        Emissive(glm::vec3 color) {
            this->color = color;
            this->bEmissive = true;
        }

        void sample_f(
            glm::vec3 wo, glm::vec3& wi,
            float& pdf, glm::vec3& brdf
        ) override {
            return;
        };
};
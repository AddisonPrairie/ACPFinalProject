#include "../glm/glm.hpp"
#include "../glm/vec3.hpp"

#pragma once

class Material {
    public:
        bool bEmissive = false;

        virtual void sample_f(
            glm::vec3 wo, glm::vec3& wi,
            float& pdf, glm::vec3& brdf
        ) = 0;
};
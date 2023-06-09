#include "../glm/glm.hpp"
#include "../glm/vec3.hpp"

#include "material.h"

class Lambertian : public Material {
    public: 
        glm::vec3 color;

        Lambertian();
        Lambertian(glm::vec3 color);

        void setColor(glm::vec3 color);
        void setColor(float a, float b, float c);

        void sample_f(
            glm::vec3 wo, glm::vec3& wi,
            float& pdf, glm::vec3& brdf
        );
};
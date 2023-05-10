#pragma once
#include "shared.h"
#include "../glm/glm.hpp"
#include "../glm/vec3.hpp"

class Camera {
    public:
        int screenX; int screenY; float aspectRatio;
        glm::vec3 position; glm::vec3 forward; glm::vec3 right; glm::vec3 up;
        glm::vec3 pinholeOrigin;

        //construct a camera
        Camera(int screenX, int screenY, float pinholeDistance, glm::vec3 position, glm::vec3 forward, glm::vec3 right);
        //gets the ray information for a given pixel
        Ray getRayForPixel(float pixelX, float pixelY);
        //function to print the information about this camera
        void printInfo();
        //static function to generate necessary vectors from two angles
        static void generateForwardAndRightFromAngles(
            float yaw, float pitch, glm::vec3& forward, glm::vec3& right
        );
};
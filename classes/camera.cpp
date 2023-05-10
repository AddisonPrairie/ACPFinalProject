#include "../headers/camera.h"
#include <cmath>
#include <stdio.h>

//construct a camera
Camera::Camera(int screenX, int screenY, float pinholeDistance, glm::vec3 position, glm::vec3 forward, glm::vec3 right) {
    this->screenX = screenX; this->screenY = screenY;
    this->position = position; this->forward = forward; this->right = right;
    this->up = glm::cross(right, forward);
    this->pinholeOrigin = (pinholeDistance) * forward;
    aspectRatio =  ((float) this->screenX) / ((float) this->screenY);
}
//gets the ray information for a given pixel
Ray Camera::getRayForPixel(int pixelX, int pixelY) {
    Ray returned;
    //find the rays position along the right and up vectors
    float xAmt = ((float) pixelX) / ((float) screenX) - .5;
    xAmt *= aspectRatio;
    float yAmt =  .5 - ((float) pixelY) / ((float) screenY);
    glm::vec3 target = position + xAmt * right + yAmt * up + pinholeOrigin;
    //find the rays direction
    returned.direction = glm::normalize(target - this->position);
    returned.origin = this->position;
    return returned;
}

//static function to generate necessary vectors from two angles
void Camera::generateForwardAndRightFromAngles(
    float yaw, float pitch, glm::vec3& forward, glm::vec3& right
) {
    forward.x = cos(yaw) * cos(pitch);
    forward.y = sin(yaw) * cos(pitch);
    forward.z = sin(pitch);

    right.x = sin(yaw);
    right.y = -cos(yaw);
    right.z = 0;
}

//prints all the information about the camera for debug purposes
void Camera::printInfo() {
    printf("---Debugging camera---\n");
    printf("position: %f %f %f\n", position.x, position.y, position.z);
    printf("forward: %f %f %f\n", forward.x, forward.y, forward.z);
    printf("right: %f %f %f\n", right.x, right.y, right.z);
    printf("up: %f %f %f\n", up.x, up.y, up.z);
}
//defines structures that are shared among all of the files
#pragma once
#include "../glm/glm.hpp"
#include "../glm/vec3.hpp"
#include <cstdlib>


#define PI 3.14159265358979323846f

inline float fabs(float x) {return x < 0 ? -x : x;}
inline float fclamp(float a, float min, float max) {
    if (a < min) return min;
    if (a > max) return max;
    return a;
};
inline float frand1() {return (float) (rand()) / (float) (RAND_MAX);};

struct Ray {
    glm::vec3 origin;
    glm::vec3 direction;
};

//for ray-object intersection
class Material;
struct RayHit {
    float distance;
    bool bHit;
    glm::vec3 hitNormal;
    Material* material;
};
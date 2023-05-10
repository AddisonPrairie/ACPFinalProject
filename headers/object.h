#include "../glm/glm.hpp"
#include "../glm/vec3.hpp"
#include "shared.h"

//the class that all objects in the scene inherit from
class Object {
    public: 
        glm::vec3 position;
    
        virtual RayHit intersect(Ray& in) = 0;
};
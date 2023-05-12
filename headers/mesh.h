#include "../glm/glm.hpp"
#include "../glm/vec3.hpp"
#include "object.h"

struct RayHit; struct Ray;
class Material;
class Mesh : public Object {
    public: 
        float* triangles; int numTriangles;
        //full constructor takes a position and radius
        Mesh(glm::vec3 position, float* triangles, int numTriangles, Material* material);

        //the ray-primitive intersection function for this sphere
        RayHit intersect(Ray& ray) override;
};
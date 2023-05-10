#include "../headers/mesh.h"

Mesh::Mesh(glm::vec3 position, float* triangles, int numTriangles, Material* material) {
    this->position = position;
    this->triangles = triangles; 
    this->numTriangles = numTriangles;
    this->material = material;
}


RayHit Mesh::intersect(Ray& ray) {
    float closestDistance; int bFound = false;
    glm::vec3 hitNormal;
    for (int i = 0; i < numTriangles; i++) {
        glm::vec3 v0 = glm::vec3(
            this->triangles[9 * i + 0],
            this->triangles[9 * i + 1],
            this->triangles[9 * i + 2]
        );
        glm::vec3 v1 = glm::vec3(
            this->triangles[9 * i + 3],
            this->triangles[9 * i + 4],
            this->triangles[9 * i + 5]
        );
        glm::vec3 v2 = glm::vec3(
            this->triangles[9 * i + 6],
            this->triangles[9 * i + 7],
            this->triangles[9 * i + 8]
        );

        glm::vec3 e1, e2, h, s, q;
        float a, f, u, v;

        e1 = v1 - v0; e2 = v2 - v0;
        h = glm::cross(ray.direction, e2);
        a = glm::dot(e1, h);

        if (a > -.0000001 && a < .0000001) continue;

        f = 1. / a;
        s = ray.origin - v0;
        u = f * glm::dot(s, h);

        if (u < 0. || u > 1.) continue;

        q = glm::cross(s, e1);
        v = f * glm::dot(ray.direction, q);

        if (v < 0. || u + v > 1.) continue;

        float t = f * glm::dot(e2, q);

        if (t > .00000001) {
            if (!bFound || t < closestDistance) {
                bFound = true;
                closestDistance = t;
                hitNormal = glm::normalize(glm::cross(e1, e2));
                if (glm::dot(ray.direction, hitNormal) > 0.) {
                    hitNormal *= -1.f;
                }
            }
        } else {
            continue;
        }
    }

    RayHit returned;
    returned.bHit = bFound;
    returned.distance = closestDistance;
    returned.material = this->material;
    returned.hitNormal = hitNormal;
    return returned;
};
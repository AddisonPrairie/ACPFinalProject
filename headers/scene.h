#include "shared.h"

class Object;
//linked list node for objects in the scene
struct Node {
    struct Node* next; Object* object;
};

//the class that stores information about the objects in the scene
class Scene {
    public:
        //linked list for the objects in the scene
        Node* rootNode = nullptr;

        //default constructor
        Scene();
        //adds an object to the scene
        void addObjectToScene(Object* object);
        //intersects a ray with the entire scene
        RayHit intersect(Ray& in);
        //cleans up objects
        ~Scene();
};
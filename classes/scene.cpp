#include "../headers/scene.h"
#include "../headers/object.h"

#include <iostream>

//the default constructor
Scene::Scene() {
    rootNode = nullptr;
}

//adds an object to the scene
void Scene::addObjectToScene(Object* object) {
    Node* newNode = new Node;
    newNode->object = object;
    newNode->next = nullptr;

    if (rootNode == nullptr) {
        rootNode = newNode;
    } else {
        Node* cur = rootNode;
        while (cur->next != nullptr) {cur = cur->next;}
        cur->next = newNode;
    }
}

//intersects a ray with the entire scene
RayHit Scene::intersect(Ray& in) {
    Node* cur = rootNode;
    //if there are no objects in the scene
    if (cur == nullptr) {
        RayHit returned; returned.bHit = false;
        return returned;
    }

    RayHit returned; returned.bHit = false;
    int numVisits = 0;
    while (cur != nullptr) {
        Object* currentObject = cur->object;
        if (currentObject) {
            RayHit newHit = currentObject->intersect(in);
            if (newHit.bHit && (!returned.bHit || newHit.distance < returned.distance)) {
                returned = newHit;
            }
        }
        cur = cur->next;
    }

    return returned;
}
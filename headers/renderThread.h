

class Camera; class TileQueue; class Scene;
//the function that a thread will execute
void threadFunc(
    unsigned char* pixels,
    int screenWidth, int screenHeight,
    Camera* camera,
    Scene* scene,
    TileQueue* tileQueue
);
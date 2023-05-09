#include "tile.h"
#include <thread>
#include <mutex>

struct QNode {
    struct QNode* next;
    Tile* tile;
};

//creates and edits a queue that allows the renderer to split work into tiles across threads
class TileQueue {
    public:
        QNode* root;
        std::mutex queueLock;
        //default constructor
        TileQueue(int tileX, int tileY, int screenX, int screenY);
        //gets the next available tile
        Tile* pop();
};
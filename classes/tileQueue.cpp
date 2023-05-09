#include "../headers/tileQueue.h"
#include <iostream>

//constructor
TileQueue::TileQueue(int tileX, int tileY, int screenX, int screenY) {
    root = nullptr; QNode* last = nullptr;
    for (int x = 0; x < screenX; x += tileX) {
        for (int y = 0; y < screenY; y += tileY) {
            Tile* newTile = new Tile;
            newTile->xLow = x; newTile->yHigh;
            newTile->xHigh = x + tileX > screenX ? screenX : x + tileX;
            newTile->yHigh = y + tileY > screenY ? screenY : y + tileY;
            if (root == nullptr) {
                root = new QNode; root->tile = newTile; root->next = nullptr;
                last = root;
            } else {
                last->next = new QNode;
                last = last->next; last->tile = newTile;
                last->next = nullptr;
            }
        }
    }
}

//gets the next available tile
Tile* TileQueue::pop() {
    if (root == nullptr) {
        return nullptr;
    }
    Tile* returned = root->tile;
    QNode* newRoot = root->next;
    delete root;
    root = newRoot;
    return returned;
}
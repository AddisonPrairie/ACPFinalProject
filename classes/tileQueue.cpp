#include "../headers/tileQueue.h"
#include <iostream>

//constructor
TileQueue::TileQueue(int tileX, int tileY, int screenX, int screenY) {
    root = nullptr; QNode* last = nullptr; numTiles = 0;
    for (int x = 0; x < screenX; x += tileX) {
        for (int y = 0; y < screenY; y += tileY) {
            numTiles++;
            Tile* newTile = new Tile;
            newTile->xLow = x; newTile->yLow = y;
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
    std::cout << "total tiles: " << numTiles << std::endl;
}

//gets the next available tile
Tile* TileQueue::pop() {
    if (root == nullptr) {
        return nullptr;
    }
    numTiles--; std::cout << numTiles << "tiles remaining" << std::endl;
    Tile* returned = root->tile;
    QNode* newRoot = root->next;
    delete root;
    root = newRoot;
    return returned;
}
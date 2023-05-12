#ifndef HashTable_h
#define HashTable_h
#include "material.h"
#include <string>
#include <iostream>

class HashTable
{
private:
    //Array of Materials
    Material ** array;
    
    // Length is the size of the Hash Table array.
    int length;
    
    // Calculates a hash for the given key.
    int hFunc(std::string Key);
    
public:
    
    // Constructs the empty Hash Table object.
    // Array length is set to 16 by default.
    HashTable(int tableLength = 16);
    
    // Adds a material to the Hash Table.
    void insert(Material* mat, std::string name);
    
    // Deletes a material by key from the Hash Table.
    void erase(std::string Key);
    
    // Returns a material from the Hash Table by key.
    Material* get(std::string Key);
    
    // Returns the number of locations in the Hash Table.
    int getLength();
    
    // De-allocates all memory used for the Hash Table.
    ~HashTable();
};

#endif
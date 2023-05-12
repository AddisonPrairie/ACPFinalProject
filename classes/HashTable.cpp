#include "../headers/HashTable.h"

// Constructs the empty Hash Table object.
// Array length is set to 16 by default.
HashTable::HashTable(int tableLength = 16)
{
    if (tableLength <= 0) tableLength = 16;
    array = new Material*[tableLength];
    length = tableLength;
}

// Returns an array location for a given material key.
int HashTable::hFunc(std::string Key)
{
    int value = 0;
    for (int i = 0; i < Key.length(); i++)
        value += Key[i];
    return (value * Key.length() ) % length;
}

// Adds a material to the Hash Table.
void HashTable::insert(Material* mat, std::string name)
{
  int ind = hFunc(name);
  array[ind] = mat;
}

// Deletes a material by key from the Hash Table.
void HashTable::erase(std::string Key)
{
  int ind = hFunc(Key);
  delete(array[ind]);
  array[ind] = nullptr;
}

// Returns a material from the Hash Table by key.
Material* HashTable::get(std::string Key)
{
  int ind = hFunc(Key);
  return(array[ind]);
}

// Returns the number of locations in the Hash Table.
int HashTable::getLength()
{
    return length;
}

// De-allocates all memory used for the Hash Table.
HashTable::~HashTable()
{
    for(int i = 0; i < length; i++){
        delete(array[i]);
    }
    delete[] array;
}

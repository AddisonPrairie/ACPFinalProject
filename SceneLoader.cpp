#include "headers/sceneLoader.h"
#include "headers/lambertian.h"
#include "headers/HashTable.h"
#include "headers/sphere.h"

//Function to load scene from scenefile
//Returns a pointer to a scene that will need to be deallocated
Scene* load(std::string filename){
    //input filestream object
    std::ifstream infile;
    //Open specified file
    infile.open (filename, std::ifstream::in);
    //If file opens successfully:
    if (infile.is_open())
    {
        //Create new scene object
        Scene* newScene = new Scene();
        //Create temp string
        std::string temp;
        //Create material table
        HashTable* materials = new HashTable();
        //RGB strings
        std::string r, g, b;
        //Name string
        std::string name;
        //Vector strings
        std::string x, y, z;
        //Radius string
        std::string rad;
        //Material string
        std::string matStr;
        //Material pointer
        Material* curMat;
        //While still lines
        while (infile.good())
        {
            //Read in line
            getline(infile, temp);
            //If item is lambertian
            if(temp == "lambertian"){
                //Make lambertian material
                Lambertian* newL = new Lambertian();
                //Add to materials table
                getline(infile, name);
                materials->insert(newL, name);
                //Set color
                getline(infile, r);
                getline(infile, g);
                getline(infile, b);
                newL->setColor(std::stof(r), std::stof(g), std::stof(b));
            }
            if(temp == "sphere"){
                //Get position
                getline(infile, x);
                getline(infile, y);
                getline(infile, z);
                //Get radius
                getline(infile, rad);
                //Get material
                getline(infile, matStr);
                curMat = materials->get(matStr);
                //Make sphere object
                Sphere* newSphere = new Sphere();
                //Add sphere to scene
                newScene->addObjectToScene(newSphere);
            }
        }
        //Close file
        infile.close();
    }
    //File does not open successfully
    else
    {
        std::cout << "Error opening file";
    }
}
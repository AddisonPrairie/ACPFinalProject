#include "headers/sceneLoader.h"

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
        //Scene* newScene = new Scene();
        //Create temp string
        std::string temp;
        while (infile.good())
        {
            //Read in line
            getline(infile, temp);
            //infile.getline(curAirport->code, 256, ',');
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
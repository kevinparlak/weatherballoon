#include <iostream>
#include <fstream>
//Raspicam libraries
#include <raspicam/raspicam.h>
#include <raspicam/raspicamtypes.h>
//Camera header file
#include "camera.h"

using namespace std;

//Constructor
CAMERA::CAMERA()
{

};

CAMERA::CAMERA(const char* path)
{
    //Call Raspicam directory classes
    raspicam::RaspiCam Camera;
    //Error if camera cannot open
    if(!Camera.open())
        cout<<"Error opening camera"<<endl;
    //Grab image
    Camera.grab();
    //Allocate space for picture
    unsigned char *data=new unsigned char [Camera.getImageTypeSize(raspicam::RASPICAM_FORMAT_RGB)];
    //Retrieve data
    Camera.retrieve(data,raspicam::RASPICAM_FORMAT_RGB);
    //Output to a file path
    ofstream outFile(path,ios::binary);
    outFile<<"P6\n"<<Camera.getWidth()<<" "<<Camera.getHeight()<<" 255\n";
    outFile.write((char*) data, Camera.getImageTypeSize(raspicam::RASPICAM_FORMAT_RGB));
    //Destroy pointer
    delete data;
};

//Destructor
CAMERA::~CAMERA()
{
    
};
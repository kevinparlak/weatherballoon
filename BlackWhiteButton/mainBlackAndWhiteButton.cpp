#include <iostream>
#include <string>
#include <vector>
#include <iterator>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <cstdio>
#include <ctime>

//Servos
#include "servo.h"
#include <fcntl.h>

using namespace std;

int main()
{
    //Open Pololu Micro Maestro 6-channel USB controller
        const char * device = "/dev/ttyACM0";  // Linux
        int fd = open(device, O_RDWR | O_NOCTTY);
        if (fd == -1)
        {
                perror(device);
                return 1; 
        }
	//Call servo class with channel from Maestro
        SERVO servo(fd);
	//Set max position for servo2000
	servo.maestroSetTarget(fd,5,30000);
        sleep(1);
        //Shut off servo
        servo.maestroSetTarget(fd,5,0);

//--------------------------------------------------------------------------
//Black and White Ribbon Redundancy Measure Initiated
cout<<"Black and White Redunancy Initiated..."<<endl;

	return 0;
}
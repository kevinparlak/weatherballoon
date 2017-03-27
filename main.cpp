#include <iostream>
#include <string>
#include <vector>
#include <iterator>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <cstdio>
#include <ctime>

//GPS
#include "gps.h"

//Camera
#include <raspicam/raspicam.h>
#include <raspicam/raspicamtypes.h>

//Servos
#include "servo.h"
#include <fcntl.h>

//Temperature Sensor
#include <wiringPi/wiringPi.h>
#include "temp.h"
#include <stdint.h>

//Pressure Sensor
#include "pressure.h"

//Output
#include <fstream>

using namespace std;

int main()
{
    //----------System checks----------
        //*****TIMER*****
        //Start timer
        clock_t startTimer=clock();
    
        //*****GPS*****
        //Set baud rate for GPS
        system("stty -F /dev/ttyUSB0 4800");
        //Input NMEA line for GPS class
        string nmea;
        fstream f;
        //Open GPS USB device
        f.open("/dev/ttyUSB0");

        //*****SERVOS*****
        //Open Pololu Micro Maestro 6-channel USB controller
        const char * device = "/dev/ttyACM0";  // Linux
        int fd = open(device, O_RDWR | O_NOCTTY);
        if (fd == -1)
        {
            perror(device);
            return 1; 
        }
        
        //*****PICTURE*****
        int count=0;
        
        //*****OUTPUT FILE*****
        ofstream balloondata;
        balloondata.open("balloondata.txt");
        
        bool hotwire=false;
while(hotwire!=true)
{
    //----------Data Streaming----------
        //**********Latitude, Longitude, Altitude Data**********
        //Call GPS class
        f>>nmea;
        GPS gps(nmea);
            //Is the data GPGGA data only?
            if(gps.isValidGGA(nmea))
            {
                balloondata<<gps.latitude<<" "<<gps.latc<<endl;
                balloondata<<gps.longitude<<" "<<gps.lonc<<endl;
                balloondata<<gps.altitude<<" ft"<<endl;
            }

        //**********Temperature Data**********
        //Call TEMP class
        TEMP temp;
        balloondata<<temp.temp_F<<" F"<<endl;
//	if ( wiringPiSetup() == -1 )
//		exit( 1 );
//       
//        
//
//        temp.tempout();
//   
        //**********Pressure Data**********
        //Call PRESSURE class
        PRESSURE pressure;
        balloondata<<pressure.pressure_psi<<" psi"<<endl;

        //**********Camera Data**********
        //Counter to take pictures every 10 seconds, uses divisor check
        if(count%2==0)
        {
            //Call Raspicam directory classes
            raspicam::RaspiCam Camera;
            Camera.grab();
            unsigned char *data=new unsigned char [Camera.getImageTypeSize(raspicam::RASPICAM_FORMAT_RGB)];
            Camera.retrieve(data,raspicam::RASPICAM_FORMAT_RGB);
            ofstream outFile("raspicam_image.jpg",ios::binary);
            outFile<<"P6\n"<<Camera.getWidth()<<" "<<Camera.getHeight()<<" 255\n";
            outFile.write((char*) data, Camera.getImageTypeSize(raspicam::RASPICAM_FORMAT_RGB));
            cout<<"Image saved at raspicam_image.jpg"<<endl;
            delete data;
        }
        //**********Servos**********
        //Altitude = 1000 feet?
        //if(gps.altitude==1000)
        //{
            //Call servo class with channel from Maestro
            //Set max position for servo1
            SERVO servo1(fd,1,9600);
        //}

        //Altitude = 2000 feet?
        //if(gps.altitude==2000)
        //{
            //Call servo class with channel from Maestro
            //Set max position for servo2
            SERVO servo2(fd,5,9600);
        //}
        //Close port
        close(fd);

        //End timer
        //Clock time elapsed
        clock_t endTimer=clock();
        double duration =(endTimer-startTimer)/(double) CLOCKS_PER_SEC;
        //Run duration in seconds
        //durationOverall=duration/1000000;
        
        double durationOverall;
        balloondata<<duration<<" ms"<<endl;

        //**********Output**********
        balloondata.close();
        
        //Wait 5 seconds for new data
        count++;
        //sleep(5);
        durationOverall=duration+5;
        //**********RELEASE**********
        //Ignite nichrome wire and release mechanism at 3000 ft
//        if(gps.altitude==3000)
//        {
//            
//            //Shut off data streaming
//            hotwire=true;
//        }
}       
    //--------------------------------------------------------------------------
    //MISSION ACCOMPLISHED
	return 0;
}
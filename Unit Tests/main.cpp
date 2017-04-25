#include <iostream>
#include <string>
#include <vector>
#include <iterator>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <cstdio>
#include <ctime>
#include <fstream>
#include <sstream>

//RaspiCam libraries
#include <raspicam/raspicam.h>
#include <raspicam/raspicamtypes.h>
#include <raspicam/raspicam_cv.h>

//Camera header file


//Servos
#include "servo.h"
#include <fcntl.h>

//GPS
#include "gps.h"
#include "hotwire.h"

//Output
#include <fstream>
#include <iomanip>

using namespace std;

int main()
{
    //*****GPS*****
//        //Set baud rate for GPS
//        system("stty -F /dev/ttyUSB0 4800");
//        //Input NMEA line for GPS class
//        string nmea;
//        fstream f;
//        //Open GPS USB device
//        f.open("/dev/ttyUSB0");
//        //Error output check
//        if(f.is_open())
//        {
//                cout<<"Device Opened..."<<endl;
//        }
//        else
//        {
//                cout<<"Unable to open GPS"<<endl;
//        }
//        //Call GPS class
//        GPS gps;
//        
//        while(1)
//        {
//            //**********Latitude, Longitude, Altitude Data**********
//                //Set data to bad to start
//                bool goodGPS=false;
//                //Loop until a GPGGA point is read with good data
//                while(goodGPS!=true)
//                {
//                    //Stream data from GPS device
//                    f>>nmea;
//                    //Call GPS class
//                    gps.GPSTest(nmea);
//                        //Is the data GPGGA data only?
//                        if(gps.isValidGGA(nmea))
//                        {
//                            //Save latitude data to overwritten file
//                            cout<<setprecision(6)<<gps.latitude<<" "<<gps.latc<<endl;
//
//                            //Save longitude data to overwritten file
//                            cout<<setprecision(6)<<gps.longitude<<" "<<gps.lonc<<endl;
//
//                            //Save altitude data to overwritten file
//                            cout<<setprecision(5)<<gps.altitude<<endl;
//
//                            //Good data has been recorded, exit GPS
//                            goodGPS=true;
//                        }
//                }//End while loop - GPS
//        }
    
    //Open Pololu Micro Maestro 6-channel USB controller
//        const char * device = "/dev/ttyACM0";  // Linux
//        int fd = open(device, O_RDWR | O_NOCTTY);
//        if (fd == -1)
//        {
//                perror(device);
//                return 1; 
//        }
//        
//        SERVO servo(fd);
//        
//        int count =1;
//        bool servomax=false;
//        bool servomin=false;
//        while(1)
//        {
//            if(count>=10&&servomax!=true)
//            {
//                servo.maestroSetTarget(fd,1,30000);
//                servomax=true;
//                sleep(1);
//            }
//            if(count>=15&&servomin!=true)
//            {
//                servo.maestroSetTarget(fd,1,-30000);
//                servomin=true;
//                sleep(1);
//            }
//                count++;
//                servo.maestroSetTarget(fd,1,0);
//            cout<<count<<endl;
//            sleep(1);
//        }
    
    HOTWIRE hotwire;
    hotwire.HOTWIREFIRE(10);

    return 0;
}
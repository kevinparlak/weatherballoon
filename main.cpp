#include <iostream>
#include <string>
#include <vector>
#include <iterator>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <cstdio>
#include <ctime>

//Threading
#include <thread>

//GPS
#include "gps.h"

//Camera
#include "camera.h"

//Servos
#include "servo.h"
#include <fcntl.h>

//Temperature Sensor
#include "temp.h"
#include <stdint.h>

//Pressure Sensor
#include "pressure.h"

//Hotwire
#include "hotwire.h"

//Output
#include <fstream>

using namespace std;

int main()
{
    //----------System checks----------
        //*****TIMER*****
			//Start timer
			clock_t startTimer=clock();
			//Timer output check
			cout<<"Timer started..."<<endl;
    
        //*****GPS*****
			//Set baud rate for GPS
			system("stty -F /dev/ttyUSB0 4800");
			//Input NMEA line for GPS class
			string nmea;
			fstream f;
			//Open GPS USB device
			f.open("/dev/ttyUSB0");
			//Error output check
			if(f.is_open()
			{
				cout<<"Device Opened..."<<endl;
			}
			else
			{
				cout<<"Unable to open GPS"<<endl;
			}

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
			//Set count for every other 5 second delay
			int count=0;
			//Overwritten image file path name
			const char *pathCurrent="Pictures/current_image.jpg";
			//Saved image file path name
			const char *pathSaved="Pictures/Saved/saved_image.jpg";			
        
        //*****OUTPUT FILE*****
			//Overwritten
			ofstream balloondata;
			balloondata.open("balloondata.txt");
			//Error output check
			if(balloondata.is_open())
			{
				cout<<"Streaming data file open..."<<endl;
			}
			else
			{
				cout<<"Error opening streaming file"<<endl;
			}
			//Saved
			ofstream balloondataSAVED;
			balloondataSAVED.open("Saved/balloondataSAVED.txt");
			//Error output check
			if(balloondataSAVED.is_open())
			{
				cout<<"Saved data file open..."<<endl;
			}
			else
			{
				cout<<"Error opening saved file"<<endl;
			}
        
		//*****HOTWIRE*****
			//False means hotwire is off
			bool hotwireON=false;
			//Error output check
			cout<<"Hotwire is off..."<<endl;
			
//Loop code and classes while hotwire is not on
//Indicates end of mission
while(hotwireON!=true)
{
    //----------Data Streaming----------
        //**********Latitude, Longitude, Altitude Data**********
			//Set data to bad to start
			bool goodGPS=false;
			//Loop until a GPGGA point is read with good data
			while(goodGPS!=true)
			{
				//Stream data from GPS device
				f>>nmea;
				//Call GPS class
				GPS gps(nmea);
					//Is the data GPGGA data only?
					if(gps.isValidGGA(nmea))
					{
						//Save latitude data to overwritten file
						balloondata<<gps.latitude<<" "<<gps.latc<<endl;
						//Save latitude data to appended file
						balloondataSAVED<<gps.latitude<<" "<<gps.latc<<endl;
						//Save longitude data to overwritten file
						balloondata<<gps.longitude<<" "<<gps.lonc<<endl;
						//Save longitude data to appended file
						balloondataSAVED<<gps.longitude<<" "<<gps.lonc<<endl;
						//Save altitude data to overwritten file
						balloondata<<gps.altitude<<endl;
						//Save altitude data to appended file
						balloondataSAVED<<gps.altitude<<" ft"<<endl;
						
						//Good data has been recorded, exit GPS
						goodGPS=true;
					}
			}
		
        //**********Temperature Data**********
			//Call TEMP class
			TEMP temp;
			//Save temperature data to overwritten file
			balloondata<<temp.temp_F<<endl;
			//Save temperature data to appended file
			balloondataSAVED<<temp.temp_F<<" F"<<endl;

        //**********Pressure Data**********
			//Call PRESSURE class
			PRESSURE pressure;
			//Save pressure data to overwritten file
			balloondata<<pressure.pressure_psi<<endl;
			//Save temperature data to appended file
			balloondataSAVED<<pressure.pressure_psi<<" psi"<<endl;

        //**********Camera Data**********
			//Counter to take pictures every 10 seconds, uses divisor check
			if(count%2==0)
			{
				CAMERA cameraCurrent(pathCurrent);
				//How to change the name of the picture every 10 seconds to record multiple pictures????
				CAMERA cameraSaved(pathSaved);
			}
			//Wait 10 seconds for new data
			count++;
		
        //**********Servos**********
			//Altitude = 1000 feet AGL?
				//Redunancy????

			if(gps.altitude>=1000)
			{
				//Call servo class with channel from Maestro
				//Set max position for servo1000
				SERVO servo1000(fd,1,9600);
			}

			//Altitude = 2000 feet AGL?
				//Redunancy????

			if(gps.altitude>=2000)
			{
				//Call servo class with channel from -+Maestro
				//Set max position for servo2000
				SERVO servo2000(fd,5,9600);
			}
			
			//Close port
			close(fd);

        //**********Output**********
			//Closing overwritten text file
			balloondata.close();

        //**********RELEASE**********
			//Ignite nichrome wire and release mechanism at AGL == 3000 ft
			//Redunancy???
			
			if(gps.altitude>=3000)
			{
				//Call HOTWIRE class for specified number on seconds
				HOTWIRE hotwire(10);
				//Shut off data streaming
				hotwireON=true;
			}
		
		//Only sleep if final class has not been called
		if(hotwireON==false)
		{
			//Sleep for 5 seconds before looping
			sleep(5);
		}
		
}//End while loop
	//End timer
	//Clock time elapsed
	clock_t endTimer=clock();
	double duration =(endTimer-startTimer)/(double) CLOCKS_PER_SEC;
	//Input duration into saved file
	balloondataSAVED<<duration<<" ms"<<endl;
	
	//Close appended file
	balloondataSAVED.close();

//--------------------------------------------------------------------------
//MISSION ACCOMPLISHED
cout<<"MISSION ACCOMPLISHED"<<endl;

	return 0;
}
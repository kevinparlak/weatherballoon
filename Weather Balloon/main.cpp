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
//RaspiCam libraries
#include <raspicam/raspicam.h>
#include <raspicam/raspicamtypes.h>
#include <raspicam/raspicam_cv.h>

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
#include <iomanip>

using namespace std;

int main()
{
    //----------System checks----------  
        //*****GPS*****
            //Set baud rate for GPS
            system("stty -F /dev/ttyUSB0 4800");
            //Input NMEA line for GPS class
            string nmea;
            fstream f;
            //Open GPS USB device
            f.open("/dev/ttyUSB0");
            //Error output check
            if(f.is_open())
            {
                    cout<<"Device Opened..."<<endl;
            }
            else
            {
                    cout<<"Unable to open GPS"<<endl;
            }
            //Call GPS class
            GPS gps;
            
        //*****SERVOS*****
            //Open Pololu Micro Maestro 6-channel USB controller
            const char * device = "/dev/ttyACM0";  // Linux
            int fd = open(device, O_RDWR | O_NOCTTY);
            if (fd == -1)
            {
                    perror(device);
                    return 1; 
            }
            //Call SERVO class
            SERVO servo1000(fd);
            SERVO servo2000(fd);
            
            // Reset Checks Variables
            bool servo1000DONE = false;
            bool servoZERO = false;
            bool servo2000DONE=false;
            bool servo2ZERO=false;
            
        //*****PICTURE*****
            //Set count for every other 5 second delay
            int count=0;	
            //Call RaspiCam directory classes
            raspicam::RaspiCam_Cv Camera;
            cv::Mat image;

            //Capture count
            int nCount=30;

            //Set camera parameters
            Camera.set(CV_CAP_PROP_FORMAT, CV_8UC1);
            //Open Camera
            cout<<"Opening Camera..."<<endl;
            //Error output check
            if(!Camera.open())
            {
                cerr<<"Error opening camera"<<endl;
            }
            
        //*****PRESSURE*****
            //Call PRESSURE class
            PRESSURE pressure;

        //*****TEMPERATURE*****
            //Call TEMP class
            TEMP temp;
            
        //*****Saved file*****
            //Count for pictures saved
            int piccnt=1;

            //Saved
            ofstream balloondataSAVED;
            balloondataSAVED.open("/media/pi/98E1-3336/Data/balloondataSAVED.txt");
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
            //Call HOTWIRE class
            HOTWIRE hotwire;
            //False means hotwire is off
            bool hotwireON=false;
            //Error output check
            cout<<"Hotwire is OFF..."<<endl;
			
//Loop code and classes while hotwire is not on
//Indicates end of mission
while(hotwireON!=true)
{
    //*****Overwritten file*****
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
                gps.GPSTest(nmea);
                    //Is the data GPGGA data only?
                    if(gps.isValidGGA(nmea))
                    {
                        //Save latitude data to overwritten file
                        balloondata<<setprecision(6)<<gps.latitude<<" "<<gps.latc<<endl;
                        //Save latitude data to appended file
                        balloondataSAVED<<setprecision(6)<<gps.latitude<<" "<<gps.latc<<endl;

                        //Save longitude data to overwritten file
                        balloondata<<setprecision(6)<<gps.longitude<<" "<<gps.lonc<<endl;
                        //Save longitude data to appended file
                        balloondataSAVED<<setprecision(6)<<gps.longitude<<" "<<gps.lonc<<endl;

                        //Save altitude data to overwritten file
                        balloondata<<setprecision(5)<<gps.altitude<<" ft"<<endl;
                        //Save altitude data to appended file
                        balloondataSAVED<<setprecision(5)<<gps.altitude<<" ft"<<endl;

                        //Good data has been recorded, exit GPS
                        goodGPS=true;
                    }
            }//End while loop - GPS
		
        //**********Temperature Data**********
            //Save temperature data to overwritten file
            balloondata<<setprecision(3)<<temp.temp_F<<" F"<<endl;
            //Save temperature data to appended file
            balloondataSAVED<<setprecision(3)<<temp.temp_F<<" F"<<endl;

        //**********Pressure Data**********
            //Save pressure data to overwritten file
            balloondata<<setprecision(4)<<pressure.pressure_psi<<" psi"<<endl;
            //Save temperature data to appended file
            balloondataSAVED<<setprecision(4)<<pressure.pressure_psi<<" psi"<<endl;

        //**********Camera Data**********
            //Counter to take pictures every 10 seconds, uses divisor check
            if(count%2==0)
            {
                //Folder location
                string path = "/media/pi/98E1-3336/Data/";
                //Type of picture
                string picfile = ".jpg";
                //Overall filename for image
                string filename;
                //Incrementing integer for saved images
                string fileint;
                //Link variables
                filename.append(path);

                //Convert integer to string and append
                ostringstream convert;
                convert<<piccnt;
                fileint=convert.str();
                filename=filename+fileint;
                filename.append(picfile);

                //Convert filename to C string for code
                const char *file=filename.c_str();

                //Start capture
                for(int i=0;i<nCount;i++)
                {
                    Camera.grab();
                    Camera.retrieve(image);
                }
                
                //SAVED file name
                cv::imwrite(file,image);
                //OVERWRITTEN file name
                cv::imwrite("image.jpg",image);

                //Increment picture count
                piccnt++;
            }
            //Wait 10 seconds for new data
            count++;
		
       //**********Servos**********
            //Altitude = 1000 feet AGL?
            if(gps.altitude>=900&&servo1000DONE!=true)
            {
                //Call servo class with channel from Maestro
                //Set max position for servo1000
                servo1000.maestroSetTarget(fd,1,30000);
                //Reset
                servo1000DONE=true;
            }
			
                //Reset servo1000
                if(servo1000DONE==true&&servoZERO!=true)
                {
                    sleep(1);
                    //Call servo class with channel 1 from Maestro
                    //Reset position to 0
                    servo1000.maestroSetTarget(fd,1,0);
                    servoZERO=true;
                }

            //Altitude = 2000 feet AGL?
            if(gps.altitude>=1900&&servo2000DONE!=true)
            {
                //Call servo class with channel from Maestro
                //Set max position for servo2000
                servo2000.maestroSetTarget(fd,5,30000);
                //Reset
                servo2000DONE=true;
            }
			
                //Reset servo2000
                if(servo2000DONE==true)
                {
                    sleep(1);
                    //Call servo class with channel 5 from Maestro
                    //Reset position to 0
                    servo2000.maestroSetTarget(fd,5,0);
                    servo2ZERO=true;
                }
			
            //Close port
            close(fd);

        //**********Output**********
            //Closing overwritten text file
            balloondata.close();
            
        //**********Hotwire**********
            //Ignite nichrome wire and release mechanism at AGL >= 3000 ft
                if(gps.altitude>=2900)
                {
                    //Fire hotwire circuit for specified amount of time
                    hotwire.HOTWIREFIRE(20);
                    //Shut off data streaming
                    hotwireON=true;
                    //Error output check
                    if(hotwireON==true)
                    {
                        cout<<"Hotwire is ON..."<<endl;
                    }
                }
		
		//Only sleep if final class has not been called
		if(hotwireON==false)
		{
                    //Sleep for 3 seconds before looping
                    sleep(3);
		}
		
}//End while loop - Mission

        //Close appended file
	balloondataSAVED.close();

//--------------------------------------------------------------------------
//MISSION ACCOMPLISHED
cout<<"MISSION ACCOMPLISHED"<<endl;

	return 0;
}
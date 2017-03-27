// Distributed with a free-will license.
// Use it any way you want, profit or free, provided it fits in the licenses of its associated works.
// BMP280
// This code is designed to work with the BMP280_I2CS I2C Mini Module available from ControlEverything.com.
// https://www.controleverything.com/content/Barometer?sku=BMP280_I2CSs#tabs-0-product_tabset-2

#include <stdio.h>
#include <stdlib.h>
#include <linux/i2c-dev.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include <fcntl.h>
#include <math.h>
//Temperature header file
#include "temp.h"
using namespace std;

//Constructor
TEMP::TEMP()
{
    tempout();
};

void TEMP::tempout()
{
    //Open i2c bus on GPIO pins
    int file;
    char *bus = "/dev/i2c-1";
        //Error check on opening the bus
	if((file = open(bus, O_RDWR)) < 0) 
	{
            printf("Failed to open the bus. \n");
            exit(1);
	}
	//Slave address for i2c device, BMP280 is 0x77(108)
	ioctl(file, I2C_SLAVE, 0x77);
        
    //Read 24 bytes of data from address(0x88)
    char reg[1] = {0x88};
    write(file, reg, 1);
    char data[24] = {0};
        //Error check on reading input data
	if(read(file, data, 24) != 24)
	{
            printf("Error : Input/output Error \n");
            exit(1);
	}
    
    //Convert the data
    //Temperature coefficients
	int dig_T1 = data[1] * 256 + data[0];
	int dig_T2 = data[3] * 256 + data[2];
	if(dig_T2 > 32767)
	{
		dig_T2 -= 65536;
	}
	int dig_T3 = data[5] * 256 + data[4];
	if(dig_T3 > 32767)
	{
		dig_T3 -= 65536;
	}
        
    //Pressure coefficients
	int dig_P1 = data[7] * 256 + data[6];
	int dig_P2  = data[9] * 256 + data[8];
	if(dig_P2 > 32767)
	{
		dig_P2 -= 65536;
	}
	int dig_P3 = data[11]* 256 + data[10];
	if(dig_P3 > 32767)
	{
		dig_P3 -= 65536;
	}
	int dig_P4 = data[13]* 256 + data[12];
	if(dig_P4 > 32767)
	{
		dig_P4 -= 65536;
	}
	int dig_P5 = data[15]* 256 + data[14];
	if(dig_P5 > 32767)
	{
		dig_P5 -= 65536;
	}
	int dig_P6 = data[17]* 256 + data[16];
	if(dig_P6 > 32767)
	{
		dig_P6 -= 65536;
	}
	int dig_P7 = data[19]* 256 + data[18];
	if(dig_P7 > 32767)
	{
		dig_P7 -= 65536;
	}
	int dig_P8 = data[21]* 256 + data[20];
	if(dig_P8 > 32767)
	{
		dig_P8 -= 65536;
	}
	int dig_P9 = data[23]* 256 + data[22];
	if(dig_P9 > 32767)
	{
		dig_P9 -= 65536;
	}
		
    //Select control measurement register(0xF4)
    //Normal mode, temperature and pressure over sampling rate = 1(0x27)
	char config[2] = {0};
	config[0] = 0xF4;
	config[1] = 0x27;
	write(file, config, 2);
	
    //Select config register(0xF5)
    //Stand_by time = 1000 ms(0xA0)
	config[0] = 0xF5;
	config[1] = 0xA0;
	write(file, config, 2);
	sleep(1);
	
    //Read 8 bytes of data from register(0xF7)
    //pressure msb1, pressure msb, pressure lsb, temp msb1, temp msb, temp lsb, humidity lsb, humidity msb
	reg[0] = 0xF7;
	write(file, reg, 1);
        //Error check on register data
	if(read(file, data, 8) != 8)
	{
            printf("Error : Input/output Error \n");
            exit(1);
	}
	
    //Convert pressure and temperature data to 19-bits
	long adc_p = (((long)data[0] * 65536) + ((long)data[1] * 256) + (long)(data[2] & 0xF0)) / 16;
	long adc_t = (((long)data[3] * 65536) + ((long)data[4] * 256) + (long)(data[5] & 0xF0)) / 16;
		
    //Temperature offset calculations
	double var1 = (((double)adc_t) / 16384.0 - ((double)dig_T1) / 1024.0) * ((double)dig_T2);
	double var2 = ((((double)adc_t) / 131072.0 - ((double)dig_T1) / 8192.0) *(((double)adc_t)/131072.0 - ((double)dig_T1)/8192.0)) * ((double)dig_T3);
	double t_fine = (long)(var1 + var2);
	double cTemp = (var1 + var2) / 5120.0;
	double fTemp = cTemp * 1.8 + 32;
        this->temp_F=fTemp;
		
    //Pressure offset calculations
	var1 = ((double)t_fine / 2.0) - 64000.0;
	var2 = var1 * var1 * ((double)dig_P6) / 32768.0;
	var2 = var2 + var1 * ((double)dig_P5) * 2.0;
	var2 = (var2 / 4.0) + (((double)dig_P4) * 65536.0);
	var1 = (((double) dig_P3) * var1 * var1 / 524288.0 + ((double) dig_P2) * var1) / 524288.0;
	var1 = (1.0 + var1 / 32768.0) * ((double)dig_P1);
	double p = 1048576.0 - (double)adc_p;
	p = (p - (var2 / 4096.0)) * 6250.0 / var1;
	var1 = ((double) dig_P9) * p * p / 2147483648.0;
	var2 = p * ((double) dig_P8) / 32768.0;
	double pressure = (p + (var1 + var2 + ((double)dig_P7)) / 16.0) / 100;
        
    //Output data to screen
	printf("%.2f F \n", this->temp_F);
};

//Destructor
TEMP::~TEMP()
{
    
};

//---------------------------------------------------------------------
/*
DHT11 Sensor
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <unistd.h>
#include <math.h>
#include <fstream>
//Temperature header file
#include "temp.h"
//WiringPi directory
#include <wiringPi/wiringPi.h>

#define MAXTIMINGS	85
//GPIO pin being used by the temperature sensor
#define DHTPIN		22

using namespace std;

//Constructor
TEMP::TEMP()
{

};

//Destructor
TEMP::~TEMP()
{

};

//Temperature function
void TEMP::tempout()
{
    //Initializing variables
    int dht11_dat[5] = { 0, 0, 0, 0, 0 };
    uint8_t laststate	= HIGH;
    uint8_t counter		= 0;
    uint8_t j		= 0, i;
    float	f; 
 
        //Define pin to be used for temperature sensor
	pinMode( DHTPIN, OUTPUT );
        //Write low reading to pin
	digitalWrite( DHTPIN, LOW );
        //Wait 18 ms
	delay( 18 );
        //Write high reading to pin
	digitalWrite( DHTPIN, HIGH );
        //Wait 40 ms
	delayMicroseconds( 40 );
	pinMode( DHTPIN, INPUT );
 
        //Loop 85 times
	for ( i = 0; i < MAXTIMINGS; i++ )
	{
            //Start counter
		counter = 0;
                //Add to counter while state is HIGH
		while ( digitalRead( DHTPIN ) == laststate )
		{
			counter++;
                        //Wait 1 ms
			delayMicroseconds( 1 );
                        //Exit if max bits reached
			if ( counter == 255 )
			{
				break;
			}
		}
                //Grab a new state from the pin
		laststate = digitalRead( DHTPIN );
                //Exit if max bits reached
		if ( counter == 255 )
			break;
                //Binary math to grab signal
		if ( (i >= 4) && (i % 2 == 0) )
		{
			dht11_dat[j / 8] <<= 1;
			if ( counter > 16 )
				dht11_dat[j / 8] |= 1;
			j++;
		}
	}
        
        //Convert temperature to degrees F
	f = dht11_dat[2] * 9. / 5. + 32;
        //Control significant figure output
        f=floor(f*100)/100;
        //Grab only good data
        if(f>=35&&f<=80)
            cout<<f<<endl;
}
 * */
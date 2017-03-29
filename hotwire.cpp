#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

//WiringPi libraries
#include <wiringPi/wiringPi.h>
//Hotwire header file
#include "hotwire.h"

//Define output GPIO pin
#define DHTPIN		7

//Constructor
HOTWIRE::HOTWIRE()
{
    
};

HOTWIRE::HOTWIRE(int time)
{
    digitalWrite( DHTPIN, HIGH );
    delay(time);
    digitalWrite( DHTPIN, LOW );
};

//Destructor
HOTWIRE::~HOTWIRE()
{
    
};
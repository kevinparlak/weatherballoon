#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <unistd.h>
//WiringPi libraries
#include <wiringPi/wiringPi.h>
//Hotwire header file
#include "hotwire.h"

//Define output GPIO pin
#define GPIO		17

//Constructor
HOTWIRE::HOTWIRE()
{
    //Configure Pi to use GPIO pin outputs
    wiringPiSetupGpio();
};

void HOTWIRE::HOTWIREFIRE(int time)
{
    //Set pinmode
    pinMode(GPIO, OUTPUT);
    //Write high = 3.3V from the GPIO pin
    digitalWrite(GPIO, HIGH);
    //Wait (seconds)
    sleep(time);
    //Write low = 0 V from the GPIO pin
    digitalWrite(GPIO, LOW);
};

//Destructor
HOTWIRE::~HOTWIRE()
{
    
};
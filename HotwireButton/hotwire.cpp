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
    wiringPiSetupGpio();
};

void HOTWIRE::HOTWIREFIRE(int time)
{
    pinMode(GPIO, OUTPUT);
    digitalWrite(GPIO, HIGH);

    sleep(time);
    digitalWrite(GPIO, LOW);
};

//Destructor
HOTWIRE::~HOTWIRE()
{
    
};
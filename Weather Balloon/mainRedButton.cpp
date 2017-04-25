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
	//Call servo class with channel from Maestro
	//Set max position for servo1000
		SERVO servo1000(fd,1,9600);

//--------------------------------------------------------------------------
//Red Ribbon Redundancy Measure Initiated
cout<<"Red Redunancy Initiated..."<<endl;

	return 0;
}
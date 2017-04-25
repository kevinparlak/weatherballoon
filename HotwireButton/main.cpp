#include <iostream>
#include <string>
#include <vector>
#include <iterator>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <cstdio>
#include <ctime>

//Hotwire
#include "hotwire.h"

using namespace std;

int main()
{
	//Call hotwire class with channel from Maestro
        HOTWIRE hotwire;
	//Set time to turn on GPIO pin 17
        hotwire.HOTWIREFIRE(20);

//--------------------------------------------------------------------------
//Black and White Ribbon Redundancy Measure Initiated
cout<<"Hotwire Redunancy Initiated..."<<endl;

	return 0;
}
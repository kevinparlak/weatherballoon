#include <iostream>
#include <string>
#include <vector>
#include <assert.h>
#include <sstream>
#include <stdlib.h>
//GPS header file
#include "gps.h"

using namespace std;

//Constructor
GPS::GPS()
{
    latitude            =   0;
    longitude           =   0;
    altitude            =   0;
}

//Destructor
GPS::~GPS()
{    
    latitude            =   0;
    longitude           =   0;
    altitude            =   0;
}

GPS::GPS(const string GGASentence)
{
    //If a GPGGA sentence, set output
    if (isValidGGA(GGASentence)) 
        setValuesGGA(GGASentence);
    else
    {
        latitude    =   latitude;
        longitude   =   longitude;
        altitude    =   altitude;
    }  
}

//Validation function
bool GPS::isValidGGA(const string GGASentence)
{
    //Set data to valid to begin
    bool returnBool = true;
    //Call split by comma function
    vector<string> elementVector = splitStringByComma(GGASentence);
        
    //Validating GPGGA data
        //Is the size of the line not equal to 15?
        if (elementVector.size() != 15)                 returnBool = false;
        else
        {
            //Is header GPGGA?
            if (elementVector[0] != "$GPGGA")               returnBool = false;
            //0 indicates invalid data
            if (elementVector[6] == "0")                    returnBool = false;
            //Is the length of the longitude data less than length of a minute
            string str1;
            str1=elementVector[4];
            if (str1.length() < MINUTE_LENGTH)              returnBool = false;
            //Is the length of the latitude data less than length of a minute
            string str2;
            str2=elementVector[2];
            if (str2.length() < MINUTE_LENGTH)              returnBool = false;
            if (elementVector[7] == "0")                    returnBool = false;
        }

    return returnBool;
}

//Setter function
void GPS::setValuesGGA(string GGA)
{
    //Elevation
    int elevation = 1154;   //ft
    //STL vector calls split function
    vector<string> elementVector = splitStringByComma(GGA);
    
    // Assert we have a GGA sentence
    assert(elementVector[0] == "$GPGGA");
    
    //North-South
    //Grab latitude from element vector 2
    this->latitude            = getCoordinates(elementVector[2]);
   
    //If direction is 'S', set coordinate to south
    if (elementVector[3] == "S")
        latc='S';
    else
        latc='N';
    
    //East - West
    //Grab longitude from element vector 4
    this->longitude           = getCoordinates(elementVector[4]);
    //If direction is 'W', set coordinate to west
    if (elementVector[5] == "W")
        lonc='W';
    else
        lonc='E';
    
    //Grab altitude and convert to ft with - elevation above SSL
    this->altitude              =   stringToDouble(elementVector[9]);
    this->altitude              =   (3.28*(this->altitude)-elevation);
}

//Split by comma function
vector<string> GPS::splitStringByComma(string input)
{
    //Initializing variables
    vector<string>  returnVector;
    stringstream    ss(input);
    string          element;
    
    //Separate data based on comma seperation
        while(getline(ss, element, ','))
        {
            returnVector.push_back(element);
        }
    
    return returnVector;
}

//Decimal degrees function
double degreesToDecimal(int degrees, double minutes, int seconds )
{
    //Initializing variables
    double returnDouble = 0;
        //Calculate coordinate in decimal degrees
        returnDouble = degrees + minutes/60 + seconds/3600.0f;
    
    return returnDouble;
}

//String to double conversion function
double GPS::stringToDouble(string inputString)
{
    //If string empty, return 0
    double returnValue = 0;
        //Convert to string
        istringstream istr(inputString);
        istr >> returnValue;
        
    return (returnValue);
}

//Coordinate function
double GPS::getCoordinates(string array)
{
    //Initializing variables
    double decimalDegrees = 0;
    string degreeArray;
    string minuteArray;

    //Check for length of latitude and longitude and parse correctly
    if (array.length() > MINUTE_LENGTH)
    {

        degreeArray.assign(array.begin()+1, array.end() - 7);
        minuteArray.assign(array.end() - 7, array.end());
    }
    else
    {
        degreeArray.assign(array.begin(),array.end()-7);
        minuteArray.assign(array.begin()+2,array.end());
    }
    
        //Convert strings into numbers
        int degrees;
        double minutes;
        degrees = atoi(degreeArray.c_str());
        minutes = stringToDouble(minuteArray);

        //Convert degrees and minutes into decimal
        decimalDegrees = degreesToDecimal(degrees,minutes);
        
    return decimalDegrees;
}
#ifndef GPS_H
#define GPS_H

#include <vector>
#include <string>

//Length of minutes data in NMEA
#define MINUTE_LENGTH 9

using namespace std;

//Class definition for GPS
class GPS
{
public:
    //Default constructor
    GPS();
    void GPSTest(const string GGASentence);
    double  latitude;
    double  longitude;
    double  altitude;
    char latc;
    char lonc;
    bool isValidGGA(const string GGASentence);
    //Destructor
    ~GPS();

private:
    void setValuesGGA(const string GGASentence);
    vector<string> splitStringByComma(const string);
    double stringToDouble(const string);
    double getCoordinates(string);
};

double degreesToDecimal(const int Degrees,const double Minutes,const int seconds = 0);

#endif // GPS_H
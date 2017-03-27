// Distributed with a free-will license.
// Use it any way you want, profit or free, provided it fits in the licenses of its associated works.
// BMP280
// This code is designed to work with the BMP280_I2CS I2C Mini Module available from ControlEverything.com.
// https://www.controleverything.com/content/Barometer?sku=BMP280_I2CSs#tabs-0-product_tabset-2

#ifndef TEMP_H
#define TEMP_H

//Class definition for temperature sensor
class TEMP
{
public:
    //Default constructor
    TEMP();
    double temp_F;
    //Destructor
    ~TEMP();
private:
    void tempout();
//---------------------------------------------------------------------    
    /*
     DHT11 Sensor
    //Default constructor
    TEMP();
    void tempout();
    //Destructor
    ~TEMP();
     */
    //
};

#endif /* TEMP_H */


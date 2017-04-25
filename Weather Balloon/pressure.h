// Distributed with a free-will license.
// Use it any way you want, profit or free, provided it fits in the licenses of its associated works.
// BMP280
// This code is designed to work with the BMP280_I2CS I2C Mini Module available from ControlEverything.com.
// https://www.controleverything.com/content/Barometer?sku=BMP280_I2CSs#tabs-0-product_tabset-2

#ifndef PRESSURE_H
#define PRESSURE_H

//Class definition for pressure sensor
class PRESSURE
{
public:
    //Default constructor
    PRESSURE();
    double pressure_psi;
    //Destructor
    ~PRESSURE();
private:
    void pressureout();
};

#endif /* PRESSURE_H */
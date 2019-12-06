#ifndef GYRO_H
#define GYRO_H

#include <Arduino.h>
#include <MPU9250.h>

class Gyro {
private:


    double x;
    double y;
    double z;

//
public:
    Gyro();

    void initialize(int pinSDA, int pinSCL, double declination);

    void update();

    // position getters
    double getX();
    double getY();
    double getZ();

    const double ANGLE_ERROR = 0.0; // determine experimentally
};

#endif

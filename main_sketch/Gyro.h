#ifndef GYRO_H
#define GYRO_H

#include <Arduino.h>
#include <Wire.h>

class Gyro {
private:
    const int MPU_ADDR = 0x68;
    int16_t AcX,AcY,AcZ,Tmp,GyX,GyY,GyZ;
    int minVal=265;
    int maxVal=402;

    double x;
    double y;
    double z;

//
public:
    Gyro();

    void initialize(int pinSDA, int pinSCL);

    void update();

    // position getters
    double getX();
    double getY();
    double getZ();

    const double ANGLE_ERROR = 0.0;
};

#endif

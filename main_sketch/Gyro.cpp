// Gyro
// This class interfaces with an MPU9250 3-axis gyroscope to get the angle
// displacement.

// Code largely taken from bit.ly/2PXP7Aw


// MEMBER VARIABLES
// const int MPU_ADDR = 0x68;
// int16_t AcX,AcY,AcZ,Tmp,GyX,GyY,GyZ;
// int minVal=265;
// int maxVal=402;

// double yaw;
// double pitch;
// double roll;


/*
KNOWN BUGS
-> needs to be reprogrammed to deal only with change in angles, rather than absolute angles

*/


#include "Gyro.h"

// constructor
Gyro::Gyro() {}


void Gyro::initialize(int pinSDA, int pinSCL, double declination) {
    // calibrate gyroscope
    // magnetic declination in Lancaster, CA is +12.01 degrees

}


// update x,y,z, with latest values
void Gyro::update() {
    Wire.beginTransmission(MPU_ADDR);
    Wire.write(0x3B);
    Wire.endTransmission(false);
    Wire.requestFrom(MPU_ADDR,14,true);
    AcX=Wire.read()<<8|Wire.read();
    AcY=Wire.read()<<8|Wire.read();
    AcZ=Wire.read()<<8|Wire.read();
    int xAng = map(AcX,minVal,maxVal,-90,90);
    int yAng = map(AcY,minVal,maxVal,-90,90);
    int zAng = map(AcZ,minVal,maxVal,-90,90);

    // update member variables with values
    x = RAD_TO_DEG * (atan2(-yAng, -zAng)+PI);
    y = RAD_TO_DEG * (atan2(-xAng, -zAng)+PI);
    z = RAD_TO_DEG * (atan2(-yAng, -xAng)+PI);
}




////////////////////////////////
// ANGLE DISPLACEMENT GETTERS //
////////////////////////////////


double Gyro::getX() {
    return x;
}


double Gyro::getY() {
    return y;
}


double Gyro::getZ() {
    return z;
}

#ifndef ENGINE_H
#define ENGINE_H

#include <Arduino.h>
#include <Servo.h>
#include "Gyro.h"


enum DirectionState {
    FORWARD,
    BACKWARD
};

enum TurningState {
    ROTATING_RIGHT,
    ROTATING_LEFT,
    TURNING_RIGHT,
    TURNING_LEFT,
    CORRECTING_RIGHT,
    CORRECTING_LEFT,
    NOT_TURNING
};


class Engine {
private:
    // state variables
    DirectionState directionState;
    TurningState turningState;
    int currentSpeed;
    int savedSpeed;
    double distanceTraveled;
    double finalTurnAngle;
    double stableAngle;

    // physical components
    Servo leftMotor;
    Servo rightMotor;
    Gyro gyro;

    // time
    unsigned long timeTurnCompleted;
    unsigned long timeSinceLastUpdate;

    // constants (settings)
    const int ROTATE_SPEED = 45; // motor speed (0-90) for rotating the robot
    const int CORRECTION_SPEED = 10;
    const double STABLE_ANGLE_THRESHOLD = 10.0; // angle robot can turn before correction is triggered

    // constants (experimentally determined)
    const double LOADED_MAX_RPM = 113; // loaded angular velocity - 113 is no-load rpm @ 5V
    const double WHEEL_RADIUS = 1; // in cm
    const double CHASSIS_WIDTH = 4; // in cm

public:
    Engine();

    void initialize(int leftMotorPin, int rightMotorPin);

    void update();

    // state functions
    boolean isStopped();
    boolean isTurning();

    // straight movement
    void setSpeed(int s);
    void setDirection(DirectionState d);
    void stop();
    void go();
    void go(DirectionState d, int s);
    void saveSpeed();

    // turning commands
    void rotateRight(double degrees);
    void rotateLeft(double degrees);

    // correction commands
    void correctionRight();
    void correctionLeft();

    // distance tracking
    void updateDistanceTraveled(unsigned long deltaTime);
    void resetDistanceTraveled();
    double getDistanceTraveled();
    double getVelocityForSpeed(int s);

};

#endif

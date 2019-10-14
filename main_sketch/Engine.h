#ifndef ENGINE_H
#define ENGINE_H

#include <Servo.h>

enum DirectionState {
    FORWARD,
    BACKWARD,
};

enum TurningState {
    ROTATING_RIGHT,
    ROTATING_LEFT,
    TURNING_RIGHT,
    TURNING_LEFT,
    NOT_TURNING
};


class Engine {
private:
    DirectionState currentDirection;
    TurningState turningState;
    int currentSpeed;
    int savedSpeed;
    int distanceTraveled;
    Servo leftMotor;
    Servo rightMotor;
    unsigned long timeTurnCompleted;
    unsigned long timeSinceLastUpdate;

    // constants (settings)
    const int ROTATE_SPEED = 45; // motor speed (0-90) for rotating the robot

    // constants (experimentally determined)
    const double LOADED_MAX_RPM = 113; // loaded angular velocity - 113 is no-load rpm @ 5V
    const double WHEEL_RADIUS = 1; // in cm
    const double CHASSIS_WIDTH = 4; // in cm

public:
    Engine(int leftMotorPin, int rightMotorPin);

    void update();

    // movement
    void setSpeed(int s);
    void setDirection(DirectionState d);
    void stop();
    void go();
    void go(DirectionState d, int s);
    void saveSpeed();

    // turning
    void rotateRight();
    void rotateLeft();

    // distance tracking
    void updateDistanceTraveled(unsigned long deltaTime);
    void resetDistanceTraveled();
    void getDistanceTraveled();
    double getVelocityForSpeed(int s);

};

#endif

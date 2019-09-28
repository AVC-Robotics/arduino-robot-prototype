#ifndef ENGINE_H
#define ENGINE_H

#include <Servo.h>

enum DirectionState {
    FORWARD,
    BACKWARD
};


class Engine {
private:
    DirectionState currentDirection;
    int currentSpeed;
    int savedSpeed;
    Servo leftMotor;
    Servo rightMotor;
    const int ROTATE_SPEED = 45;
public:
    Engine(int leftMotorPin, int rightMotorPin);

    void setSpeed(int s);
    void setDirection(DirectionState d);
    void stop();
    void go();
    void go(DirectionState d, int s);
    void rotateRight();
    void rotateLeft();
protected:
    void saveSpeed();
};

#endif

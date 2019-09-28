#include "Engine.h"

// Engine
// This class models the robot's left and right continuous servo motors,
// allowing operations such as moving and turning.

// see Engine.h for member variables

////////////
// PUBLIC //
////////////

// CONSTRUCTOR
Engine::Engine(int leftMotorPin, int rightMotorPin) {
    // set up motors
    leftMotor.attach(leftMotorPin);
    rightMotor.attach(rightMotorPin);

    // set default values
    currentDirection = FORWARD;
    currentSpeed = 0;
    savedSpeed = 0;
}


// set angular speed
void Engine::setSpeed(int s) {
    if (s >= 0 && s <= 90) {

        // The servo motor reads values from 0-180. 0 and 180 are the
        // the fastest speeds backwards and forwards, respectively, with 0
        // being stopped.
        // Here, we will just read a speed from 0-90 and use the
        // direction member variable to determine which direction to go

        switch (currentDirection) {
            case FORWARD:
            leftMotor.write(s + 90);
            rightMotor.write(s + 90);
            break;
            case BACKWARD:
            leftMotor.write(s);
            rightMotor.write(s);
            break;
        }
    }
}


// set direction (forwards/backwards), keep speed
void Engine::setDirection(DirectionState d) {
    // don't do anything if no change
    if (d != currentDirection) {
        currentDirection = d;
        setSpeed(currentSpeed); // same speed, opposite direction
    }
}


// set speed to zero, but keep direction state
void Engine::stop() {
    saveSpeed();
    setSpeed(0);
}


// continue with previous speed and direction; should be called after stop() or saveSpeed()
void Engine::go() {
    setSpeed(savedSpeed);
}


// a function specifying direction and speed
void Engine::go(DirectionState d, int s) {
    setDirection(d);
    setSpeed(s);
}


// robot rotates right in place
void Engine::rotateRight() {
    stop();
    rightMotor.write(ROTATE_SPEED);
    leftMotor.write(ROTATE_SPEED + 90);
    go();
}


// robot rotates right in place
void Engine::rotateLeft() {
    stop();
    rightMotor.write(ROTATE_SPEED);
    leftMotor.write(ROTATE_SPEED + 90);
    go(); // continue as before
}



///////////////
// PROTECTED //
///////////////

// stores the current speed value before some operation which will change it (e.g. turning)
void Engine::saveSpeed() {
    savedSpeed = currentSpeed;
}

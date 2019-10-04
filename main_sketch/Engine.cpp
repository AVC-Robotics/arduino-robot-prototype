#include "Engine.h"

// Engine
// This class models the robot's left and right continuous servo motors,
// allowing operations such as moving and turning.

// see Engine.h for member variables

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


// MEMBER FUNCTIONS

// set angular speed
void Engine::setSpeed(int s) {
    if (s >= 0 && s <= 90) {

        // The servo motor reads values from 0-180. 0 and 180 are the
        // the fastest speeds backwards and forwards, respectively, with 90
        // being stopped.
        
        // Here, we will just read a speed from 0-90 and use the
        // currentDirection member variable to determine which direction to go
        
        // Note that the motors turn in opposite directions when mounted
        // on the chassis, so we account for that here by turning the 
        // left motor "backwards" so that it matches with the right motor

        switch (currentDirection) {
            case FORWARD:
            leftMotor.write(90 - s); // left motor is reverse of right motor
            rightMotor.write(90 + s);
            break;
            case BACKWARD:
            leftMotor.write(90 + s); // left motor is reverse of right motor
            rightMotor.write(90 - s);
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


// robot rotates right in place at a predefined speed
void Engine::rotateRight() {
    stop();
    rightMotor.write(90 + ROTATE_SPEED); // forwards
    leftMotor.write(90 + ROTATE_SPEED); // backwards
    go();
}


// robot rotates right in place
void Engine::rotateLeft() {
    stop();
    rightMotor.write(90 - ROTATE_SPEED); // backwards
    leftMotor.write(90 - ROTATE_SPEED); // forwards
    go(); // continue as before
}



///////////////
// PROTECTED //
///////////////

// stores the current speed value before some operation which will change it (e.g. turning)
void Engine::saveSpeed() {
    savedSpeed = currentSpeed;
}

#include "Engine.h"
#include <Arduino.h>

// Engine
// This class models the robot's left and right continuous servo motors,
// allowing operations such as moving and turning.

// see Engine.h for member variables


// CONSTRUCTOR
Engine::Engine() {

}


void Engine::initialize(int leftMotorPin, int rightMotorPin) {
    // set up motors
    leftMotor.attach(leftMotorPin);
    rightMotor.attach(rightMotorPin);

    // set default values
    currentDirection = FORWARD;
    turningState = NOT_TURNING;
    currentSpeed = 0;
    savedSpeed = 0;
}




///////////////////////
// GENERAL FUNCTIONS //
///////////////////////


// The update function is called by the loop() function in main. This updates
// anything that depends on time.
void Engine::update() {
    unsigned long curTime = millis(); // get current time in MS
    unsigned long deltaTime = curTime - timeSinceLastUpdate;

    // update distance
    switch (turningState) {
        case NOT_TURNING:
        updateDistanceTraveled(deltaTime);
        break;

        case ROTATING_LEFT:
        case ROTATING_RIGHT:
        // turning operation completed
        if (curTime > timeTurnCompleted) {
            turningState = NOT_TURNING;
            go(); // go straight w/ previous speed
        }
        break;

        case TURNING_LEFT:
        case TURNING_RIGHT:
        // don't update distance because we're just rotating in place
        break;
    }
}



/////////////////////
// STATE FUNCTIONS //
/////////////////////


// engine is stopped
boolean Engine::isStopped() {
    if (currentSpeed == 0) {
      return true;
    }
    else {
      return false;
    }
}


// engine is turning
boolean Engine::isTurning() {
    if (turningState != NOT_TURNING) {
        return true;
    }
    else {
        return false;
    }
}




///////////////////////
// MOVEMENT COMMANDS //
///////////////////////


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

        turningState = NOT_TURNING;
        currentSpeed = s;

        switch (currentDirection) {

            case FORWARD:
            rightMotor.write(90 + s);
            leftMotor.write(90 - s); // left motor is reverse of right motor
            break;

            case BACKWARD:
            rightMotor.write(90 - s);
            leftMotor.write(90 + s); // left motor is reverse of right motor
            break;

        }
    }
}


// set direction (forwards/backwards), keep speed
void Engine::setDirection(DirectionState d) {
    // don't do anything if no change in direction
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


// continue with previous speed and direction
void Engine::go() {
    setSpeed(savedSpeed);
}


// a function specifying direction and speed
void Engine::go(DirectionState d, int s) {
    setDirection(d);
    setSpeed(s);
}


// stores the current speed value before some operation which will change it (e.g. turning)
void Engine::saveSpeed() {
    savedSpeed = currentSpeed;
}




//////////////////////////
// ROTATE/TURN COMMANDS //
//////////////////////////


// robot rotates right in place at a predefined speed
void Engine::rotateRight(double degrees) {
    double radians = degrees * PI / 180.0;
    double arcLength = CHASSIS_WIDTH / 2.0 * radians; // arc length wheels will travel
    double deltaTime = arcLength / getVelocityForSpeed(ROTATE_SPEED);
    timeTurnCompleted = millis() + (unsigned long)deltaTime;

    turningState = ROTATING_RIGHT;
    rightMotor.write(90 + ROTATE_SPEED); // forwards
    leftMotor.write(90 + ROTATE_SPEED); // backwards
}


// robot rotates right in place
void Engine::rotateLeft(double degrees) {
    double radians = degrees * PI / 180.0;
    double arcLength = CHASSIS_WIDTH / 2.0 * radians; // arc length wheels will travel
    double deltaTime = arcLength / getVelocityForSpeed(ROTATE_SPEED);
    timeTurnCompleted = millis() + (unsigned long)deltaTime;

    turningState = ROTATING_LEFT;
    rightMotor.write(90 - ROTATE_SPEED); // backwards
    leftMotor.write(90 - ROTATE_SPEED); // forwards
}




////////////////////////
// DISTANCE FUNCTIONS //
////////////////////////


// called by update function to get latest distance
void Engine::updateDistanceTraveled(unsigned long deltaTime) {
    // deltaD = v*deltaT
    distanceTraveled += getVelocityForSpeed(currentSpeed) * deltaTime;
}


// reset distance traveled to 0
void Engine::resetDistanceTraveled() {
    distanceTraveled = 0;
}


// return distance traveled since last reset
double Engine::getDistanceTraveled() {
    return distanceTraveled;
}


// return a linear velocity (cm/s) for a given speed
double Engine::getVelocityForSpeed(int s) {
    // convert speed to rpm
    double rpm = (double)(map(s, 0, 90, 0, LOADED_MAX_RPM));
    // convert rotations per minute to radians per second
    double rps = 2.0 * rpm * PI / 60.0;
    double velocity = rps * WHEEL_RADIUS;
    return velocity;
}

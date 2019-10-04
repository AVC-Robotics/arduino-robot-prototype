#include "Sensor.h"
#include <Arduino.h>
// Sensor 
// This class models a four-pin HC-SR04 ultrasonic sensor,
// which consists of power and ground pins, plus two control pins:
// - a trigger pin for sending an audio signal
// - an echo pin for picking up the signal

// see Sensor.h for member variables

// CONSTRUCTOR
Sensor::Sensor(int t, int e) {
    triggerPin = t;
    echoPin = e;
}

// MEMBER FUNCTIONS
double Sensor::getDistance() {
    // using code created by Rui Santos, https://randomnerdtutorials.com
    
    // The sensor is triggered by a HIGH pulse of 10 or more microseconds.
    // Give a short LOW pulse beforehand to ensure a clean HIGH pulse:
    digitalWrite(triggerPin, LOW);
    delayMicroseconds(5);
    digitalWrite(triggerPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(triggerPin, LOW);

    // Read the signal from the sensor: a HIGH pulse whose
    // duration is the time (in microseconds) from the sending
    // of the ping to the reception of its echo off of an object.
    pinMode(triggerPin, INPUT);
    double duration = pulseIn(echoPin, HIGH);

    // Convert the time into a distance
    double cm = (duration/2.0) / 29.1;     // Divide by 29.1 or multiply by 0.0343

    return cm;
}

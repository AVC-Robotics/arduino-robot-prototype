#include "Sensor.h"
#include <Arduino.h>
// Sensor
// This class models a four-pin HC-SR04 ultrasonic sensor,
// which consists of power and ground pins, plus two control pins:
// - a trigger pin for sending an audio signal
// - an echo pin for picking up the signal

// see Sensor.h for member variables

// CONSTRUCTOR
Sensor::Sensor() {
}


void Sensor::initialize(int t, int e) {
    trigPin = t;
    echoPin = e;
    pinMode(trigPin, OUTPUT);
    pinMode(echoPin, INPUT);
}

// MEMBER FUNCTIONS
double Sensor::getDistance() {
    long duration;
    double cm, inches;
    // The sensor is triggered by a HIGH pulse of 10 or more microseconds.
    // Give a short LOW pulse beforehand to ensure a clean HIGH pulse:
    digitalWrite(trigPin, LOW);
    delayMicroseconds(5);
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);

    // Read the signal from the sensor: a HIGH pulse whose
    // duration is the time (in microseconds) from the sending
    // of the ping to the reception of its echo off of an object.
    pinMode(echoPin, INPUT);
    duration = pulseIn(echoPin, HIGH);

    // Convert the time into a distance
    cm = (duration/2.0) / 29.1;     // Divide by 29.1 or multiply by 0.0343
    inches = (duration/2.0) / 74.0;   // Divide by 74 or multiply by 0.0135

    return cm;
}

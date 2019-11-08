#include "Engine.h"
#include "Sensor.h"
#include "Gyro.h"

#include <Servo.h>

Engine engine = Engine();
Sensor sensor = Sensor();

void setup() {
    Serial.begin(9600);
    engine.initialize(7,8); // left,right
    sensor.initialize(12,13); // trig,echo

    engine.go(FORWARD, 45);
}

void loop() {
    engine.update();

    // stop when obstacle detected
    if (engine.isStopped()) {
        if (sensor.getDistance() > 10.0) {
            engine.go(); // return to previous speed
        }
    }
    else if (!engine.isStopped() && sensor.getDistance() < 10.0) {
        engine.stop();
    }
}

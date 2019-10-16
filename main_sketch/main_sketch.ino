#include "Engine.h"
#include "Sensor.h"

Engine engine = Engine(7,8); // left,right
Sensor sensor = Sensor(12,13); // trig,echo

void setup() {
    engine.go(FORWARD, 50);
}

void loop() {
    if (engine.isStopped()) {
        if (sensor.getDistance() > 10.0) {
            engine.go(); // return to previous speed
        }
    }
    else if (!engine.isStopped && sensor.getDistance() < 10.0) {
        engine.stop();
        engine.rotateRight(90);
    }
}

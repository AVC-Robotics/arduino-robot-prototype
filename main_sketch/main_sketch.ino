#include "Engine.h"
#include "Sensor.h"

Engine engine = Engine(9,10);
Sensor sensor = Sensor(11,12);

void setup() {
  Engine engine = Engine(9,10);
  Sensor sensor = Sensor(11,12);

  engine.go(FORWARD, 10);
}

void loop() {
   if (sensor.getDistance() < 100.0) {
       engine.stop();
   }
   else {
       engine.go();
   }
}

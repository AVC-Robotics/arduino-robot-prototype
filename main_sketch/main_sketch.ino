#include "Engine.h"
#include "Sensor.h"

Engine engine = Engine(9,10);
Sensor sensor = Sensor(11,12);

void setup() {
  Engine engine = Engine(9,10);
  engine.go(FORWARD, 45);
}

void loop() {
  
}

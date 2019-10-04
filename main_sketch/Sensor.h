#ifndef SENSOR_H
#define SENSOR_H


class Sensor {
private:
    int triggerPin;
    int echoPin;

public:
    Sensor(int triggerPin, int echoPin);

    double getDistance();
};

#endif

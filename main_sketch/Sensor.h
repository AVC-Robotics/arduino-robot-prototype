#ifndef SENSOR_H
#define SENSOR_H


class Sensor {
private:
    int trigPin;
    int echoPin;

public:
    Sensor();

    void initialize(int trigPin, int echoPin);

    double getDistance();
};

#endif

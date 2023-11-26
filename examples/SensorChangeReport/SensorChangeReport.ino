#include <Arduino.h>
#include <EasIno.h>
#include <SerialCom.h>

int DIGITAL_PIN = 7;  // pushbutton
int digital_val = 0;
long start_time = 0;  // avoid bounces

int ANALOG_PIN = A0;  // potentiometer
int analog_val = 0;
int threshold = 10;

EasIno* easino;
DataCom data_received;

void setup() {
    easino = new SerialCom(115200);
    easino->start();
    pinMode(DIGITAL_PIN, INPUT);
}

void loop() {
    int digital_val_updated = digitalRead(DIGITAL_PIN);
    if (digital_val_updated != digital_val && millis() - start_time > 100) {
        digital_val = digital_val_updated;
        start_time = millis();

        DataCom data = DataCom();
        data.setOperation("BUTTON");
        data.setArgument(0, digital_val);
        easino->send(data);
    }

    data_received = easino->receive();
    if (strcmp(data_received.operation, "THRESHOLD") == 0) {
        threshold = atoi(data_received.args[0]);

        DataCom data = DataCom();
        data.setOperation("THRESHOLD");
        data.setArgument(0, threshold);
        easino->send(data);
        delay(100);
    }

    int analog_val_updated = analogRead(ANALOG_PIN);
    if (abs(analog_val_updated - analog_val) > threshold) {
        analog_val = analog_val_updated;

        DataCom data = DataCom();
        data.setOperation("POTENTIOMETER");
        data.setArgument(0, analog_val);
        data.setArgument(1, threshold);
        easino->send(data);
    }
}

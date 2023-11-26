#include <Arduino.h>
#include <EasIno.h>
#include <SerialCom.h>

EasIno* easino;
DataCom data;

void setup() {
    easino = new SerialCom(115200);
    easino->start();
    pinMode(13, OUTPUT);
}

void loop() {
    data = easino->receive();

    if (strcmp(data.operation, "LED13") == 0) {
        DataCom data_out;
        if (strcmp(data.args[0], "1") == 0) {
            digitalWrite(13, HIGH);
            data_out.builder("LED13;1;", ';');
        } else if (strcmp(data.args[0], "0") == 0) {
            digitalWrite(13, LOW);
            data_out.builder("LED13;0;", ';');
        } else {
            data_out.builder("LED13;-1;", ';');
        }
        easino->send(data_out);
    }
}

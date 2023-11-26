#include <Arduino.h>
#include <EasIno.h>
#include <SerialCom.h>

EasIno *easino;
DataCom data;

void setup() {
    easino = new SerialCom(115200);
    easino->start();
}

void loop() {
    data = easino->receive();

    delay(2000);

    DataCom data_out = DataCom();
    data_out.builder("LED13;1;", ';');
    easino->send(data_out);

    delay(2000);

    data_out = DataCom();
    data_out.builder("LED13;0;", ';');
    easino->send(data_out);
}

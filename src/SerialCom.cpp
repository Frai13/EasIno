#include "SerialCom.h"

const int SerialCom::max_buffer_serial_byte = 64;
const int SerialCom::max_time_between_messages = 100;

SerialCom::SerialCom(long _baud_rate) {
    data_buffer[0] = '\0';
    baud_rate = _baud_rate;
}

void SerialCom::start() {
  Serial.begin(baud_rate);
}

void SerialCom::stop() {
  Serial.end();
}

void SerialCom::derived_send(const char* line) {
    if (strlen(line) != 0) {
        int i = 0;
        while (i * max_buffer_serial_byte <= strlen(line)) {
            if (Serial.availableForWrite() > 0) {
                int last_index = (i + 1) * max_buffer_serial_byte;
                if ((i + 1) * max_buffer_serial_byte > strlen(line)) {
                    last_index = strlen(line);
                }
                char substring[FULL_LENGTH];
                substring[0] = '\0';
                data.subStr(line, i * max_buffer_serial_byte,
                            last_index - (i * max_buffer_serial_byte), substring);
                Serial.print(substring);
                i++;
            }
        }
    }
}

void SerialCom::derived_receive(char* line) {
    while (Serial.available() > 0) {
        char incomingByte = Serial.read();
        strncat(data_buffer, &incomingByte, 1);
        if (data.indexOfCharArray(data_buffer, DataCom::tail, 0) > 0) {
            memcpy(line, data_buffer, strlen(data_buffer) + 1);
            data_buffer[0] = '\0';
            return;
        }
        start_time = millis();
    }

    unsigned long current_time = millis();
    if (strlen(data_buffer) > 0 &&
        ((current_time - start_time) >
             SerialCom::max_time_between_messages  // If time elapsed > 100ms
         || current_time < start_time)) {          // If current time has been overflowed
        data_buffer[0] = '\0';
    }

    return;
}
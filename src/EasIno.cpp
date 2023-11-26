#include "EasIno.h"

#include <Arduino.h>

void EasIno::send(DataCom data) {
    char line[FULL_LENGTH];
    line[0] = '\0';
    data.toString(line);
    derived_send(line);
}

DataCom EasIno::receive() {
    char line[FULL_LENGTH];
    line[0] = '\0';
    derived_receive(line);

    DataCom data = DataCom(line);
    DataCom data_out = manage_builtin_message(data);

    if (strlen(data_out.operation) > 0) {
        send(data_out);
        return DataCom();
    } else {
        return data;
    }
}

DataCom EasIno::manage_builtin_message(DataCom data) {
    DataCom data_out;

    if (strcmp(data.operation, "VERSION") == 0) {
        memcpy(data_out.operation, "VERSION", strlen("VERSION") + 1);
        memcpy(data_out.args[0], VERSION, strlen(VERSION) + 1);
    } else if (strcmp(data.operation, "PING") == 0) {
        memcpy(data_out.operation, "PING", strlen("PING") + 1);
    }

    return data_out;
}

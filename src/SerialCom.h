
#ifndef SERIALCOM_H
#define SERIALCOM_H

#include <Arduino.h>

#include "DataCom.h"
#include "EasIno.h"

class SerialCom : public EasIno {
   public:
    SerialCom(long);

   private:
    const static int max_buffer_serial_byte;
    const static int max_time_between_messages;

    char data_buffer[FULL_LENGTH];
    long baud_rate;
    unsigned long start_time;

    virtual void start();
    virtual void stop();
    virtual void derived_send(const char* data);
    virtual void derived_receive(char* line);
};

#endif
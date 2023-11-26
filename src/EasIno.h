
#ifndef EASINO_H
#define EASINO_H

#include "DataCom.h"

#define VERSION "v1.0.0"

class EasIno {
   private:
    virtual void derived_send(const char* data) = 0;
    virtual void derived_receive(char* line) = 0;
    DataCom manage_builtin_message(DataCom);

   public:
    DataCom data;

    EasIno() {}
    virtual void start() = 0;
    virtual void stop() = 0;
    void send(DataCom data);
    DataCom receive();
};

#endif
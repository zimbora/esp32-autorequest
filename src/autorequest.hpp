#ifndef AUTOREQUEST_H
#define AUTOREQUEST_H

#include "Arduino.h"

#ifndef UNITTEST
#include <ArduinoJson.h>
#include <Time.h>
#include <TimeLib.h>
//#include "../log/logging.h"
//#include "../settings/settings.h"

#else

  #include <iostream>
  //#include "../libraries/nlohmann/json.hpp"
  #define String std::string
#endif

class AUTOREQUEST {

  public:
    int16_t time_offset = 0;
    bool use_local_time = false;
    #ifndef UNITTEST
    HardwareSerial* serial = &Serial;
    AUTOREQUEST(HardwareSerial* serial_port, bool local_time = false){
      serial = serial_port;
      use_local_time = local_time;
    };
    #endif
    AUTOREQUEST(){};
    AUTOREQUEST(bool local_time){
      use_local_time = local_time;
    };
    void set_time_offset(int16_t offset){
      time_offset = offset;
    };

    // check if it is time to execute the task associated to ref,
    // int that case call execute callback
    bool check(String ref,bool(*execute)(String ref));
    // check if it is time to execute task associated to ref
    bool check(String ref);

    //  @period - seconds
    bool add(String ref, uint32_t period);
    void list();
    JsonObject get(String ref);
  private:
    #ifdef UNITTEST
    uint32_t now();
    #endif
    uint32_t get_aligned_hour(uint32_t);
    void log(String text);
};

#endif

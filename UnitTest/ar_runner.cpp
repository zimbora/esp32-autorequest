// Your First C++ Program

#include <stdint.h>
#include <stdio.h>
#include <iostream>

//#include "./libraries/nlohmann/json.hpp"
//#include "./Arduino.h"

#include "./tmp/autorequest.hpp"
#include "./libraries/output.h"


#define String std::string
using json = nlohmann::json;

uint8_t type_arr[] = {
  byte_type,
  uint8_type,
  int8_type ,
  uint16be_type,
  uint16le_type,
  int16be_type,
  int16le_type,
  uint32be_type,
  uint32le_type,
  int32be_type,
  int32le_type,
  floatbe_type,
  floatle_type,
  hex_arr,
  char_arr,
  index_itron
};

extern json doc_ar;

AUTOREQUEST Ar;

// testing null structs
bool ar_test1(){
  // Null json
  print_colour_text("\n\nTest1 - null JSON!","white");

  std::string refs[] = {"p1","tamb","capacity"};
  uint32_t period[] = {300,900,21600};
  uint32_t timeout = 0;

  uint8_t i = 0;
  while(i<sizeof(period)/(sizeof(uint32_t))){

    Ar.add(refs[i],period[i]);
    timeout = doc_ar[refs[i]]["timeout"];

    std::cout << "\n\n" << doc_ar[refs[i]] << "\n";
    if( (timeout % period[i]) != 0){
      print_colour_text("Test1 - failed (timeout not divisibly by period)","red");
      return false;
    }else
      print_colour_text("Test1 - passed (hour aligned)","green");

    if(!Ar.check("p1"))
      print_colour_text("Test1 - passed (Timeout well calculated)","green");
    else{
      print_colour_text("Test1 - failed (Timeout too low or too high)","red");
      return false;
    }

    i++;
  }

  print_colour_text("\n --- Test1 ended ---\n\n","white");
  return true;
}


int main() {
    #ifndef UNITTEST
    print_colour_text("Hello World!","red");
    #else
    print_colour_text("\n\n","white");
    print_colour_text("--- --- ---","blue");
    print_colour_text("Hello Unit Test!","blue");
    try{
      if(!ar_test1())
        print_colour_text("\n --- Test1 Error - routines tests have been suspended ---\n\n","red");
      //printf("\ncheck function called: %d times \n",Alarm.check_counter());
    }catch(std::invalid_argument& e){
      std::cerr << e.what() << std::endl;
    }catch(...){
      print_colour_text("!! Exception Ocurred !! - terminating process ","red");
      return -1;
    }
    print_colour_text("Test terminated","blue");
    #endif
    return 0;
}

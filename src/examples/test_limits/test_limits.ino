
#include "autorequest.hpp"

AUTOREQUEST Ar(&Serial);
//AUTOREQUEST Ar;

String ref = "sensor1";
bool (*callback)(String);
bool calledInAutorequest(String ref){
  Serial.println("executing task for ref: "+ref);
  return true;
}

void setup() {
  // put your setup code here, to run once:

  Serial.begin(115200);

  Serial.printf("now: %lu \n",now());

  struct tm timeinfo;
  int y = 122 + 1900;
  int mo = 11;
  int d = 28;
  int h = 11;
  int m = 33;
  int s = 0;

  setTime(h, m, s, d, mo, y);

  uint8_t i = 0;
  while(i<50){
    if(!Ar.add("sensor"+String(i),random(15,900))){
      Serial.println("!! autorequest "+String(i)+" not added");
    }
    i++;
  }

}

void loop() {
  // put your main code here, to run repeatedly:

  if(Ar.check(ref,calledInAutorequest)){
    Serial.printf("now: %lu \n",now());
    Serial.println(ref+" execute action..\n");
  }

  delay(3000);
}


#include "autorequest.hpp"

AUTOREQUEST Ar(&Serial);
//AUTOREQUEST Ar;

String ref1 = "sensor1";
String ref2 = "sensor2";
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

  if(!Ar.add(ref1,15)){
    Serial.println("!! autorequest not added");
  }

}

void loop() {
  // put your main code here, to run repeatedly:

  if(Ar.check(ref1)){
    Serial.printf("now: %lu \n",now());
    Serial.println(ref1+" execute action..\n");
  }

  if(Ar.check(ref2)){
    Serial.printf("now: %lu \n",now());
    Serial.println(ref2+" execute action..\n");
  }

  delay(3000);
}

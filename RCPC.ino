#include "HID-Project.h"

#define CHCOUNT 5
#define LED 8
#define RC_LOW 1050
#define RC_HIGH 1900

typedef struct {
  int rc_val;
  int16_t hid_val;
  int8_t hid_val_8;
  uint8_t pin;
} rc_chanel;

rc_chanel chlist[CHCOUNT];
int blik;

void setup() {
  Gamepad.begin();

  pinMode(9,INPUT);
  pinMode(10,INPUT);
  pinMode(14,INPUT);
  pinMode(15,INPUT);
  pinMode(16,INPUT);

  pinMode(LED, OUTPUT);
  
  //Serial.begin(9600);

  chlist[0].pin = 15;
  chlist[1].pin = 16;
  chlist[2].pin = 10;
  chlist[3].pin = 14;
  chlist[4].pin = 9;

  digitalWrite(8, HIGH);
  blik = 0;
}

void loop() {
  int i;

  for(i = 0; i < CHCOUNT; i++){
     chlist[i].rc_val = pulseIn(chlist[i].pin, HIGH);
     
     if(chlist[i].rc_val < RC_LOW) chlist[i].rc_val = RC_LOW;
     if(chlist[i].rc_val > RC_HIGH) chlist[i].rc_val = RC_HIGH;
     
     chlist[i].hid_val = map(chlist[i].rc_val, RC_LOW, RC_HIGH, -32760, 32760);
     chlist[i].hid_val_8 = map(chlist[i].rc_val, RC_LOW, RC_HIGH, -127, 127);
  }

  /*
  Serial.print(chlist[4].rc_val);
  Serial.print(" > ");
  Serial.print(chlist[4].hid_val_8);
  Serial.println("");
  delay(100);
  */

  // zapis do joye
  Gamepad.xAxis(chlist[3].hid_val);
  Gamepad.yAxis(chlist[0].hid_val);
  Gamepad.rxAxis(chlist[1].hid_val);
  Gamepad.ryAxis(chlist[2].hid_val);  
  Gamepad.zAxis(chlist[4].hid_val_8);  
  
  Gamepad.write();

  // co 10 cyklu bliknuti
  if(blik == 5){
    digitalWrite(LED, LOW);
  }
  if(blik == 10){
    digitalWrite(LED, HIGH);
    blik = 0;
  }
  blik++;
}

//#include <I2C.h>
#include <Wire.h>
#include "AB1805.h"

AB1805 timer;

void setup() {
   
    pinMode(7, OUTPUT);
    digitalWrite(7, HIGH);
    delay(1000);

    timer.begin();
    timer.set_datetime(0x16, 0x01, 0x12, 0x02, 0x16, 0x56, 0x00); //year, month, date, week_day, hour, minute, second (2016, Jan 12, Tuesday, 16:56:00)

    Serial.begin(9600);
}

void loop(){
  
    delay(1000);
 
    Serial.println(timer.get_date_string());
}

#include <Arduino.h>

#include "RTClib.h"

RTC_DS3231 rtc;
char daysOfTheWeek[7][12] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};

void setup_rtc() {
  if (! rtc.begin()) {
    Serial.println("Couldn't find RTC");
    Serial.flush();
    abort();
  }

  if (rtc.lostPower()) {
    Serial.println("-----------------------------------");
    Serial.println("RTC lost power, let's set the time!");
    Serial.println("-----------------------------------");
    delay(2000);
    // When time needs to be set on a new device, or after a power loss, the
    // following line sets the RTC to the date & time this sketch was compiled
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
    // This line sets the RTC with an explicit date & time, for example to set
    // January 21, 2014 at 3am you would call:
    // rtc.adjust(DateTime(2014, 1, 21, 3, 0, 0));
  }
}

void loop_rtc() {
  DateTime now = rtc.now();
  Serial.printf("%04d/%02d/%02d (%s) %02d:%02d:%02d\n",
    now.year(), now.month(), now.day(), daysOfTheWeek[now.dayOfTheWeek()],
    now.hour(),now.minute(),now.second() );
  Serial.print("Temperature: ");
  Serial.print(32.0 + 1.8*rtc.getTemperature());
  Serial.println(" F");

  Serial.println();
}

void blink(int count) {
  for(int i=0;i<max(0,count);i++) {
    digitalWrite(LED_BUILTIN,LOW);    delay(100);
    digitalWrite(LED_BUILTIN,HIGH);   delay(100);
  }
  return;
}
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial.println("\n");
  Serial.println("rts_ds3231 test");
  pinMode(LED_BUILTIN,OUTPUT); 
  setup_rtc();
}


void loop() {
  // put your main code here, to run repeatedly:
  blink(1);
  loop_rtc();
  delay(3000);
  setup_rtc();
}
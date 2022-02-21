#include <LapX9C10X.h>

/*
  GITMRG Nova Custom Trolling Motor Driver

  Interfaces with PWM Module through digital potentiometer
  PWM Module is interfaced with NV-series 8-speed trolling motor.  

  v0.1
  modified 20 FEB 2022
  by Sean Fish

  Roadmap
   - Version 0: Arduino Nano - Serial Commuication
   - Version 1: Raspberry Pi Pico - micro-ROS

  Resources
  https://stackoverflow.com/questions/6504211/is-it-possible-to-include-a-library-from-another-library-using-the-arduino-ide
*/

// PINS -------------------------------------------------------------
const int THROT_CS_PIN = 5;
const int THROT_UD_PIN = 6;
const int THROT_INC_PIN = 7;

// VARS -------------------------------------------------------------
const int THROT_RESISTANCE = LAPX9C10X_X9C104;
const int throttleMax = 50;
int direction = 0; // 0 - OFF | 1 - FWD | 2 - BWD


// DEVICES ----------------------------------------------------------
LapX9C10X throttle(THROT_INC_PIN, THROT_UD_PIN, THROT_CS_PIN, THROT_RESISTANCE);

void setup() {
  Serial.begin(9600);
  Serial.println("MOTOR INIT");
  throttle.begin(-1); // Min resistance
  delay(5000);
}

void loop() {
  // Demo test loop
   int counter;
   for(counter = 0; counter < throttleMax; counter++) {
     Serial.print("Inc: counter = ");
     Serial.print(counter);
     throttle.set(counter);
     Serial.print(", new resistance = ");
     Serial.print(throttle.getK());
     Serial.println("KOhms");
     delay(100);
   }
   for(counter = throttleMax - 1; counter >= 0; counter--) {
     Serial.print("Decc: counter = ");
     Serial.print(counter);
     throttle.set(counter);
     Serial.print(", new resistance = ");
     Serial.print(throttle.getK());
     Serial.println("KOhms");
     delay(100);
   }

  // Check signal for motor command

  // Set motor to command value


}
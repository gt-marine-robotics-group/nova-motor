#include <LapX9C10X.h>

/*
  GITMRG Nova Custom Trolling Motor Driver

  Interfaces with PWM Module through digital potentiometer
  PWM Module is interfaced with NV-series 8-speed trolling motor.  

  v0.1
  modified 20 FEB 2022
  by Sean Fish, Alvaro Pelaez

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
const int DIR_SEL0_PIN = 2;
const int DIR_SEL1_PIN = 3;


// VARS -------------------------------------------------------------
const int THROT_RESISTANCE = LAPX9C10X_X9C104;
const int throttleMax = 50;
int direction = 0; // 0 - OFF | 1 - FWD | 2 - BWD
int m_signal=0;

// DEVICES ----------------------------------------------------------
LapX9C10X throttle(THROT_INC_PIN, THROT_UD_PIN, THROT_CS_PIN, THROT_RESISTANCE);

void setup() {
  Serial.begin(9600);
  pinMode(DIR_SEL0_PIN, OUTPUT);
  pinMode(DIR_SEL1_PIN, OUTPUT);
  Serial.println("NOVA MOTOR STARTING...");
  throttle.begin(-1); // Min resistance
  delay(5000);

  Serial.println("==================================================");
  Serial.println("============ NOVA MOTOR INIT COMPLETE ============");
  Serial.println("==================================================");
}

void set_direction(int d) {
  if (d==0){ //OFF
    digitalWrite(DIR_SEL0_PIN, LOW);
    digitalWrite(DIR_SEL1_PIN, LOW);
    Serial.println("DIRECTION OFF");
  }
  else if (d==1){ //FWD
    digitalWrite(DIR_SEL0_PIN, LOW);
    digitalWrite(DIR_SEL1_PIN, HIGH);
    Serial.println("DIRECTION 1");
  }
  else if (d==2){ //BWD
    digitalWrite(DIR_SEL0_PIN, HIGH);
    digitalWrite(DIR_SEL1_PIN, LOW);
    Serial.println("DIRECTION 2");
  }
}

void loop() {
  // Demo test loop
  int counter;
//  direction=2;   //BWD
//  set_direction(direction);
  
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
  
 //Set motor to command value
  if (m_signal<0) {
    direction=2;   //BWD
    set_direction(direction);
    //throttle.set(abs(m_signal));
  }
  else if (m_signal==0) {
    direction=0;   //OFF
    set_direction(direction);
    //throttle.set(0);
  }
  else {
    direction=1;   //FWD
    set_direction(direction);
    //throttle.set(m_signal);
  }
  m_signal = ((m_signal + 1 + 1) % 3) - 1;

}

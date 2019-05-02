#include <SoftwareSerial.h>

#define txPin 4 // pin 4 connects to smcSerial RX
#define rxPin 3 // pin 4 connects to smcSerial RX

#define MOTOR_1 9
#define MOTOR_2 10
#define MOTOR_3 11

int i = 0;
int motorRaw = 0;


SoftwareSerial smcSerial1 = SoftwareSerial(rxPin, MOTOR_1);
SoftwareSerial smcSerial2 = SoftwareSerial(rxPin, MOTOR_2);
SoftwareSerial smcSerial3 = SoftwareSerial(rxPin, MOTOR_3);

// required to allow motors to move
// must be called when controller restarts and after any error
void exitSafeStart(){
  smcSerial1.write(0x83);
  smcSerial2.write(0x83);
  smcSerial3.write(0x83);
}
// speed should be a number from -3200 to 3200

void setMotorSpeed1(int speed){
  if (speed < 0){
    smcSerial1.write(0x86); // motor reverse command
    speed = -speed; // make speed positive
  }
  else {
    smcSerial1.write(0x85); // motor forward command
  }
  smcSerial1.write(speed & 0x1F);
  smcSerial1.write(speed >> 5);
}


void setMotorSpeed2(int speed){
  if (speed < 0){
    smcSerial2.write(0x86); // motor reverse command
    speed = -speed; // make speed positive
  }
  else {
    smcSerial2.write(0x85); // motor forward command
  }
  smcSerial2.write(speed & 0x1F);
  smcSerial2.write(speed >> 5);
}

void setMotorSpeed3(int speed){
  if (speed < 0){
    smcSerial3.write(0x86); // motor reverse command
    speed = -speed; // make speed positive
  }
  else {
    smcSerial3.write(0x85); // motor forward command
  }
  smcSerial3.write(speed & 0x1F);
  smcSerial3.write(speed >> 5);
}


void setup(){
  Serial.begin(9600);
  Serial.print("READY");
  // initialize software serial object with baud rate of 19.2 kbps
  smcSerial1.begin(19200);
  smcSerial2.begin(19200);
  smcSerial3.begin(19200);
  // the Simple Motor Controller must be running for at least 1 ms
  // before we try to send serial data, so we delay here for 5 ms
  delay(5);
  // if the Simple Motor Controller has automatic baud detection
  // enabled, we first need to send it the byte 0xAA (170 in decimal)
  // so that it can learn the baud rate
  smcSerial1.write(0xAA); // send baud-indicator byte
  smcSerial2.write(0xAA); // send baud-indicator byte
  smcSerial3.write(0xAA); // send baud-indicator byte
  // next we need to send the Exit Safe Start command, which
  // clears the safe-start violation and lets the motor run
  exitSafeStart(); // clear the safe-start violation and let the motor run
}
void loop(){
  if (Serial.available()){
    if (i < 4) i++;
    else i = 0;
    motorRaw = Serial.read();
    Serial.println(motorRaw);
    if (i == 1){
      setMotorSpeed1(motorRaw);
      Serial.print("Motor 1: ");
      Serial.println(motorRaw);
    }
    else if (i == 2){
      setMotorSpeed2(motorRaw);
      Serial.print("Motor 2: ");
      Serial.println(motorRaw);
    }
    else if (i == 3){
      setMotorSpeed3(motorRaw);
      Serial.print("Motor 3: ");
      Serial.println(motorRaw);
      i = 0;
    }
  }
}

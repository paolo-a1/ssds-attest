#define MOTOR_1 9
#define MOTOR_2 10
#define MOTOR_3 11

int i = 0;
int motorRaw = 0;

byte valveCommandRaw;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial.println("MOTOR CONTROLLER");
  //Serial.println("Attitude Testbed and Spacecraft Flight Simulator");
  //Serial.println();
  //Serial.println("CORNELL UNIVERSITY");
  //Serial.println("Copyright (C) 2019 by Space Systems Design Studio");
  //Serial.println();
  //Serial.println("Written by Paolo Arguelles (M.Eng. ECE '19");
  //Serial.println();
}

void loop() {
  if (Serial.available()){
    if (i < 4) i++;
    else i = 0;
    motorRaw = Serial.read();
    //Serial.println(motorRaw);
    if (i == 1){
      analogWrite(MOTOR_1, motorRaw);
      Serial.print("Motor 1: ");
      Serial.println(motorRaw);
    }
    else if (i == 2){
      analogWrite(MOTOR_2, motorRaw);
      Serial.print("Motor 2: ");
      Serial.println(motorRaw);
    }
    else if (i == 3){
      analogWrite(MOTOR_3, motorRaw);
      Serial.print("Motor 3: ");
      Serial.println(motorRaw);
      i = 0;
    }
  }
}

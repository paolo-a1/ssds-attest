#define VALVE_1 7
#define VALVE_2 8
#define VALVE_3 9
#define VALVE_4 10
#define VALVE_5 11
#define VALVE_6 12

byte valveCommandRaw;

void setup() {
  // Set up both ports at 9600 baud. This value is most important
  // for the XBee. Make sure the baud rate matches the config
  // setting of your XBee.
  Serial.begin(9600);
  Serial.println("VALVE CONTROLLER");
  //Serial.println("Attitude Testbed and Spacecraft Flight Simulator");
  //Serial.println();
  //Serial.println("CORNELL UNIVERSITY");
  //Serial.println("Copyright (C) 2019 by Space Systems Design Studio");
  //Serial.println();
  //Serial.println("Written by Paolo Arguelles (ECE '19)");
  //Serial.println();
  
  pinMode(13, OUTPUT);
  pinMode(VALVE_6, OUTPUT);
  pinMode(VALVE_5, OUTPUT);
  pinMode(VALVE_4, OUTPUT);
  pinMode(VALVE_3, OUTPUT);
  pinMode(VALVE_2, OUTPUT);
  pinMode(VALVE_1, OUTPUT);
}

void loop() {
  if (Serial.available()) { // If data comes in from serial monitor, send it out to XBee
    valveCommandRaw = Serial.read();    // read one character from the I2C
    Serial.println(valveCommandRaw);
  
    char valveCommandArray[9] = {0};
    valveCommandRaw += 128;
    itoa(valveCommandRaw, valveCommandArray, 2);
    char* string = valveCommandArray + 2; //get rid of the most significant digit as you only want 7 bits
    for(byte i = 0; i < 7; i++){
      digitalWrite(8+i,string[i] - '0');
    }
    Serial.println(valveCommandArray);
  }
}

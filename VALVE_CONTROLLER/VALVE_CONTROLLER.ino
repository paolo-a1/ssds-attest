#define VALVE_1 7
#define VALVE_2 8
#define VALVE_3 9
#define VALVE_4 10
#define VALVE_5 11
#define VALVE_6 12
#define LOW_PRESSURE_PIN  4

byte valveCommandRaw;

const int analogInPin = A0;  // Analog input pin that the potentiometer is attached to
int rawPressure = 0;        // value read from the pot
int psi = 0;        // value output to the PWM (analog out)

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
  pinMode(LOW_PRESSURE_PIN, OUTPUT);
}

void closeValves(){
  digitalWrite(VALVE_1, LOW);
  digitalWrite(VALVE_2, LOW);
  digitalWrite(VALVE_3, LOW);
  digitalWrite(VALVE_4, LOW);
  digitalWrite(VALVE_5, LOW);
  digitalWrite(VALVE_6, LOW);
}

void flushSerial(){
  while(Serial.available())
    Serial.read();
}

void loop() {
  rawPressure = analogRead(analogInPin);
  psi = map(rawPressure, 245, 1023, 0, 250);
  if (psi <= 140){
    //Serial.println("1");
    digitalWrite(LOW_PRESSURE_PIN, HIGH);
  }
  else{
    //Serial.println("0");
    digitalWrite(LOW_PRESSURE_PIN, LOW);
  }
  if (Serial.available()) { // If data comes in from serial monitor, send it out to XBee
    valveCommandRaw = Serial.read();    // read one character from the I2C
    char valveCommandArray[9] = {0};
    valveCommandRaw += 128;
    itoa(valveCommandRaw, valveCommandArray, 2);
    char* string = valveCommandArray + 2; //get rid of the most significant digit as you only want 7 bits
    for(byte i = 0; i < 7; i++){
      digitalWrite(7+i,string[i] - '0');
    }
    delay(100);
    closeValves();
  }
}

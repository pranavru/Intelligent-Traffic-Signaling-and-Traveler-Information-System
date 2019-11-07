#include <Wire.h>

#define noOfIRS 3
#define noOfUS 2
#define noOfSensors 5
#define SLAVE_ADDRESS 12
#define noOfLanes 3


int ct = 0, ctHigh = 15750, ctLow = 15000;
int CountData[noOfSensors];
int UStrigPin[noOfUS];
int USechoPin[noOfUS];
boolean SensorValue[noOfSensors];
int cycleTime = 32000;
int Sensor[noOfSensors];
int SectionStartTime = 16000;
long duration = 0;
int distance = 0;
int rangeUSensor = 25;
String sendData = "";
String receiveData = "";
int laneTime = 0;
int cop = -1, rop = -1;

void setup() {
  USechoPin[0] = 7;
  USechoPin[1] = 9;
  UStrigPin[0] = 8;
  UStrigPin[1] = 10;
  Sensor[0] = USechoPin[0];
  Sensor[1] = USechoPin[1];
  Sensor[2] = 6;
  Sensor[3] = 5;
  Sensor[4] = 4;

  for (int i = 0; i < noOfSensors; i++) {
    pinMode(Sensor[i], INPUT);
  }
  for (int i = 0; i < noOfUS; i++) {
    pinMode(UStrigPin[i], OUTPUT);                       // Sets the trigPin as an Output2
  }

  Serial.begin(9600);

  Wire.begin(SLAVE_ADDRESS);                        // MASTER-SLAVE SET_UP
  Wire.onRequest(sendToMaster); // register event
  Wire.onReceive(receiveEvent);

}

void loop() {
  if (ct >= cycleTime) {                            //Reset the Timer
    ct = 0;
    rop = -1; cop = -1;
    for (int i = 0; i < noOfSensors; i++) {
      CountData[i] = 0;
      SensorValue[i] = false;
    }
  }
  
  if (ct >= ctLow && ct <= ctHigh) {                 //Data Received From US Sensor
    Serial.print("Current Time : ");
    Serial.println(ct);
    while (ct <= ctHigh) {
      int i = 0;
      while (i < noOfUS) {
        //CODE for ULTRASONIC SENSOR
        digitalWrite(UStrigPin[i], LOW);
        delayMicroseconds(2);
        // Sets the trigPin on HIGH state for 10 micro seconds
        digitalWrite(UStrigPin[i], HIGH);
        delayMicroseconds(10);
        digitalWrite(UStrigPin[i], LOW);
        // Reads the echoPin, returns the sound wave travel time in microseconds
        duration = pulseIn(USechoPin[i], HIGH);
        // Calculating the distance
        distance = duration * 0.0340 / 2;
        if (distance < rangeUSensor) {
          CountData[i]++;
        }
        if (CountData[i] == 5) {
          SensorValue[i] = true;
        }
        i++;
      }
      while (i < noOfSensors) {                             //DATA from IR Sensor
        int data = digitalRead(Sensor[i]);
        if (data == LOW) {
          CountData[i]++;
        }
        else {
          CountData[i] = 0;
        }
        if (CountData[i] == 5) {
          SensorValue[i] = true;
        }
        i++;
      }
      ct += 100;
      delay(100);
    }
    int density  = 0;
    if (SensorValue[0]) {
      cop = 1;
    } else {
      cop = 0;
    }
    Serial.println ("Sensor Values: ");
    for (int i=0; i<noOfSensors; i++) {
      Serial.print (SensorValue[i]);
      Serial.print (" ");
    }
    for (int i = (noOfSensors - 1); i >= 1; i--) {
      if (SensorValue[i]) {
        if (i > 1 && SensorValue[i-1]) {
          rop = i;
        } else if (i == 1) {
           rop = 1;
        } else {
          rop = i-1;
        }
        break;
      }
    }

    Serial.print("Right : ");
    Serial.println(rop);
    
  }
  ct += 100;
  delay(100);
}

void sendToMaster() {                                                  //Sending Data to MASTER
  Serial.println ("Sending LOP and ROP :");
  Serial.println (cop);
  Serial.println (rop);
  // respond with message of 6 bytes
  Wire.write("r");
  Wire.write(rop);
  Wire.write("c");
  Wire.write(cop);
}


void receiveEvent(int howMany) {                                      //Receive Data from MASTER
  Serial.println ("Data receiving: ");
  int temp = 0;
  if (Wire.available()) { // loop through all but the last
    temp = Wire.read(); // receive byte as a integer
    SectionStartTime = temp * 1000;
    ctLow = SectionStartTime - 1000;
    ctHigh = SectionStartTime - 250;
    Serial.print(SectionStartTime);         // print the integer
    if (Wire.available()) { // loop through all but the last
      temp = Wire.read(); // receive byte as a integer
      ct = temp * 100;
      Serial.print(ct);         // print the integer
    }
  }
}

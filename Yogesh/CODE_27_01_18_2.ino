#include <Wire.h>

#define noOfIRS 2
#define noOfUS 2
#define noOfSensors 3
#define UStrigPin 9
#define USechoPin 10
#define SLAVE_ADDRESS 3
#define noOfLanes 3

int ct = 0, ctHigh = 3750, ctLow = 3000;
int CountData[noOfSensors];
boolean SensorValue[noOfSensors];
int cycleTime = 8000;
int Sensor[noOfSensors];
int SectionStartTime = 4000;
long duration = 0;
int distance = 0;
int rangeUSensor = 25;
String sendData = "";
String receiveData = "";
int laneTime = 0;
int lop = -1, cop = -1, rop = -1;

void setup() {
  Sensor[0] = USechoPin;
  Sensor[1] = USechoPin;
  Sensor[noOfUS] = 32;
  Sensor[noOfUS+1] = 33;

  // put your setup code here, to run once:
  for (int i=0; i<noOfSensors; i++) {
    pinMode(Sensor[i], INPUT);
  }
  pinMode(UStrigPin, OUTPUT);                       // Sets the trigPin as an Output

  Serial.begin(9600);

  Wire.begin(SLAVE_ADDRESS);                        // MASTER-SLAVE SET_UP
  Wire.onRequest(sendToMaster); // register event
  //Wire.onReceive(receiveEvent);

}

void loop() {
  // put your main code here, to run repeatedly
  if (ct >= cycleTime) {                            //Reset the Timer
    ct = 0;
    for (int i=0; i<noOfSensors; i++) {
      CountData[i] = 0;
      SensorValue[i] = false;
    }
  }
  if (ct >= ctLow && ct <= ctHigh) {
    Serial.println(ct);
    while(ct <= ctHigh) {
      int i = 0;
      while (i < noOfUS) {
                                                     //CODE for ULTRASONIC SENSOR
        digitalWrite(UStrigPin, LOW);
        delayMicroseconds(2);
                                                    // Sets the trigPin on HIGH state for 10 micro seconds
        digitalWrite(UStrigPin, HIGH);
        delayMicroseconds(10);
        digitalWrite(UStrigPin, LOW);
                                                    // Reads the echoPin, returns the sound wave travel time in microseconds
        duration = pulseIn(USechoPin, HIGH);
        // Calculating the distance
        distance = duration * 0.0340/2;
        if(distance < rangeUSensor) {
          CountData[i]++;          
        }
        if(CountData[i] == 5) {
          SensorValue[i] = true;
        }
        i++;
      }
      while (i < noOfSensors) {                           //DATA from IR Sensor
        int data = digitalRead(Sensor[i]);
        if(data == LOW) {
          CountData[i]++;          
        }
        else {
          CountData[i] = 0;
        }
        if(CountData[i] == 5) {
          SensorValue[i] = true;
        }
        i++;
      }
      ct +=100;
      delay(100);
    }
    int density  = 0;
    for (int i=(noOfSensors-2); i>=0; i -= 2) {
      if (SensorValue[i]) {
        if (i > 0 && SensorValue[i-2]) {
          rop = i;
        } else if (i == 0) {
          rop = 0;
        } else {
          rop = i - 2;
        }
        break;
      }
    }
    for (int i=(noOfSensors-1); i>0; i -= 2) {
      if (SensorValue[i]) {
        if (i > 0 && SensorValue[i-2]) {
          lop = i;
        } else if (i == 1) {
          lop = 1;
        } else {
          lop = i - 2;
        }
        break;
      }
    }
    if (noOfLanes <= 2) {
      cop = lop;
    } else {
      cop = (int)ceil((lop + rop) / 2.0);
    }
    Serial.println(lop);
    Serial.println(cop);
    Serial.println(rop);
//    Wire.requestFrom(requestEvent,9,true);
  }
  ct += 100;
  delay(100);
}

// function that executes whenever data is requested by master
// this function is registered as an event, see setup()
void sendToMaster() {                                                  //Sending Data to MASTER
  Serial.println ("Sending LOP and ROP :" + lop);
  Serial.println (cop + " " + rop);
  Wire.write("l");
  Wire.write(lop); // respond with message of 6 bytes
  delay(100);
  Wire.write("c");
  Wire.write(cop);
  delay(100);
  Wire.write("r");
  Wire.write(rop);
}

/*void receiveEvent(int howMany) {                                      //Receive Data from MASTER
  while (1 < Wire.available()) { // loop through all but the last
    int laneTime = Wire.read(); // receive byte as a character
    Serial.print(laneTime);         // print the character
    delay(100);
  }
  int x = Wire.read();    // receive byte as an integer
  Serial.println(x);         // print the integer
}*/

#define noOfIRS 2
#define noOfUS 1
#define noOfSensors 3
#define UStrigPin 9
#define USechoPin 10

int ct = 0, ctHigh = 3750, ctLow = 3000;
int CountData[noOfSensors];
boolean SensorValue[noOfSensors];
int cycleTime = 8000;
int Sensor[noOfSensors];
int SectionStartTime = 4000;
long duration = 0;
int distance = 0;
int rangeUSensor = 25;

void setup() {
  Sensor[0] = USechoPin;
  Sensor[noOfUS] = 32;
  Sensor[noOfUS+1] = 33;

  // put your setup code here, to run once:
  for (int i=0; i<noOfSensors; i++) {
    pinMode(Sensor[i], INPUT);
  }
  pinMode(UStrigPin, OUTPUT);                       // Sets the trigPin as an Output

  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly
  
  //CODE for IR SENSOR
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
        distance= duration * 0.0340/2;
        if(distance < rangeUSensor) {
          CountData[i]++;          
        }
        if(CountData[i] == 5) {
          SensorValue[i] = true;
        }
        i++;
      }
      while (i < noOfSensors) {
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
    int op = -1;
    for (int i=(noOfSensors-1); i>=0; i--) {
      if (SensorValue[i]) {
        if (i > 0 && SensorValue[i-1]) {
          op = i;
          break;
        } else if (i == 0) {
          op = 0;
        } else {
          op = i - 1;
        }
      }
    }
    Serial.println(op);
  }
  ct += 100;
  delay(100);
}

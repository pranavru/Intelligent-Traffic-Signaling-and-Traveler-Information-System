#define noOfSensors 2

int ct = 0, ctHigh = 3750, ctLow = 3000;
int CountData[noOfSensors];
boolean SensorValue[noOfSensors];
int cycleTime = 8000;
int Sensor[noOfSensors];
int durationTime = 4000;
int op = -1;
boolean flag = true;

void setup() {
  Sensor[0] = 32;
  Sensor[1] = 33;
  // put your setup code here, to run once:
  for (int i=0; i<noOfSensors; i++) {
    pinMode(Sensor[i], INPUT);
  }
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly
  if (ct >= cycleTime) {          //Reset the Timer
    ct = 0;
    flag = true;
  }
  if (ct >= ctLow && ct <= ctHigh) {
    Serial.println(ct);
    while(ct <= ctHigh) {
      int i = 0;
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
    for (int i=0; i<noOfSensors; i++) {
      CountData[i] = 0;
    }
  }
  if (ctHigh <= ct && ct <= durationTime && flag) {
     for (int i=(noOfSensors-1); i>=0; i--) {
        if (SensorValue[i]) {
          if (i > 0 && SensorValue[i-1]) {
            op = i;
            break;
          } else if (i == 0) {
            op = 0;
          }
        }
     }
     Serial.println(op);
     flag = false;
  }
  ct += 100;
  delay(100);
}

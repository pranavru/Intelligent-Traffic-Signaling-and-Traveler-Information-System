#include <Wire.h>

#define NoOfLanes 1
#define CycleDur 2000
//#define NoOfSections 
#define YellowLightTime 250

int Slaves[NoOfLanes];
int GreenDurOfLane[NoOfLanes];
double RightRatioOfLane[NoOfLanes];
//int GreenStartDurOfSection[NoOfSections];
int ct = 0;

void setup() {
  // put your setup code here, to run once:
  for (int i=0; i<NoOfLanes; i++) {
    GreenDurOfLane[i] = CycleDur / NoOfLanes;
    RightRatioOfLane[i] = 0.75;
    Slaves[i] = i * 2 + 1;
  }
//  setGreenStartDurOfSections();
  Serial.begin(9600);

  Wire.begin();        // join i2c bus (address optional for master)
}

void loop() {
  // put your main code here, to run repeatedly:
  int StartTime = ct;
  int CurrentTime = ct;
  while (CurrentTime <= StartTime + CycleDur) {
    if (CurrentTime == StartTime) {
      Serial.println ("SECTION 111111");  
    } /* else if (CurrentTime == GreenStartDurOfSection[0]) {
      Serial.println("SECTION 2222222");
    } else if (CurrentTime == GreenStartDurOfSection[1]) {
      Serial.println("SECTION 3333333");
    } else if (CurrentTime == GreenStartDurOfSection[2]) {
      Serial.println("SECTION 4444444");
    } else if (CurrentTime == GreenStartDurOfSection[3]) {
      Serial.println("SECTION 5555555");
    } else if (CurrentTime == GreenStartDurOfSection[4]) {
      Serial.println("SECTION 6666666");
    } */  else if (CurrentTime >= CycleDur - YellowLightTime) {
      int sum = 0;
      int VehicleDensity[NoOfLanes];
      for (int i=0; i<NoOfLanes; i++) {
        String str = readFromSlave(Slaves[i]);
        VehicleDensity[i] = 4;
        sum += VehicleDensity[i];
      }
      for (int i=0; i<NoOfLanes; i++) {
        GreenDurOfLane[i] = CycleDur / sum * VehicleDensity[i];
      }
//      setGreenStartDurOfSections();
    }
    CurrentTime += 100;
    delay(100);
  } 
  delay(100);
  ct += 100;
}

/*void setGreenStartDurOfSections() {
  GreenStartDurOfSection[0] = 0;
  GreenStartDurOfSection[1] = GreenDurOfLane[0] * RightRatioOfLane[0];
  GreenStartDurOfSection[2] = GreenDurOfLane[0] + GreenDurOfLane[2] * (1 - RightRatioOfLane[2]);
  GreenStartDurOfSection[3] = GreenDurOfLane[0] + GreenDurOfLane[2];
  GreenStartDurOfSection[4] = GreenStartDurOfSection[3] + GreenDurOfLane[1] * RightRatioOfLane[1];
  GreenStartDurOfSection[5] = GreenStartDurOfSection[3] + GreenDurOfLane[2] + GreenDurOfLane[3] * (1 - RightRatioOfLane[3]);
}*/

String readFromSlave(int slaveNo) {
  String data = "";
  Wire.requestFrom(slaveNo, 4);
  while (Wire.available()) {
    char c = Wire.read();
    Serial.print(c);
    data += "" + c;
    if (Wire.available()) {
      int x = Wire.read();
      Serial.print(x);
      data += "" + x;
      data += ",";
    }
    Serial.println();
  }
  return data;
}

void sendToSlave(int slaveNo, int data) {
  Wire.beginTransmission(slaveNo);
  Wire.write(data);
  Wire.endTransmission();
}

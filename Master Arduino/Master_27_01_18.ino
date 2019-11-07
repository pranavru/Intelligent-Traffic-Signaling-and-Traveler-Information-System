#include <Wire.h>
int data = 100;
void setup() {
  Wire.begin();        // join i2c bus (address optional for master)
  Wire.onRequest(requestEvent);
//  Wire.onReceive(receiveEvent);
  Serial.begin(9600);  // start serial for output
}

void loop() {
  requestEvent();
  Serial.println("Reading: ");
  Wire.requestFrom(8, 1);    // request 6 bytes from slave device #8
  while (1 < Wire.available()) { // slave may send less than requested
    int c = Wire.read(); // receive a byte as character
    Serial.print(c);         // print the character
  }
  int x = Wire.read();
  Serial.println(x);
  delay(95);
}

void receiveEvent() {
}

void requestEvent() {
  Wire.beginTransmission(8);
  Wire.write(data);
  Wire.endTransmission();
  data++;
}


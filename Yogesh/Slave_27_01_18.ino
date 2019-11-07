#include <Wire.h>

int no = 1;
void setup() {
  Wire.begin(8);                // join i2c bus with address #8
  Wire.onRequest(requestEvent); // register event
  Wire.onReceive(receiveEvent);
  Serial.begin(9600);
}

void loop() {
  requestEvent();
  delay(1500);
}

// function that executes whenever data is requested by master
// this function is registered as an event, see setup()
void requestEvent() {
  Serial.print ("Sending");
  Serial.println (no);
  Wire.write(no); // respond with message of 6 bytes
  // as expected by master
  no = no > 8 ? 0 : (no+1);
}

void receiveEvent(int howMany) {
  while (1 < Wire.available()) { // loop through all but the last
    int c = Wire.read(); // receive byte as a character
    Serial.print(c);         // print the character
  }
  int x = Wire.read();    // receive byte as an integer
  Serial.println(x);         // print the integer
}

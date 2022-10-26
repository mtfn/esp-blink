#include <SoftwareSerial.h>

void setup() {
  pinMode(10, OUTPUT);
  Serial.begin(9600);
  while (!Serial) {
    ;
  }
}


void loop() {
  // send data only when you receive data:
  if (Serial.available() > 0) {
    int b = Serial.read();
    
    if(b == 1) {
      digitalWrite(10, HIGH);  
    } else if(b == 0) {
      digitalWrite(10, LOW);  
    }
  }
}

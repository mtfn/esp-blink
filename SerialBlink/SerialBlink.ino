void setup() {
  /* LED in D10 */
  pinMode(10, OUTPUT);

  /* Baud rate matches ESP */
  Serial.begin(9600);
  while (!Serial) {
    ;
  }
}


void loop() {

  /* Read only when available */
  if (Serial.available() > 0) {
    int b = Serial.read();
    
    if(b == 1) {
      digitalWrite(10, HIGH);  
    } else if(b == 0) {
      digitalWrite(10, LOW);  
    }
  }
}

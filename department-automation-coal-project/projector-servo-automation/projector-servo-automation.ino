#include <Servo.h>

Servo myServo;

const int buttonPin = 13;   
const int ledPin    = 2;  
const int servoPin  = 6;   

bool lastButtonState = HIGH; 

void setup() {
  pinMode(buttonPin, INPUT_PULLUP); 
  pinMode(ledPin, OUTPUT);
  myServo.attach(servoPin);
  myServo.write(90);               
  digitalWrite(ledPin, LOW);

}

void loop() {
  bool currentButtonState = digitalRead(buttonPin);

  if (lastButtonState == HIGH && currentButtonState == LOW) {

    digitalWrite(ledPin, HIGH);   

    for (int pos = 70; pos <= 120; pos++) {
      myServo.write(pos);
      delay(5);                   
    }

    for (int pos = 120; pos >= 70; pos--) {
      myServo.write(pos);
      delay(5);
    }

    digitalWrite(ledPin, LOW);  
  }

  lastButtonState = currentButtonState;
}
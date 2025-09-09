#include <Servo.h>

Servo myServo;  
const int servoPin = 9; 
String inputPassword;  
int incorrectAttempts = 0; 
bool systemLocked = false;  

int LED_CLOSE = 13;
int LED_OPEN = 12;


void setup() {
  Serial.begin(9600);  
  myServo.attach(servoPin);  
  myServo.write(0);  
  pinMode(LED_OPEN, OUTPUT);
  pinMode(LED_CLOSE, OUTPUT);
  Serial.println("ENTER PASSWORD : ");
  digitalWrite(LED_CLOSE,HIGH);
  digitalWrite(LED_OPEN,LOW);
}

void loop() {
  if (systemLocked) {
    if (Serial.available() > 0) {  // Check for master key input
      inputPassword = Serial.readStringUntil('\n');
      if (inputPassword == "999") {  // Master key to unlock system
        systemLocked = false;
        incorrectAttempts = 0;  // Reset attempt counter
        Serial.println("SYSTEM UNLOCKED");
        Serial.println("ENTER PASSWORD : ");
        digitalWrite(LED_CLOSE,HIGH);
        digitalWrite(LED_OPEN,LOW);
      }
      else {
        Serial.println("INVALID MASTER KEY");
      }
    }
    return;
  }

  if (Serial.available() > 0) {  // Check for regular input
    inputPassword = Serial.readStringUntil('\n');

    if (inputPassword == "000") {  // Correct password
      Serial.println("PASSWORD CORRECT");
      digitalWrite(LED_OPEN,HIGH);
      digitalWrite(LED_CLOSE,LOW);
      myServo.write(180);  // Open door
      incorrectAttempts = 0;  // Reset attempt counter
      
      // Wait for close command
      while (true) {
        if (Serial.available() > 0) {
          String closeInput = Serial.readStringUntil('\n');
          if (closeInput == "*") {
            myServo.write(0);  // Close door
            digitalWrite(LED_CLOSE,HIGH);
            digitalWrite(LED_OPEN,LOW);
            Serial.println("DOOR CLOSED");
            Serial.println("ENTER PASSWORD : ");
            break;
          }
        }
      }
    }
    else {  // Incorrect password
      incorrectAttempts++;
      Serial.println("PASSWORD INCORRECT");
      delay(1000);
      Serial.println("TRY AGAIN");
      
      // Check for lock condition after 5 incorrect attempts
      if (incorrectAttempts >= 5) {
        systemLocked = true;
        digitalWrite(LED_CLOSE,HIGH);
        digitalWrite(LED_OPEN,LOW);
        Serial.println("SYSTEM LOCKED, INSERT MASTER KEY");
      }
    }
  }
}

Arduino Servo Door Lock System :-
This is an Arduino-based door lock control system using a servo motor and password authentication via serial input. The system features password checking, limited incorrect attempts lockout, and a master key override.

Project Description
This project implements a simple electronic door lock using:

Arduino microcontroller

Servo motor to actuate the door lock mechanism

Serial communication for password input

Two status LEDs to indicate door locked/unlocked states

Password security with limited attempts and master key override

Features
Password Protection: Only the correct password (000) opens the door.

Locked Out After Multiple Attempts: After 5 incorrect password attempts, the system locks and disables password input.

Master Key: Entering the master key (999) unlocks the system after lockout.

Servo Control: The servo rotates to 180° to open the door and 0° to close it.

Status LEDs:

Red LED (pin 13) indicates door locked (ON when locked).

Green LED (pin 12) indicates door unlocked (ON when open).

Hardware Requirements
Arduino board (Uno, Mega, etc.)

Servo motor connected to pin 9

Red LED connected to pin 13 (with appropriate resistor)

Green LED connected to pin 12 (with appropriate resistor)

Serial monitor (baud rate 9600) for password input and system messages

Usage Instructions
Connect the servo motor and LEDs to the Arduino according to the pin configuration.

Upload the code to the Arduino.

Open the Serial Monitor in the Arduino IDE (set baud rate to 9600).

The system will prompt: ENTER PASSWORD :

Enter the password 000 to open the door:

The green LED will light.

The servo will rotate to open position (180°).

To close the door, send * from the serial monitor:

The servo will rotate back to 0°.

The red LED will light indicating door locked.

If incorrect password is entered 5 times consecutively, the system locks out.

To unlock locked system, enter the master key 999.

Notes
Password and master key are hardcoded. Modify the code to change them as needed.

Ensure proper power supply and servo motor compatibility.

The locking mechanism and servo motor size should be matched physically for reliable operation.

Code Structure
Password input and verification using Serial.readStringUntil('\n')

Servo control via myServo.write()

Lock state managed with boolean systemLocked

LED indicators using digitalWrite()

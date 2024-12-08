#include <Arduino.h>
#include <SoftwareSerial.h>

SoftwareSerial mySerial(12, 13); // TX, RX

const int ledPin = 8;
const int buttonPin1 = 3, buttonPin2 = 5, buttonPin3 = 7;
int buttonState1 = 0, buttonState2 = 0, buttonState3 = 0;

void setup() {
	Serial.begin(9600);
	Serial.println("ard-on");

	mySerial.begin(9600);
	mySerial.println("ble-on");

	pinMode(ledPin, OUTPUT);

	pinMode(buttonPin1, INPUT);
	pinMode(buttonPin2, INPUT);
	pinMode(buttonPin3, INPUT);
}


void serialSent(int buttonPin, int buttonState) {
	switch (buttonPin) {
		case 3:
			// if the button state changes from high to low send button pressed 
			if(buttonState != buttonState1) {
				if (buttonState == LOW) {
					Serial.println("ard-" + String(buttonPin) + "-p");
					mySerial.println("ble-" + String(buttonPin) + "-p");
				}
				buttonState1 = buttonState;
			}
			break;
		case 5:
			if(buttonState != buttonState2) {
				if (buttonState == LOW) {
					Serial.println("ard-" + String(buttonPin) + "-p");
					mySerial.println("ble-" + String(buttonPin) + "-p");
				}
				buttonState2 = buttonState;
			}
			break;
		case 7:
			if(buttonState != buttonState3) {
				if (buttonState == LOW) {
					Serial.println("ard-" + String(buttonPin) + "-p");
					mySerial.println("ble-" + String(buttonPin) + "-p");
				}
				buttonState3 = buttonState;
			}
			break;
	}
}

void buttonClickedEvent(int buttonPin) {
	int buttonState = digitalRead(buttonPin);

	if (buttonState == HIGH) {
		digitalWrite(ledPin, HIGH);
	} else {
		digitalWrite(ledPin, LOW);
	}

	serialSent(buttonPin, buttonState);
}

void loop() {
	buttonClickedEvent(buttonPin1);
	buttonClickedEvent(buttonPin2);
	buttonClickedEvent(buttonPin3);

	delay(10);
}

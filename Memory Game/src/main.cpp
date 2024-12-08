#include <Arduino.h>

#include "./Game.cpp"

// const int ledPin1 = 2, ledPin2 = 4, ledPin3 = 6, ledPin4 = 8;
const int buttonPin1 = 3, buttonPin2 = 5, buttonPin3 = 7, buttonPin4 = 9;

int buttonState1 = 0, buttonState2 = 0, buttonState3 = 0, buttonState4 = 0;

Game game;

void flashLed(int ledPin);
// void checkButton(int buttonPin, int *buttonState);
bool checkButtonClicked(int buttonPin, int *buttonState);
int btnNumberToLedPin(int btnNumber);

void setup() {

	Serial.begin(9600);

	game = Game();

	pinMode(buttonPin1 - 1, OUTPUT);
	pinMode(buttonPin2 - 1, OUTPUT);
	pinMode(buttonPin3 - 1, OUTPUT);
	pinMode(buttonPin4 - 1, OUTPUT);

	pinMode(buttonPin1, INPUT);
	pinMode(buttonPin2, INPUT);
	pinMode(buttonPin3, INPUT);
	pinMode(buttonPin4, INPUT);
}


void Start_State_Loop() {
	digitalWrite(buttonPin3-1, HIGH);
	if (checkButtonClicked(buttonPin3, &buttonState3)) {
		digitalWrite(buttonPin3-1, LOW);
		game.start();
	}
}

void Flash_Leds_State_Loop() {
	ArrayList<int> memoryChoice = game.getMemoryChoice();
	for (int i = 0; i < memoryChoice.getSize(); i++) {
		flashLed(btnNumberToLedPin(memoryChoice.get(i)));
		Serial.print(memoryChoice.get(i));
	}
	game.clearMemoryChoice();
	game.setGameState(GameState::START);
}


void loop() {
	GameState state = game.getGameState();
	switch (state) {
		case GameState::START:
			Start_State_Loop();
			break;
		case GameState::FLASH_LEDS:
			Flash_Leds_State_Loop();
			break;
		case GameState::CHECK_BUTTONS:
			// checkButton(buttonPin1, &buttonState1);
			// checkButton(buttonPin2, &buttonState2);
			// checkButton(buttonPin3, &buttonState3);
			// checkButton(buttonPin4, &buttonState4);
			break;
		case GameState::GAME_OVER:
			break;
	}
}


void flashLed(int ledPin) {
	digitalWrite(ledPin, HIGH);
	delay(1500);
	digitalWrite(ledPin, LOW);
	delay(1000);
}

int btnNumberToLedPin(int btnNumber) {
	switch(btnNumber) {
		case 1:
			return buttonPin1-1;
		case 2:
			return buttonPin2-1;
		case 3:
			return buttonPin3-1;
		case 4:
			return buttonPin4-1;
		default:
			return -1;
	}
}

// void checkButton(int buttonPin, int *buttonState) {
// 	int readButtonState = digitalRead(buttonPin);
// 	if (readButtonState != *buttonState) {
// 		*buttonState = readButtonState;
// 		if (readButtonState == LOW) {
// 			flashLed(buttonPin - 1);
// 		}
// 	}
// }

bool checkButtonClicked(int buttonPin, int *buttonState) {
	int readButtonState = digitalRead(buttonPin);
	if (readButtonState != *buttonState) {
		*buttonState = readButtonState;
		if (readButtonState == LOW) {
			return true;
		}
	}
	return false;
}
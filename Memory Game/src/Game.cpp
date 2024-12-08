#include <Arduino.h>

#include "./ArrayList.cpp"


enum class GameState {
    START,
    FLASH_LEDS,
    CHECK_BUTTONS,
    GAME_OVER
};

class Game {
    private:
        int level;
        ArrayList<int> memoryChoice;
        ArrayList<int> playerChoice;
        GameState state;
    public:
        Game();
        void start();
        void increaseLevel();
        void setGameState(GameState state);
        void addMemoryChoice(int choice);
        void clearMemoryChoice();
        void addPlayerChoice(int choice);
        void clearPlayerChoice();

        int getLevel();
        ArrayList<int> getMemoryChoice();
        ArrayList<int> getPlayerChoice();
        GameState getGameState();
};

inline Game::Game() {
    level = 1;
    memoryChoice = ArrayList<int>();
    state = GameState::START;
}

void inline Game::start() {
    state = GameState::FLASH_LEDS;
    for (int i = 0; i < 5; i++) {
        int choice = random(1, 5);
        Serial.print(choice);
        memoryChoice.add(choice);
    }
}

void inline Game::increaseLevel() {
    level++;
}

void inline Game::setGameState(GameState state) {
    this->state = state;
}

void inline Game::addMemoryChoice(int choice) {
    memoryChoice.add(choice);
}

void inline Game::clearMemoryChoice() {
    memoryChoice.clear();
}

void inline Game::addPlayerChoice(int choice) {
    playerChoice.add(choice);
}

void inline Game::clearPlayerChoice() {
    playerChoice.clear();
}

int inline Game::getLevel() { return level; }

ArrayList<int> inline Game::getMemoryChoice() { return memoryChoice; }

ArrayList<int> inline Game::getPlayerChoice() { return playerChoice; }

GameState inline Game::getGameState() { return state; }



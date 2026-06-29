#include "MiniGames.h"
#include <Adafruit_ST7735.h>
#include <Adafruit_SSD1306.h>
#include "config.h"

void MiniGames::OnEnter() {
    _tft->fillScreen(ST77XX_BLACK);
    _tft->setCursor(10, 10);
    _tft->setTextColor(ST77XX_WHITE);
    _tft->setTextSize(2);
    _tft->print("Tasks");
}

void MiniGames::onShortClick() {
    if (_pm) _pm->SwitchToIndex(0);  
}

void MiniGames::onLongClick() {

}

void MiniGames::Update(uint32_t deltaTimeMs) {

}

void MiniGames::OnExit() {

}

void MiniGames::Draw() {
 
}
#include "MiniGames.h"
#include <Adafruit_ST7735.h>
#include <Adafruit_SSD1306.h>
#include "PageManager.h"
#include "config.h"

void MiniGames::onShortClick() {
    if (_pm) _pm->SwitchToIndex(PageIndex::HOME);  
}

void MiniGames::onLongClick() {

}

void MiniGames::onDoubleClick() {
    
}

void MiniGames::OnEnter() {
    DrawFrame("GAMES");
}

void MiniGames::Update(uint32_t deltaTimeMs) {

}

void MiniGames::OnExit() {

}


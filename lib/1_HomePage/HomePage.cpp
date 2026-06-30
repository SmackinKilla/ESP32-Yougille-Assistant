// HomePage.cpp
#include "HomePage.h"
#include <Adafruit_ST7735.h>
#include <Adafruit_SSD1306.h>
#include "ColorPalette.h"

void HomePage::DrawMenu() {
    for (int i = 0; i < 5; i++) {
    int y = charStart + charOffset * (i);
    
    if (i == currentIndex) {
        _tft->fillRect(0, y - 2, SCREEN_WIDTH, charOffset, COLOR_WHITE);
        _tft->setTextColor(COLOR_BLUE);
    } else {
        _tft->fillRect(0, y - 2, SCREEN_WIDTH, charOffset, COLOR_BLUE);
        _tft->setTextColor(COLOR_WHITE);
        }
        
    _tft->setCursor(2, y);
    _tft->setTextSize(globalTextSize);
    _tft->print(menuItems[i]);
    }
}

void HomePage::onShortClick() {
    currentIndex++;
    if (currentIndex >= 5) currentIndex = 0;
    previousIndex = -1;
}

void HomePage::onLongClick() {
    _pm->SwitchToIndex(currentIndex);
}

void HomePage::onDoubleClick() {

}

void HomePage::OnEnter() {
    DrawFrame("HOME");
    DrawMenu();
}

void HomePage::Update(uint32_t deltaTimeMs) {
    if (currentIndex != previousIndex) {
    DrawMenu();
    previousIndex = currentIndex;
    }
}

void HomePage::OnExit() {
    _tft->fillRect(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, COLOR_BLUE);
}


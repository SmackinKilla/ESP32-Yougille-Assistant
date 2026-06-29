// HomePage.cpp
#include "HomePage.h"
#include <Adafruit_ILI9341.h>
#include <Adafruit_SSD1306.h>
#include <ColorPalette.h>

void HomePage::onShortClick() {
    currentIndex++;
    if (currentIndex >= 5) currentIndex = 0;
    previousIndex = -1;
}

void HomePage::onLongClick() {
    pageManager->SwitchToIndex(currentIndex);
    OnExit();
}

void HomePage::DrawGUI() {
    _tft->fillRect(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, COLOR_BLUE);
    _tft->setCursor (2, 5);
    _tft->setTextSize(1);
    _tft->setTextColor(COLOR_WHITE);
    _tft->print("HOME");
    _tft->drawLine(0, 13, SCREEN_WIDTH, 13, COLOR_WHITE);
    _tft->drawLine(0, 117, 160, 117, COLOR_WHITE);
    _tft->setCursor(2, 120);
    _tft->setTextSize(1);
    _tft->setTextColor(COLOR_WHITE);
    _tft->print("<== Prev");
    _tft->setCursor(110, 120);
    _tft->setTextSize(1);
    _tft->setTextColor(COLOR_WHITE);
    _tft->print("Next ==>");
}

void HomePage::DrawMenu() {
    for (int i = 0; i < 5; i++) {
    int y = charStart + charOffset * i;
    
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

void HomePage::OnEnter() {
    DrawGUI();
    DrawMenu();
}

void HomePage::Update(uint32_t deltaTimeMs) {
    if (currentIndex != previousIndex) {
    DrawMenu();
    previousIndex = currentIndex;
    }
}

void HomePage::OnExit() {
    _tft->fillRect(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, COLOR_BLACK);
}

void HomePage::Draw() {

}

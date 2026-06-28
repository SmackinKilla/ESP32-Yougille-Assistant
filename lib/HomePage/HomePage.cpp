// HomePage.cpp
#include "HomePage.h"
#include <Adafruit_ST7735.h>
#include <Adafruit_SSD1306.h>

int currentIndex = 0;
void HomePage::onButtonPressed() {
    currentIndex++;
    if (currentIndex >= 5) currentIndex = 0;
    previousIndex = -1;
}

void HomePage::DrawGUI() {
    _tft->fillScreen(ST7735_BLUE);
    _tft->setCursor (2, 5);
    _tft->setTextSize(1);
    _tft->setTextColor(ST7735_WHITE);
    _tft->print("HOME");
    _tft->drawLine(0, 13, SCREEN_WIDTH, 13, ST7735_WHITE);
    _tft->drawLine(0, 117, 160, 117, ST7735_WHITE);
    _tft->setCursor(2, 120);
    _tft->setTextSize(1);
    _tft->setTextColor(ST7735_WHITE);
    _tft->print("<== Prev");
    _tft->setCursor(110, 120);
    _tft->setTextSize(1);
    _tft->setTextColor(ST7735_WHITE);
    _tft->print("Next ==>");
}

void HomePage::Weather() {
    _tft->setCursor(2, 18);
    _tft->setTextSize(globalTextSize);
    _tft->setTextColor(ST7735_WHITE);
    _tft->print(menuItems[0]);
}

void HomePage::Tasks() {
    _tft-> setCursor(2, 28);
    _tft-> setTextSize(globalTextSize);
    _tft-> setTextColor(ST7735_WHITE);
    _tft-> print(menuItems[1]);
}

void HomePage::Time_Zones() {
    _tft-> setCursor (2, 38);
    _tft-> setTextSize(globalTextSize);
    _tft-> setTextColor(ST7735_WHITE);
    _tft-> print(menuItems[2]);
}

void HomePage::Gambling() {
    _tft-> setCursor (2, 48);
    _tft-> setTextSize(globalTextSize);
    _tft-> setTextColor(ST7735_WHITE);
    _tft-> print(menuItems[3]);
}

void HomePage::Settings(){
    _tft-> setCursor (2, 58);
    _tft-> setTextSize(globalTextSize);
    _tft-> setTextColor(ST7735_WHITE);
    _tft-> print(menuItems[4]);    
}

void HomePage::OnEnter() {
    DrawGUI();
    Weather();
    Tasks();
    Time_Zones();
    Gambling();
    Settings();
}

void HomePage::Update(uint32_t deltaTimeMs) {

}

void HomePage::OnExit() {

}

void HomePage::Draw() {

}
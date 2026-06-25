// HomePage.cpp
#include "HomePage.h"
#include <Adafruit_ST7735.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_HEIGHT 128
#define SCREEN_WIDHT 160

void HomePage::DrawGUI() {
    _tft->setCursor(1, 1);
    _tft->setTextColor(ST7735_CYAN);
    _tft->setTextSize(2);
    _tft->print("Screen 1");
    _oled->clearDisplay();
    _oled->setCursor(15, 15);
    _oled->setTextColor(SSD1306_WHITE);
    _oled->setTextSize(3);
    _oled->print("Screen 1 OLED");
    _oled->display();
}

void HomePage::OnEnter() {

}

void HomePage::Update(uint32_t deltaTimeMs) {

}

void HomePage::OnExit() {
    _tft->fillScreen(ST7735_BLACK);
}

void HomePage::Draw() {
    DrawGUI();
}
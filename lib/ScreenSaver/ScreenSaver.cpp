// ScreenSaver.cpp
#include "ScreenSaver.h"
#include <Adafruit_ST7735.h>
#include <Adafruit_SSD1306.h>

void ScreenSaver::OnEnter() { //tipa setup

}

void ScreenSaver::Update(uint32_t deltaTimeMs) {
    _tft->setCursor(1, 1);
    _tft->setTextColor(ST7735_CYAN);
    _tft->setTextSize(2);
    _tft->print("Screen 2");
    _oled->clearDisplay();
    _oled->setCursor(15, 12);
    _oled->setTextColor(SSD1306_WHITE);
    _oled->setTextSize(3);
    _oled->print("Screen 2 OLED");
    _oled->display(); //tipa loop

}

void ScreenSaver::OnExit() {
    _tft->fillScreen(ST7735_BLACK);
}

void ScreenSaver::Draw() { // tyt vse risui

}
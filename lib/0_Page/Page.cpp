#include "Page.h"
#include <Adafruit_ST7735.h>
#include "ColorPalette.h"

void Page::DrawFrame(const char* title) {
    _tft->fillScreen(COLOR_BLUE);
    
    _tft->setCursor(2, 5);
    _tft->setTextSize(1);
    _tft->setTextColor(COLOR_WHITE);
    _tft->print(title);
    _tft->drawLine(0, 13, SCREEN_WIDTH, 13, COLOR_WHITE);
    _tft->drawLine(0, 117, SCREEN_WIDTH, 117, COLOR_WHITE);
    _tft->setCursor(2, 120);
    _tft->setTextSize(1);
    _tft->setTextColor(COLOR_WHITE);
    _tft->print("<== Back");
    _tft->setCursor(110, 120);
    _tft->print("Next ==>");
}
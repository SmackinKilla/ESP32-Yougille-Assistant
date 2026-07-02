#include "Page.h"
#include <Adafruit_ST7735.h>
#include "ColorPalette.h"

void Page::DrawFrame(const char* title) {
    _tft->fillScreen(COLOR_BG);
    
    _tft->setCursor(2, 5);
    _tft->setTextSize(1);
    _tft->setTextColor(COLOR_TEXT);
    _tft->print(title);
    _tft->drawLine(0, 13, SCREEN_WIDTH, 13, COLOR_TEXT);
    _tft->drawLine(0, 117, SCREEN_WIDTH, 117, COLOR_TEXT);
    _tft->setCursor(2, 120);
    _tft->setTextSize(1);
    _tft->setTextColor(COLOR_TEXT);
    _tft->print("Next: x1");
    _tft->setCursor(86, 120);
    _tft->print("Select: Hold");
}

void Page::DrawMenu(const char* items[], int count, int currentIndex) {
    int charStart = 18;
    int charOffset = 11;

    for (int i = 0; i < count; i++) {
        int y = charStart + charOffset * i;
        
        if (i == currentIndex) {
            _tft->fillRect(0, y - 2, SCREEN_WIDTH, charOffset, COLOR_ACCENT);
            _tft->setTextColor(COLOR_BG);
        } else {
            _tft->fillRect(0, y - 2, SCREEN_WIDTH, charOffset, COLOR_BG);
            _tft->setTextColor(COLOR_TEXT);
        }
        
        _tft->setCursor(2, y);
        _tft->setTextSize(1);
        _tft->print(items[i]);
    }
}
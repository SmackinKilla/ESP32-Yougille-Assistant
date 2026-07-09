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

void Page::drawModalWindow(const char* title, const char* items[], int itemCount, int selectedIdx, int x, int y, int w, int h, int maxVisibleItems) {
    _tft->fillRect(x + 6, y + 6, w, h, COLOR_BLACK);
    _tft->fillRect(x, y, w, h, COLOR_BG);
    _tft->drawRect(x, y, w, h, COLOR_TEXT);
    int contentY = y + 2;
    if (title != nullptr) {
        _tft->setTextColor(COLOR_ACCENT);
        _tft->setTextSize(1);
        _tft->setCursor(x + 4, contentY);
        _tft->print(title);
        contentY += 12; 
        _tft->drawFastHLine(x + 2, contentY - 2, w - 4, COLOR_TEXT);
    }

    int itemHeight = 10;
    int maxVisible = (y + h - contentY) / itemHeight;
    /*for (int i = 0; i < itemCount && i < maxVisible; i++) {
        int iy = contentY + i * itemHeight;
        
        if (i == selectedIdx) {
            _tft->fillRect(x + 2, iy - 1, w - 4, itemHeight, COLOR_ACCENT);
            _tft->setTextColor(COLOR_BG);
        } else {
            _tft->setTextColor(COLOR_TEXT);
        }
        _tft->setCursor(x + 6, iy);
        _tft->setTextSize(1);
        _tft->print(items[i]);
    }*/

    int scrollOffset = 0;
    if (itemCount > maxVisible) {
        if (selectedIdx >= maxVisible) {
            scrollOffset = selectedIdx - maxVisible + 1;
        }
        int maxScroll = itemCount - maxVisible;
        if (scrollOffset > maxScroll) scrollOffset = maxScroll;
    }
    int visibleCount = (itemCount < maxVisible) ? itemCount : maxVisible;
    for (int i = 0; i < visibleCount; i++) {
        int actualIdx = scrollOffset + i; 
        int iy = contentY + i * itemHeight;
        if (actualIdx == selectedIdx) {
            _tft->fillRect(x + 2, iy - 1, w - 4, itemHeight, COLOR_ACCENT);
            _tft->setTextColor(COLOR_BG);
        } else {
            _tft->setTextColor(COLOR_TEXT);
        }
        _tft->setCursor(x + 6, iy);
        _tft->setTextSize(1);
        _tft->print(items[actualIdx]); 
    }


    if (scrollOffset > 0) {
        _tft->setTextColor(COLOR_ACCENT);
        _tft->setCursor(x + w - 10, contentY);
        _tft->print("^");
    }
    if (scrollOffset + visibleCount < itemCount) {
        _tft->setTextColor(COLOR_ACCENT);
        _tft->setCursor(x + w - 10, contentY + (visibleCount - 1) * itemHeight);
        _tft->print("v");
    }
}
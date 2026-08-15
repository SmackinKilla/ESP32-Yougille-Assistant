#include "Page.h"
#include <Adafruit_GFX.h>
#include <ColorPalette.h>
#include "DisplayManager.h"

static int calcScrollOffset(int selectedIdx, int itemCount, int maxVisible) {
    if (itemCount <= maxVisible) return 0;

    int scrollOffset = 0;
    if (selectedIdx >= maxVisible) {
        scrollOffset = selectedIdx - maxVisible + 1;
    }
    int maxScroll = itemCount - maxVisible;
    if (scrollOffset > maxScroll) scrollOffset = maxScroll;
    return scrollOffset;
}

void Page::DrawFrame(const char* title) {
    screen(0)->fillScreen(COLOR_BG);
    
    screen(0)->setCursor(2, 5);
    screen(0)->setTextSize(1);
    screen(0)->setTextColor(COLOR_TEXT);
    screen(0)->print(title);
    screen(0)->drawLine(0, 13, SCREEN_WIDTH, 13, COLOR_TEXT);
    screen(0)->drawLine(0, SCREEN_HEIGHT - 13, SCREEN_WIDTH, SCREEN_HEIGHT - 13, COLOR_TEXT);
    screen(0)->setCursor(2, SCREEN_HEIGHT - 8);
    screen(0)->print("Next: x1");
    screen(0)->setCursor(SCREEN_WIDTH - 78, SCREEN_HEIGHT - 8);
    screen(0)->print("Select: Hold");
}

void Page::DrawMenu(const char* items[], int count, int currentIndex) {
    int charStart = 18;
    int charOffset = 11;
    
    int areaBottom = SCREEN_HEIGHT - 13;
    int maxVisible = (areaBottom - charStart) / charOffset;
    int scrollOffset = calcScrollOffset(currentIndex, count, maxVisible);
    int visibleCount = (count < maxVisible) ? count : maxVisible;

    for (int i = 0; i < visibleCount; i++) {
        int actualIdx = scrollOffset + i;
        int y = charStart + charOffset * i;

        if (actualIdx == currentIndex) {
            screen(0)->fillRect(0, y - 2, SCREEN_WIDTH, charOffset, COLOR_ACCENT);
            screen(0)->setTextColor(COLOR_BG);
        } else {
            screen(0)->fillRect(0, y - 2, SCREEN_WIDTH, charOffset, COLOR_BG);
            screen(0)->setTextColor(COLOR_TEXT);
        }
        screen(0)->setCursor(2, y);
        screen(0)->setTextSize(1);
        screen(0)->print(items[actualIdx]);
    }


    if (scrollOffset > 0) {
        screen(0)->setTextColor((scrollOffset == currentIndex) ? COLOR_BG : COLOR_ACCENT);
        screen(0)->setCursor(SCREEN_WIDTH - 8, charStart);
        screen(0)->print("^");
    }
    if (scrollOffset + visibleCount < count) {
        int lastVisible = scrollOffset + visibleCount - 1;
        screen(0)->setTextColor((lastVisible == currentIndex) ? COLOR_BG : COLOR_ACCENT);
        screen(0)->setCursor(SCREEN_WIDTH - 8, charStart + (visibleCount - 1) * charOffset);
        screen(0)->print("v");
    }
}

void Page::drawModalWindow(const char* title, const char* items[], int itemCount, int selectedIdx, int x, int y, int w, int h, int maxVisibleItems) {
    screen(0)->fillRect(x + 6, y + 6, w, h, COLOR_BLACK);
    screen(0)->fillRect(x, y, w, h, COLOR_BG);
    screen(0)->drawRect(x, y, w, h, COLOR_TEXT);
    int contentY = y + 2;
    if (title != nullptr) {
        screen(0)->setTextColor(COLOR_ACCENT);
        screen(0)->setTextSize(1);
        screen(0)->setCursor(x + 4, contentY);
        screen(0)->print(title);
        contentY += 12; 
        screen(0)->drawFastHLine(x + 2, contentY - 2, w - 4, COLOR_TEXT);
    }

    int itemHeight = 10;
    int maxVisible = (y + h - contentY) / itemHeight;
    int scrollOffset = calcScrollOffset(selectedIdx, itemCount, maxVisible);
    int visibleCount = (itemCount < maxVisible) ? itemCount : maxVisible;
    for (int i = 0; i < visibleCount; i++) {
        int actualIdx = scrollOffset + i; 
        int iy = contentY + i * itemHeight;
        if (actualIdx == selectedIdx) {
            screen(0)->fillRect(x + 2, iy - 1, w - 4, itemHeight, COLOR_ACCENT);
            screen(0)->setTextColor(COLOR_BG);
        } else {
            screen(0)->setTextColor(COLOR_TEXT);
        }
        screen(0)->setCursor(x + 6, iy);
        screen(0)->setTextSize(1);
        screen(0)->print(items[actualIdx]); 
    }


    if (scrollOffset > 0) {
        screen(0)->setTextColor(COLOR_ACCENT);
        screen(0)->setCursor(x + w - 10, contentY);
        screen(0)->print("^");
    }
    if (scrollOffset + visibleCount < itemCount) {
        screen(0)->setTextColor(COLOR_ACCENT);
        screen(0)->setCursor(x + w - 10, contentY + (visibleCount - 1) * itemHeight);
        screen(0)->print("v");
    }
}
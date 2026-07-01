// HomePage.cpp
#include "HomePage.h"
#include "PageManager.h"
#include "ColorPalette.h"
#include <stdio.h>
#include <Adafruit_ST7735.h>

void HomePage::DrawMenu() {
    const int count = static_cast<int>(PageIndex::COUNT);
    const char* items[count];
    char buffers[count][32];
    for (int i = 0; i < count; i++) {
        PageIndex idx = static_cast<PageIndex>(i);
        TitleInfo props = getTitleInfo(idx);

        if (props.hasCounter) {
            snprintf(buffers[i], sizeof(buffers[i]), "%d. %s(0)", i + 1, props.title);
            items[i] = buffers[i];
        } else {
            items[i] = props.title;
        }
    }
    Page::DrawMenu(menuItems, MENU_COUNT, currentIndex);
}

void HomePage::onShortClick() {
    currentIndex++;
    if (currentIndex >= MENU_COUNT) currentIndex = 0;
    previousIndex = -1;
}

void HomePage::onLongClick() {
    _pm->SwitchToIndex(static_cast<PageIndex>(currentIndex));
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
    _tft->fillRect(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, COLOR_BG);
}


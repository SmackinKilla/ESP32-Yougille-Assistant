// HomePage.h
#pragma once
#include "Page.h"
#include "PageManager.h"

const int SCREEN_WIDTH = 160;
const int SCREEN_HEIGHT = 128;

class HomePage : public Page {
public:
    HomePage(Adafruit_ST7735* tft, Adafruit_SSD1306* oled, PageManager* pm) 
        : Page(tft, oled), pageManager(pm){}

    void onShortClick() override;
    void onLongClick() override;
    void OnEnter() override;
    void Update(uint32_t deltaTimeMs) override;
    void OnExit() override;
    void Draw() override;

private:
    PageManager* pageManager;
    void DrawMenu();
    void DrawGUI();
    int currentIndex = 0;
    int previousIndex = -1;
    int charOffset = 10;
    int charStart = 18;
    int globalTextSize = 1;
    const char* menuItems[5] {
        "1. Weather",
        "2. Tasks(0)",
        "3. Time Zones",
        "4. Gambling",
        "5. Settings"
    };
};

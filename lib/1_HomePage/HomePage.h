// HomePage.h
#pragma once
#include "Page.h"
#include "PageManager.h"

class HomePage : public Page {
public:
    HomePage(Adafruit_ST7735* tft, Adafruit_SSD1306* oled, PageManager* pm) 
        : Page(tft, oled, pm){}

    void onShortClick() override;
    void onLongClick() override;
    void onDoubleClick() override;
    void OnEnter() override;
    void Update(uint32_t deltaTimeMs) override;
    void OnExit() override;

private:
    PageManager* pageManager;
    void DrawMenu();
    void DrawGUI();
    int currentIndex = 1;
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
    static constexpr int MENU_COUNT = sizeof(menuItems) / sizeof(menuItems[0]);
};

// HomePage.h
#pragma once
#include "Page.h"

const int SCREEN_WIDTH = 160;
const int SCREEN_HEIGHT = 128;

class HomePage : public Page {
public:
    HomePage(Adafruit_ST7735* tft, Adafruit_SSD1306* oled) 
        : Page(tft, oled) {}

    void onButtonPressed() override; 
    void OnEnter() override;
    void Update(uint32_t deltaTimeMs) override;
    void OnExit() override;
    void Draw() override;

private:
    void DrawGUI();
    void Weather();
    void Tasks();
    void Time_Zones();
    void Gambling();
    void Settings();
    int currentIndex = 0;
    int previousIndex;
    int charOffset;
    int globalTextSize = 1;
    const char* menuItems[5] {
        "1. Weather",
        "2. Tasks(0)",
        "3. Time Zones",
        "4. Gambling",
        "5. Settings"
    };
};
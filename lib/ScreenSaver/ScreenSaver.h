// ScreenSaver.h
#pragma once
#include "Page.h"

class ScreenSaver : public Page {
public:
    ScreenSaver(Adafruit_ST7735* tft, Adafruit_SSD1306* oled, PageManager* pm) 
        : Page(tft, oled, pm) {}
    
    void OnEnter() override;
    void Update(uint32_t deltaTimeMs) override;
    void OnExit() override;
    void Draw() override;
};

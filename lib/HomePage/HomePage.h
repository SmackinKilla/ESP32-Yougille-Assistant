// HomePage.h
#pragma once
#include "Page.h"

class HomePage : public Page {
public:
    HomePage(Adafruit_ST7735* tft, Adafruit_SSD1306* oled) 
        : Page(tft, oled) {}
    
    void OnEnter() override;
    void Update(uint32_t deltaTimeMs) override;
    void OnExit() override;
    void Draw() override;
private:
    void DrawGUI();
};
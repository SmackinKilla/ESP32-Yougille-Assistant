// ScreenSaver.h
#pragma once
#include "Page.h"

class ScreenSaver : public Page {
public:
    ScreenSaver(Adafruit_GFX* tft, Adafruit_GFX* oled, PageManager* pm) 
        : Page(tft, oled, pm) {}
    
    void OnEnter() override;
    void Update(uint32_t deltaTimeMs) override;
    void OnExit() override;

};

#pragma once
#include "Page.h"
#include "PageManager.h"
class Adafruit_ST7735;
class Adafruit_SSD1306;

class TimeZonesPage : public Page {
public:
    TimeZonesPage(Adafruit_ST7735* tft, Adafruit_SSD1306* oled, PageManager* pm) 
        : Page(tft, oled, pm) {}

    void onShortClick() override;
    void onLongClick() override;
    void OnEnter() override;
    void Update(uint32_t deltaTimeMs) override;
    void OnExit() override;
    void Draw() override;
    
private:
    PageManager* pageManager;
};
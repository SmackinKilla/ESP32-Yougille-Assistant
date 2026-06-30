#pragma once
#include "Page.h"
#include "PageManager.h"
class Adafruit_ST7735;
class Adafruit_SSD1306;

class TasksPage : public Page {
public:
    TasksPage(Adafruit_ST7735* tft, Adafruit_SSD1306* oled, PageManager* pm) 
        : Page(tft, oled, pm) {}

    void onShortClick() override;
    void onLongClick() override;
    void onDoubleClick() override;
    void OnEnter() override;
    void Update(uint32_t deltaTimeMs) override;
    void OnExit() override;
    
private:
    PageManager* pageManager;
};
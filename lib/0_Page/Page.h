#pragma once
#include <stdint.h>

class Adafruit_ST7735;
class Adafruit_SSD1306;
class PageManager;
class Page {
public:
    Page(Adafruit_ST7735* tft, Adafruit_SSD1306* oled, PageManager* pm = nullptr) 
        : _tft(tft), _oled(oled), _pm(pm) {}  
    virtual ~Page() = default;
    virtual void onShortClick() {}
    virtual void onLongClick() {}
    virtual void OnEnter() {}
    virtual void Update(uint32_t deltaTimeMs) {}
    virtual void OnExit() {}
    virtual void onDoubleClick() {}

protected:
    void DrawFrame(const char* title);
    Adafruit_ST7735* _tft;
    Adafruit_SSD1306* _oled;
    PageManager* _pm; 
    static constexpr int SCREEN_WIDTH  = 160;
    static constexpr int SCREEN_HEIGHT = 128;
};

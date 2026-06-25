#pragma once
#include <stdint.h>

class Adafruit_ILI9341;
class Adafruit_SSD1306;

class Page {
public:
    Page(Adafruit_ILI9341* tft, Adafruit_SSD1306* oled) 
        : _tft(tft), _oled(oled) {}
    
    virtual ~Page() = default;
    
    virtual void OnEnter() {}
    virtual void Update(uint32_t deltaTimeMs) {}
    virtual void OnExit() {}
    virtual void Draw() = 0;
    
protected:
    Adafruit_ILI9341* _tft;
    Adafruit_SSD1306* _oled;
};
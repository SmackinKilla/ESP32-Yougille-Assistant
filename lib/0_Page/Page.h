#pragma once
#include <stdint.h>

class Adafruit_GFX;
class PageManager;
class Page {
public:
    Page(Adafruit_GFX* tft, Adafruit_GFX* oled, PageManager* pm = nullptr) 
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
    void DrawMenu(const char* items[], int count, int currentIndex);
    void drawWinMenu(const char* winItems[], int count, int currentIndex);
    void drawModalWindow( const char* title, const char* items[], int itemCount, int selectedIdx, int x, int y, int w, int h, int maxVisibleItems = 4);
    Adafruit_GFX* _tft;
    Adafruit_GFX* _oled;
    PageManager* _pm; 
    static constexpr int SCREEN_WIDTH  = 160;
    static constexpr int SCREEN_HEIGHT = 128; 
};

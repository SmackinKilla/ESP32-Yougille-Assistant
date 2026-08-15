// HomePage.h
#pragma once
#include "Page.h"
#include "PageManager.h"

class HomePage : public Page {
public:
    HomePage(Adafruit_GFX* tft, Adafruit_GFX* oled, PageManager* pm) 
        : Page(tft, oled, pm), _currentIndex(0), _previousIndex(-1) {}

    void onShortClick() override;
    void onLongClick() override;
    void onDoubleClick() override;
    void OnEnter() override;
    void Update(uint32_t deltaTimeMs) override;
    void OnExit() override;

private:
    void DrawMenu();
    
    static constexpr int MAX_MENU_ITEMS = 10;  
    
    int _currentIndex;      
    int _previousIndex; 
};

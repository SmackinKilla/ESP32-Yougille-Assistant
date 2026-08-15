#include "WeatherPage1.h"
#include <Adafruit_GFX.h>
#include "PageManager.h"
#include <ColorPalette.h>

void WeatherPage1::onShortClick() {
    if (_pm) _pm->SwitchToIndex(PageIndex::WEATHER); 
}

void WeatherPage1::onLongClick() {
    
}

void WeatherPage1::onDoubleClick() {

}

void WeatherPage1::OnEnter() {
    screen(0)->fillScreen(COLOR_BG);
    screen(0)->setCursor(0, 0);
    screen(0)->setTextColor(COLOR_TEXT);
    screen(0)->setTextSize(1);
    screen(0)->print("Weather Page 1");
    
}

void WeatherPage1::Update(uint32_t deltaTimeMs) {

}

void WeatherPage1::OnExit() {
    
}


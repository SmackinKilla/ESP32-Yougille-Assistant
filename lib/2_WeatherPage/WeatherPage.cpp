#include "WeatherPage.h"
#include <Adafruit_ST7735.h>
#include <Adafruit_SSD1306.h>
#include "config.h"

void WeatherPage::onShortClick() {
    if (_pm) _pm->SwitchToIndex(5); 
}

void WeatherPage::onLongClick() {
    
}

void WeatherPage::onDoubleClick() {
    
}

void WeatherPage::OnEnter() {
    DrawFrame("WEATHER");
}

void WeatherPage::Update(uint32_t deltaTimeMs) {

}

void WeatherPage::OnExit() {
    
}


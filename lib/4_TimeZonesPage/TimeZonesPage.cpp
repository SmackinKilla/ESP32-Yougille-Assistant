#include "TimeZonesPage.h"
#include <Adafruit_ST7735.h>
#include <Adafruit_SSD1306.h>
#include "config.h"

void  TimeZonesPage::onShortClick() {
    if (_pm) _pm->SwitchToIndex(5);  
}

void TimeZonesPage::onLongClick() {
    
}

void TimeZonesPage::onDoubleClick() {
    
}

void TimeZonesPage::OnEnter() {
    DrawFrame("TIME ZONES");
}

void TimeZonesPage::Update(uint32_t deltaTimeMs) {
    
}

void TimeZonesPage::OnExit() {
    
}


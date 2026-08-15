#include "TimeZonesPage.h"
#include <Adafruit_GFX.h>
#include "PageManager.h"

void  TimeZonesPage::onShortClick() {
    if (_pm) _pm->SwitchToIndex(PageIndex::HOME);  
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


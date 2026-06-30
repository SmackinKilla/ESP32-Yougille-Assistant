#include "SettingsPage.h"
#include <Adafruit_ST7735.h>
#include <Adafruit_SSD1306.h>
#include "config.h"

void SettingsPage::onShortClick() {
    if (_pm) _pm->SwitchToIndex(5); 
}

void SettingsPage::onLongClick() {
    
}

void SettingsPage::onDoubleClick() {
    
}

void SettingsPage::OnEnter() {
    DrawFrame("SETTINGS");
}

void SettingsPage::Update(uint32_t deltaTimeMs) {
    
}

void SettingsPage::OnExit() {
    
}


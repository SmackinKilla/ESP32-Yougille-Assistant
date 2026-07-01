#include "SettingsPage.h"
#include <Adafruit_ST7735.h>
#include <Adafruit_SSD1306.h>
#include "PageManager.h"

void SettingsPage::onShortClick() {

}

void SettingsPage::onLongClick() {
    
}

void SettingsPage::onDoubleClick() {
    if (_pm) _pm->SwitchToIndex(PageIndex::HOME); 
}

void SettingsPage::OnEnter() {
    DrawFrame("SETTINGS");
}

void SettingsPage::Update(uint32_t deltaTimeMs) {

}

void SettingsPage::OnExit() {
    
}


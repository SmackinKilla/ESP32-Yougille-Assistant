#include "TimeZonesPage.h"
#include <Adafruit_ST7735.h>
#include <Adafruit_SSD1306.h>
#include "config.h"

void TimeZonesPage::OnEnter() {
    _tft->fillScreen(ST77XX_BLACK);
    _tft->setCursor(10, 10);
    _tft->setTextColor(ST77XX_WHITE);
    _tft->setTextSize(2);
    _tft->print("Time Zones");
}

void  TimeZonesPage::onShortClick() {
    if (_pm) _pm->SwitchToIndex(0);  // Возврат домой
}

void TimeZonesPage::onLongClick() {
    // пока ничего не делаем
}

void TimeZonesPage::Update(uint32_t deltaTimeMs) {
    // пока ничего не делаем
}

void TimeZonesPage::OnExit() {
    // пока ничего не делаем
}

void TimeZonesPage::Draw() {
    // пока ничего не делаем
}
#include "WeatherPage.h"
#include <Adafruit_ST7735.h>
#include <Adafruit_SSD1306.h>
#include "config.h"

void WeatherPage::OnEnter() {
    _tft->fillScreen(ST77XX_BLACK);
    _tft->setCursor(10, 10);
    _tft->setTextColor(ST77XX_WHITE);
    _tft->setTextSize(2);
    _tft->print("WEATHER");
}

void WeatherPage::onShortClick() {
    if (_pm) _pm->SwitchToIndex(5);  // Возврат домой
}

void WeatherPage::onLongClick() {
    // пока ничего не делаем
}

void WeatherPage::Update(uint32_t deltaTimeMs) {
    // пока ничего не делаем
}

void WeatherPage::OnExit() {
    // пока ничего не делаем
}

void WeatherPage::Draw() {
    // пока ничего не делаем
}
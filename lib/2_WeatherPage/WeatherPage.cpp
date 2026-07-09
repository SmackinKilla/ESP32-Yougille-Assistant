#include "WeatherPage.h"
#include <Adafruit_ST7735.h>
#include <Adafruit_SSD1306.h>
#include "PageManager.h"
#include "WeatherIcons.h"
#include "ColorPalette.h"

int currentWeatherCode = 701;     
float currentTemp = 24.5;        
String currentDescription = "Scattered clouds";

void WeatherPage::DrawWeatherIcons(int x, int y, int weatherCode) {
    WeatherIcon icon = getIconFromCode(weatherCode);
    const unsigned char* bitmap = getIconBitmap(icon);
    _tft->drawBitmap(x, y, bitmap, 64, 32, ST7735_WHITE);
}


void DrawGUI() {
    
}

void WeatherPage::onShortClick() {
    if (_pm) _pm->SwitchToIndex(PageIndex::HOME); 
}

void WeatherPage::onLongClick() {
    
}

void WeatherPage::onDoubleClick() {
    
}

void WeatherPage::OnEnter() {
    DrawFrame("WEATHER");
    DrawWeatherIcons(100, 30, currentWeatherCode);
    _tft->drawRect(100, 13, 64, 56, COLOR_WHITE);
    _tft->setCursor(102, 16);
    _tft->setTextColor(COLOR_TEXT);
    _tft->setTextSize(1);
    _tft->print("PREVIEW");
    _tft->drawLine(100, 24, 160, 24, COLOR_WHITE);
    /*_tft->setTextColor(ST7735_YELLOW);
    _tft->setTextSize(3);
    _tft->setCursor(50, 35);
    _tft->printf("%d°C", currentTemp);
    _tft->setTextColor(ST7735_WHITE);
    _tft->setTextSize(1);
    _tft->setCursor(10, 70);
    _tft->print(currentDescription);*/
}

void WeatherPage::Update(uint32_t deltaTimeMs) {

}

void WeatherPage::OnExit() {
    
}


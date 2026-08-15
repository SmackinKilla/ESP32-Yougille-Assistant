#include "WeatherPage.h"
#include <Adafruit_GFX.h>
#include "PageManager.h"
#include "WeatherIcons.h"
#include <ColorPalette.h>
 // debug weather API
int currentWeatherCode = 701;     
float currentTemp = 24.5;        
String currentDescription = "Cloudy";

void WeatherPage::DrawWeatherIcons(int x, int y, int weatherCode) {
    WeatherIcon icon = getIconFromCode(weatherCode);
    const unsigned char* bitmap = getIconBitmap(icon);
    screen(0)->drawBitmap(x, y, bitmap, 64, 32, COLOR_WHITE);
}


void DrawGUI() {
    
}

void WeatherPage::onShortClick() {
    
}

void WeatherPage::onLongClick() {
    if (_pm) _pm->SwitchToIndex(PageIndex::WEATHER1); 
}

void WeatherPage::onDoubleClick() {
    if (_pm) _pm->SwitchToIndex(PageIndex::HOME); 
}

void WeatherPage::OnEnter() {
    DrawFrame("WEATHER");
    DrawWeatherIcons(SCREEN_WIDTH - 50, 30, currentWeatherCode);
    screen(0)->drawFastVLine(SCREEN_WIDTH - 45, 13, 56, COLOR_WHITE);
    screen(0)->drawFastVLine(SCREEN_WIDTH - 115, 13, 56, COLOR_WHITE);
    screen(0)->drawFastHLine(0, 24, SCREEN_WIDTH, COLOR_WHITE);
    screen(0)->setCursor(SCREEN_WIDTH - 42, 16);
    screen(0)->setTextColor(COLOR_TEXT);
    screen(0)->setTextSize(1);
    
    screen(0)->print("PREVIEW");
    screen(0)->setCursor(SCREEN_WIDTH - 100, 16);

    screen(0)->print("OUTSIDE");
    screen(0)->setCursor(SCREEN_WIDTH - 112, 30);
    screen(0)->printf("T:%.1fC", currentTemp);
    screen(0)->setCursor(SCREEN_WIDTH - 112, 40);
    screen(0)->printf("H:%d%%", 60);
    screen(0)->setCursor(SCREEN_WIDTH - 112, 50);
    screen(0)->print(currentDescription);
    screen(0)->setCursor(7, 16);

    screen(0)->print("LOCAL");
    screen(0)->setCursor(2, 30);
    screen(0)->printf("T:%.1fC", 25.0);
    screen(0)->setCursor(2, 40);
    screen(0)->printf("H:%d%%", 60);

    screen(0)->drawFastHLine(0, 69, SCREEN_WIDTH, COLOR_WHITE);
    screen(0)->drawFastVLine(40, 69, 46, COLOR_WHITE);
    screen(0)->drawFastVLine(80, 69, 46, COLOR_WHITE);
    screen(0)->drawFastVLine(120, 69, 46, COLOR_WHITE);
    screen(0)->drawFastHLine(0, 80, SCREEN_WIDTH, COLOR_WHITE);

    screen(0)->setCursor(5, 72);
    screen(0)->print("test1");
    screen(0)->setCursor(5, 85);
    screen(0)->printf("T:%.iC", 25);
    screen(0)->setCursor(5, 95);
    screen(0)->printf("H:%d%%", 60);

    screen(0)->setCursor(45, 72);
    screen(0)->print("test2");
    screen(0)->setCursor(45, 85);
    screen(0)->printf("T:%iC", 25);
    screen(0)->setCursor(45, 95);
    screen(0)->printf("H:%d%%", 60);
    
    screen(0)->setCursor(85, 72);
    screen(0)->print("test3");
    screen(0)->setCursor(85, 85);
    screen(0)->printf("T:%iC", 25);
    screen(0)->setCursor(85, 95);
    screen(0)->printf("H:%d%%", 60);

    screen(0)->setCursor(125, 72);
    screen(0)->print("test4");
    screen(0)->setCursor(125, 85);
    screen(0)->printf("T:%iC", 25);
    screen(0)->setCursor(125, 95);
    screen(0)->printf("H:%d%%", 60);
}

void WeatherPage::Update(uint32_t deltaTimeMs) {

}

void WeatherPage::OnExit() {
    
}


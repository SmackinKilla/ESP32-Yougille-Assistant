#include <Arduino.h>
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_ST7735.h>
#include <Adafruit_SSD1306.h>
#include "PageManager.h"
#include "Page.h"
#include "WeatherPage.h"
#include "TasksPage.h"
#include "TimeZonesPage.h"
#include "MiniGames.h"
#include "SettingsPage.h"
#include "HomePage.h"
#include "ScreenSaver.h"
#include <string.h>
#include <OneButton.h>

  


#define TFT_CS    5    // Chip Select
#define TFT_DC    16   // Data/Command
#define TFT_RST   17   // Reset
#define TFT_BL    32   // Backlight (подсветка)
#define TFT_SCK   18   // SPI Clock
#define TFT_MOSI  23   // SPI Data

#define OLED_SDA  21   // I2C Data
#define OLED_SCL  22   // I2C Clock
#define OLED_ADDR 0x3C // Адрес OLED экрана
#define OLED_RST  -1   // Пин Reset (если нет - ставим -1)

#define BUTTON_PIN 4 

Adafruit_ST7735 tft = Adafruit_ST7735(TFT_CS, TFT_DC, TFT_RST);
Adafruit_SSD1306 oled(128, 64, &Wire, -1);

OneButton button(BUTTON_PIN, true);
PageManager pm;
WeatherPage weatherPage(&tft, &oled, &pm);
TasksPage tasksPage(&tft, &oled, &pm);
TimeZonesPage TZPage(&tft, &oled, &pm);
MiniGames minigamesPage(&tft, &oled, &pm);
SettingsPage settings(&tft, &oled, &pm);
HomePage homePage(&tft, &oled, &pm);
ScreenSaver screenSaver(&tft, &oled, &pm);



void setup() {
    Serial.begin(115200);
    tft.initR(INITR_BLACKTAB);
    tft.setRotation(1);
    tft.fillScreen(ST7735_BLACK);
    oled.begin(SSD1306_SWITCHCAPVCC, 0x3C);
    pinMode(BUTTON_PIN, INPUT_PULLUP);
    button.setClickMs(300);
    button.setPressMs(500);  
    button.attachClick([]() {
        Serial.println("Short click");
        pm.getCurrent()->onShortClick();
    });
    
    button.attachLongPressStart([]() {
        Serial.println("Long press");
        pm.getCurrent()->onLongClick();
    });      
    pm.addPage(&weatherPage); 
    pm.addPage(&tasksPage);
    pm.addPage(&TZPage); 
    pm.addPage(&minigamesPage);
    pm.addPage(&settings); 
    pm.addPage(&homePage);
    pm.addPage(&screenSaver);
    pm.getCurrent()->OnEnter();

}

void loop() {
    button.tick();

    static uint32_t lastTime = 0;
    uint32_t now = millis();
    uint32_t dt = now - lastTime;
    lastTime = now;
    
    Page* current = pm.getCurrent();
    current->Update(dt);
    current->Draw();
    
    delay(16);
}

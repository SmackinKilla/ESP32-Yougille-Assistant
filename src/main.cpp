#include <Arduino.h>
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_ST7735.h>
#include <Adafruit_SSD1306.h>
#include "PageManager.h"
#include "Page.h"
#include "HomePage.h"
#include "ScreenSaver.h"
#include <string.h>
#include <OneButton.h>

#define TFT_CS    5    // Chip Select
#define TFT_DC    2   // Data/Command
#define TFT_RST   4   // Reset
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
HomePage homePage(&tft, &oled, &pm);
ScreenSaver screenSaver(&tft, &oled);


void setup() {
    Serial.begin(115200);
    tft.initR(INITR_BLACKTAB);
    tft.setRotation(1);
    tft.fillScreen(ILI9341_BLACK);
    oled.begin(SSD1306_SWITCHCAPVCC, 0x3C);
    pinMode(BUTTON_PIN, INPUT_PULLUP);
    button.setClickTicks(300u);
    button.setPressTicks(500u); 
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

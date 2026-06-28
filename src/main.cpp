// main.cpp
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


bool lastButtonState = HIGH;      
bool currentButtonState = HIGH;   
uint32_t lastDebounceTime = 0;    
uint32_t debounceDelay = 50;      
bool buttonPressed = false; 

Adafruit_ST7735 tft = Adafruit_ST7735(TFT_CS, TFT_DC, TFT_RST);
Adafruit_SSD1306 oled(128, 64, &Wire, -1);

HomePage homePage(&tft, &oled);
ScreenSaver screenSaver(&tft, &oled);
PageManager pm;

void setup() {
    Serial.begin(115200);
    pinMode(BUTTON_PIN, INPUT_PULLUP);
    tft.initR(INITR_BLACKTAB);
    tft.setRotation(1);
    tft.fillScreen(ST7735_BLACK);
    oled.begin(SSD1306_SWITCHCAPVCC, 0x3C);
    pm.addPage(&homePage);
    pm.addPage(&screenSaver);
    pm.getCurrent()->OnEnter();

}

void loop() {
    int reading = digitalRead(BUTTON_PIN);
    
    if (reading != lastButtonState) {
        lastDebounceTime = millis();
    }
    
    if ((millis() - lastDebounceTime) > debounceDelay) {
        if (reading != currentButtonState) {
            currentButtonState = reading;
            
            if (currentButtonState == LOW) {
                pm.getCurrent()->onButtonPressed();
            }
        }
    }
    
    lastButtonState = reading;

    static uint32_t lastTime = 0;
    uint32_t now = millis();
    uint32_t dt = now - lastTime;
    lastTime = now;
    
    Page* current = pm.getCurrent();
    current->Update(dt);
    current->Draw();
    
    delay(16);
}

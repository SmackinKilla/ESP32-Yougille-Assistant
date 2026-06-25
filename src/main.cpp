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

#define TFT_CS  5
#define TFT_DC  4
#define TFT_RST 16
#define BUTTON_PIN 13
// Дисплеи
Adafruit_ST7735 tft = Adafruit_ST7735(TFT_CS, TFT_DC, TFT_RST);
Adafruit_SSD1306 oled(128, 64, &Wire, -1);

// Страницы
HomePage homePage(&tft, &oled);
ScreenSaver screenSaver(&tft, &oled);
PageManager pm;

void setup() {
    Serial.begin(115200);
    oled.begin(SSD1306_SWITCHCAPVCC, 0x3C);
    pinMode(BUTTON_PIN, INPUT_PULLUP);
    pm.addPage(&homePage);
    pm.addPage(&screenSaver);
    pm.getCurrent()->OnEnter();

}

void loop() {
    static uint32_t lastTime = 0;
    uint32_t now = millis();
    uint32_t dt = now - lastTime;
    lastTime = now;
    Page* current = pm.getCurrent();
    current->Update(dt);
    current->Draw();
    
    // Переключение страниц по кнопке
    if (digitalRead(BUTTON_PIN) == LOW) {
        delay(50); 
        if (digitalRead(BUTTON_PIN) == LOW) {
            pm.next();  
            while (digitalRead(BUTTON_PIN) == LOW);
        }
    }
    
    delay(16);
}

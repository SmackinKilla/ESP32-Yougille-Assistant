#include "TasksPage.h"
#include <Adafruit_ST7735.h>
#include <Adafruit_SSD1306.h>
#include "config.h"

void TasksPage::OnEnter() {
    _tft->fillScreen(ST77XX_BLACK);
    _tft->setCursor(10, 10);
    _tft->setTextColor(ST77XX_WHITE);
    _tft->setTextSize(2);
    _tft->print("Tasks");
}

void TasksPage::onShortClick() {
    if (_pm) _pm->SwitchToIndex(0);  // Возврат домой
}

void TasksPage::onLongClick() {
    // пока ничего не делаем
}

void TasksPage::Update(uint32_t deltaTimeMs) {
    // пока ничего не делаем
}

void TasksPage::OnExit() {
    // пока ничего не делаем
}

void TasksPage::Draw() {
    // пока ничего не делаем
}
#include "TasksPage.h"
#include <Adafruit_ST7735.h>
#include <Adafruit_SSD1306.h>
#include "PageManager.h"
#include "config.h"

void TasksPage::onShortClick() {
    if (_pm) _pm->SwitchToIndex(PageIndex::HOME);  
}

void TasksPage::onLongClick() {
    
}

void TasksPage::onDoubleClick() {
    
}

void TasksPage::OnEnter() {
    DrawFrame("TASKS");
}

void TasksPage::Update(uint32_t deltaTimeMs) {
   
}

void TasksPage::OnExit() {
   
}


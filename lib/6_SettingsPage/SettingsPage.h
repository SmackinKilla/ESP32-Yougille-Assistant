#pragma once
#include "Page.h"
#include "PageManager.h"
#include <string.h>

class SettingsPage : public Page {
public:
    SettingsPage(Adafruit_ST7735* tft, Adafruit_SSD1306* oled, PageManager* pm) 
        : Page(tft, oled, pm), _currentIndex(0), _previousIndex(-1) {}

    void onShortClick() override;
    void onLongClick() override;
    void onDoubleClick() override;
    void OnEnter() override;
    void Update(uint32_t deltaTimeMs) override;
    void OnExit() override;

private:
    // 🔒 статические константные строки
    static constexpr int SETTINGS_COUNT = 4;
    static constexpr const char* SETTINGS_ITEMS[SETTINGS_COUNT] = {
        "1. Theme",
        "2. Click Speed",
        "3. Timezone",
        "4. Reset"
    };
    
    int _currentIndex;      // текущий выбранный пункт
    int _previousIndex;     // предыдущий индекс (для оптимизации)
};

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
    static constexpr int SETTINGS_COUNT = 4;
    const char* _settingsItems[4] = {
        "1. Theme",
        "2. Click Speed",
        "3. Timezone",
        "4. Reset"
    };
    const char* _themeOptions[5] = {"Blue", "Red", "Purple", "Green", "Dark"};
    const char* _speedOptions[3] = {"Fast", "Normal", "Slow"};
    const char* _tzOptions[5] = {"UTC+0", "UTC+1", "UTC+2", "UTC+3", "UTC+4", };
    const char** _subMenus[SETTINGS_COUNT] = {_themeOptions, _speedOptions, _tzOptions, nullptr};
    const int _subMenuCounts[SETTINGS_COUNT] = {5, 3, 5, 0};
    int _currentIndex;
    int _previousIndex;
    bool _IsWindowOpen = false;
    int _WindowIndex = 0;
};

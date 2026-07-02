#include "SettingsPage.h"
#include "ColorPalette.h"
#include <Adafruit_ST7735.h>
#include "PageManager.h"

// 🔒 определение статического массива
const char* SettingsPage::SETTINGS_ITEMS[SettingsPage::SETTINGS_COUNT];

void SettingsPage::onShortClick() {
    _currentIndex++;
    if (_currentIndex >= SETTINGS_COUNT) _currentIndex = 0;
    _previousIndex = -1;
}

void SettingsPage::onLongClick() {
    // Логика для входа в выбранную настройку
    switch (_currentIndex) {
        case 0: /* смена темы */ break;
        case 1: /* смена скорости клика */ break;
        case 2: /* смена часового пояса */ break;
        case 3: /* сброс настроек */ break;
    }
}

void SettingsPage::onDoubleClick() {
    // Возврат в HOME
    if (_pm) _pm->SwitchToIndex(PageIndex::HOME);
}

void SettingsPage::OnEnter() {
    DrawFrame("SETTINGS");
    Page::DrawMenu(SETTINGS_ITEMS, SETTINGS_COUNT, _currentIndex);
}

void SettingsPage::Update(uint32_t deltaTimeMs) {
    if (_currentIndex != _previousIndex) {
        Page::DrawMenu(SETTINGS_ITEMS, SETTINGS_COUNT, _currentIndex);
        _previousIndex = _currentIndex;
    }
}

void SettingsPage::OnExit() {
    _tft->fillRect(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, COLOR_BG);
}

#include "SettingsPage.h"
#include "ColorPalette.h"
#include <Adafruit_ST7735.h>
#include "PageManager.h"

void SettingsPage::drawWindow() {
    const char** items = _subMenus[_currentIndex];
    int count = _subMenuCounts[_currentIndex];
    if (items == nullptr || count == 0) return;
    drawModalWindow(_settingsItems[_currentIndex], items, count, _WindowIndex, 33, 30, 100, 63);
}

void SettingsPage::onShortClick() {
    if (_IsWindowOpen) {
        _WindowIndex++;
        if (_WindowIndex >= _subMenuCounts[_currentIndex]) _WindowIndex = 0;
        drawWindow();
    } else {
        _currentIndex++;
        if (_currentIndex >= SETTINGS_COUNT) _currentIndex = 0;
        _previousIndex = -1;
    }
}

void SettingsPage::onLongClick() {
    if (_IsWindowOpen) {
        switch (_currentIndex) {
            case 0: g_settings.theme = static_cast<Theme>(_WindowIndex); break;
            case 1: g_settings.clickSpeed = static_cast<ClickSpeed>(_WindowIndex); break;
            case 2: g_settings.timezoneOffset = _WindowIndex; break;
            case 3: g_settings.reset(); break;
        }
        g_settings.save();
        applyTheme();

        _IsWindowOpen = false;
        OnEnter();
    } else {
        if (_subMenus[_currentIndex] != nullptr) {
            _IsWindowOpen = true;
            _WindowIndex = 0;
            drawWindow();
        } else if (_currentIndex == 3) {
            g_settings.reset();
            applyTheme();
            OnEnter();
        }
    }
}

void SettingsPage::onDoubleClick() {
    if (_pm) _pm->SwitchToIndex(PageIndex::HOME);
}

void SettingsPage::OnEnter() {
    DrawFrame("SETTINGS");
    Page::DrawMenu(_settingsItems, SETTINGS_COUNT, _currentIndex);
}

void SettingsPage::Update(uint32_t deltaTimeMs) {
    if (_currentIndex != _previousIndex) {
        Page::DrawMenu(_settingsItems, SETTINGS_COUNT, _currentIndex);
        _previousIndex = _currentIndex;
    }
}

void SettingsPage::OnExit() {
    _tft->fillRect(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, COLOR_BG);
}

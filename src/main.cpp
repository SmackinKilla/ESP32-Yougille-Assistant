#include <Arduino.h>
#include <SPI.h>
#include <Wire.h>
#include <OneButton.h>
#include <Adafruit_GFX.h>
#include "PageManager.h"
#include "Page.h"
#include "WeatherPage.h"
#include "TasksPage.h"
#include "TimeZonesPage.h"
#include "MiniGames.h"
#include "SettingsPage.h"
#include "HomePage.h"
#include "ScreenSaver.h"
#include "ColorPalette.h"
#include "SystemSettings.h"

#include "DisplayManager.h"
#include "DisplayTypes.h"

#define BUTTON_PIN 4

static const DisplayConfig DISPLAY_CONFIGS[] = {
    {
        DisplayType::ST7735,
        160,
        128,
        1,

        5,
        16,
        17,
        32,

        0,
        -1,
        -1
    },

    {
        DisplayType::SSD1306,
        128,
        64,
        0,

        -1,
        -1,
        -1,
        -1,

        0x3C,
        21,
        22
    }
};

static constexpr uint8_t DISPLAY_COUNT = sizeof(DISPLAY_CONFIGS) / sizeof(DISPLAY_CONFIGS[0]);

DisplayManager displays;
OneButton button(BUTTON_PIN, true);
PageManager pm;

void setup() {
    Serial.begin(115200);

    if (!displays.begin(DISPLAY_CONFIGS, DISPLAY_COUNT)) {
        Serial.println("[HW] Display init failed");
        while (true) {
            delay(1000);
        }
    }

    g_settings.load();
    applyTheme();

    displays.gfx(0)->fillScreen(COLOR_BG);
    displays.flushAll();

    static WeatherPage weatherPage(displays.gfx(0), displays.gfx(1), &pm);
    static TasksPage tasksPage(displays.gfx(0), displays.gfx(1), &pm);
    static TimeZonesPage TZPage(displays.gfx(0), displays.gfx(1), &pm);
    static MiniGames minigamesPage(displays.gfx(0), displays.gfx(1), &pm);
    static SettingsPage settings(displays.gfx(0), displays.gfx(1), &pm);
    static HomePage homePage(displays.gfx(0), displays.gfx(1), &pm);
    static ScreenSaver screenSaver(displays.gfx(0), displays.gfx(1), &pm);

    pinMode(BUTTON_PIN, INPUT_PULLUP);

    button.setClickMs(200);
    button.setPressMs(500);

    button.attachClick([]() {
        Page* p = pm.getCurrent();
        if (p) p->onShortClick();
    });

    button.attachDoubleClick([]() {
        Page* p = pm.getCurrent();
        if (p) p->onDoubleClick();
    });

    button.attachLongPressStart([]() {
        Page* p = pm.getCurrent();
        if (p) p->onLongClick();
    });

    pm.registerPage(PageIndex::WEATHER, &weatherPage, TitleInfo("Weather", false, true));
    pm.registerPage(PageIndex::TASKS, &tasksPage, TitleInfo("Tasks", true, true));
    pm.registerPage(PageIndex::TIMEZONES, &TZPage, TitleInfo("World Time", false, true));
    pm.registerPage(PageIndex::GAMES, &minigamesPage, TitleInfo("Gambling", false, true));
    pm.registerPage(PageIndex::SETTINGS, &settings, TitleInfo("Settings", false, true));
    pm.registerPage(PageIndex::HOME, &homePage, TitleInfo("Home", false, false));
    pm.registerPage(PageIndex::SCREENSAVER, &screenSaver, TitleInfo("ScreenSaver", false, false));

    pm.SwitchToIndex(PageIndex::HOME);

    displays.flushAll();
}

void loop() {
    button.tick();

    static uint32_t lastTime = 0;

    uint32_t now = millis();
    uint32_t dt = now - lastTime;
    lastTime = now;

    Page* current = pm.getCurrent();

    if (current) {
        current->Update(dt);
    }

    displays.flushAll();

    delay(16);
}
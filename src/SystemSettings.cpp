#include "SystemSettings.h"
#include <Preferences.h>
#include <Arduino.h>

SystemSettings g_settings;

const char* getThemeName(Theme t) {
    switch (t) {
        case Theme::BLUE:   return "Blue";
        case Theme::RED:    return "Red";
        case Theme::PURPLE: return "Purple";
        case Theme::GREEN:  return "Green";
        case Theme::DARK:   return "Dark";
        default:            return "Unknown";
    }
}

const char* getClickSpeedName(ClickSpeed s) {
    switch (s) {
        case ClickSpeed::FAST:   return "Fast (200ms)";
        case ClickSpeed::NORMAL: return "Normal (300ms)";
        case ClickSpeed::SLOW:   return "Slow (450ms)";
        default:                 return "Unknown";
    }
}

uint16_t getClickMs(ClickSpeed s) {
    switch (s) {
        case ClickSpeed::FAST:   return 200;
        case ClickSpeed::NORMAL: return 300;
        case ClickSpeed::SLOW:   return 450;
        default:                 return 300;
    }
}

void SystemSettings::load() {
    Preferences prefs;
    prefs.begin("app", true); 
    uint8_t t = prefs.getUChar("theme", (uint8_t)Theme::BLUE);
    uint8_t cs = prefs.getUChar("clkSpd", (uint8_t)ClickSpeed::NORMAL);

    timezoneOffset = prefs.getChar("tz", 3);
    use24hFormat = prefs.getBool("24h", true);
    prefs.end();
    
    if (t >= (uint8_t)Theme::COUNT) t = 0;
    if (cs >= (uint8_t)ClickSpeed::COUNT) cs = 1;
    
    theme = (Theme)t;
    clickSpeed = (ClickSpeed)cs;
    
    Serial.printf("[Settings] Loaded: theme=%s, speed=%s, tz=%d, 24h=%d\n",
                  getThemeName(theme), getClickSpeedName(clickSpeed),
                  timezoneOffset, use24hFormat);
}

void SystemSettings::save() {
    Preferences prefs;
    prefs.begin("app", false);  
    prefs.putUChar("theme", (uint8_t)theme);
    prefs.putUChar("clkSpd", (uint8_t)clickSpeed);
    prefs.putChar("tz", timezoneOffset);
    prefs.putBool("24h", use24hFormat);
    prefs.end();
    Serial.println("[Settings] Saved to NVS");
}

void SystemSettings::reset() {
    Preferences prefs;
    prefs.begin("app", false);
    prefs.clear();
    prefs.end();
    *this = SystemSettings();
    save();
    Serial.println("[Settings] Reset to defaults");
}
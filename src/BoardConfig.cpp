#include "BoardConfig.h"
#include <Arduino.h>
#include <string.h>

BoardConfig g_board;

void BoardConfig::setDefaults() {
    displayCount = 2;
    memset(wifiSsid, 0, sizeof(wifiSsid));
    memset(wifiPass, 0, sizeof(wifiPass));
    displays[0] = DisplayConfig{ "main", DisplayType::ST7735, 160, 128, 1, 5, 16, 17, 32, 0, -1, -1 };
    displays[1] = DisplayConfig{ "oled", DisplayType::SSD1306, 128, 64, 0, -1, -1, -1, -1, 0x3C, 21, 22 };
}

#ifdef NATIVE_SIM
bool BoardConfig::load() { return false; }
bool BoardConfig::save() { return false; }
#else

#include <LittleFS.h>
#include <ArduinoJson.h>

static DisplayType parseType(const char* t) {
    if (!t) return DisplayType::None;
    if (strcmp(t, "ST7735") == 0) return DisplayType::ST7735;
    if (strcmp(t, "SSD1306") == 0) return DisplayType::SSD1306;
    return DisplayType::None;
}

static const char* typeName(DisplayType t) {
    switch (t) {
        case DisplayType::ST7735: return "ST7735";
        case DisplayType::SSD1306: return "SSD1306";
        default: return "None";
    }
}

bool BoardConfig::load() {
    if (!LittleFS.begin(true)) {
        Serial.println("[Board] LittleFS mount failed");
        return false;
    }
    File f = LittleFS.open("/config.json", "r");
    if (!f) {
        Serial.println("[Board] config.json not found");
        return false;
    }

    JsonDocument doc;
    DeserializationError err = deserializeJson(doc, f);
    f.close();
    if (err) {
        Serial.printf("[Board] parse error: %s\n", err.c_str());
        return false;
    }


    JsonObject wifi = doc["wifi"];
    if (!wifi.isNull()) {
        strlcpy(wifiSsid, wifi["ssid"] | "", sizeof(wifiSsid));
        strlcpy(wifiPass, wifi["pass"] | "", sizeof(wifiPass));
    }


    JsonArray arr = doc["displays"];
    if (arr.isNull()) return false;

    uint8_t n = 0;
    for (JsonObject o : arr) {
        if (n >= 4) break;
        DisplayConfig& d = displays[n];
        strlcpy(d.name, o["name"] | "", sizeof(d.name));
        d.type     = parseType(o["type"] | "");
        d.width    = o["width"]    | 0;
        d.height   = o["height"]   | 0;
        d.rotation = o["rotation"] | 0;
        d.cs       = o["cs"]       | -1;
        d.dc       = o["dc"]       | -1;
        d.rst      = o["rst"]      | -1;
        d.bl       = o["bl"]       | -1;
        d.i2cAddr  = o["addr"]     | 0;
        d.sda      = o["sda"]      | -1;
        d.scl      = o["scl"]      | -1;
        if (d.type != DisplayType::None && d.name[0] != '\0') n++;
    }
    displayCount = n;
    return n > 0;
}

bool BoardConfig::save() {
    JsonDocument doc;


    JsonObject wifi = doc["wifi"].to<JsonObject>();
    wifi["ssid"] = wifiSsid;
    wifi["pass"] = wifiPass;


    JsonArray arr = doc["displays"].to<JsonArray>();
    for (uint8_t i = 0; i < displayCount; i++) {
        JsonObject o = arr.add<JsonObject>();
        o["name"]     = displays[i].name;
        o["type"]     = typeName(displays[i].type);
        o["width"]    = displays[i].width;
        o["height"]   = displays[i].height;
        o["rotation"] = displays[i].rotation;
        o["cs"]       = displays[i].cs;
        o["dc"]       = displays[i].dc;
        o["rst"]      = displays[i].rst;
        o["bl"]       = displays[i].bl;
        o["addr"]     = displays[i].i2cAddr;
        o["sda"]      = displays[i].sda;
        o["scl"]      = displays[i].scl;
    }
    File f = LittleFS.open("/config.json", "w");
    if (!f) return false;
    serializeJson(doc, f);
    f.close();
    return true;
}
#endif
#pragma once
#include <stdint.h>
#include "DisplayTypes.h"

struct BoardConfig {
    char wifiSsid[32] = "";    
    char wifiPass[64] = "";
    DisplayConfig displays[4];
    uint8_t displayCount = 0;

    void setDefaults();
    bool load();
    bool save();  
};

extern BoardConfig g_board;
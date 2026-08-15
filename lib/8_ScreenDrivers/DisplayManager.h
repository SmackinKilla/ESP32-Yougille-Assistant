#pragma once

#include <stdint.h>

#include "IDisplay.h"
#include "DisplayTypes.h"

IDisplay* createDisplay(const DisplayConfig& cfg);

class DisplayManager {
public:
    static constexpr uint8_t MAX_DISPLAYS = 4;

    bool begin(const DisplayConfig* configs, uint8_t count) {
        if (configs == nullptr) return false;

        if (count > MAX_DISPLAYS) {
            count = MAX_DISPLAYS;
        }

        _count = count;

        for (uint8_t i = 0; i < _count; i++) {
            _drivers[i] = createDisplay(configs[i]);

            if (_drivers[i] == nullptr) {
                return false;
            }

            if (!_drivers[i]->begin()) {
                return false;
            }
        }

        return true;
    }

    IDisplay* get(uint8_t index) {
        if (index >= _count) return nullptr;
        return _drivers[index];
    }

    Adafruit_GFX* gfx(uint8_t index) {
        IDisplay* display = get(index);
        return display ? display->gfx() : nullptr;
    }

    void flushAll() {
        for (uint8_t i = 0; i < _count; i++) {
            if (_drivers[i]) {
                _drivers[i]->flush();
            }
        }
    }

private:
    IDisplay* _drivers[MAX_DISPLAYS] = {};
    uint8_t _count = 0;
};
#include "DisplayManager.h"
#ifdef NATIVE_SIM
#include "EmuDisplay.h"
#else
#include "ST7735Driver.h"
#include "SSD1306Driver.h"
#endif
IDisplay *createDisplay(const DisplayConfig &cfg) {
#ifdef NATIVE_SIM
    return new EmuDisplay(cfg);
#else
    switch (cfg.type) {
        case DisplayType::ST7735:
            return new St7735Display(cfg);

        case DisplayType::SSD1306:
            return new Ssd1306Display(cfg);

        default:
            return nullptr;
    }
#endif
}
#include <Adafruit_ST7735.h>
#include "ColorPalette.h"

uint16_t COLOR_BLUE   = ST77XX_BLUE;
uint16_t COLOR_WHITE  = ST77XX_WHITE;
uint16_t COLOR_BLACK  = ST77XX_BLACK;
uint16_t COLOR_RED    = ST77XX_RED;
uint16_t COLOR_GREEN  = ST77XX_GREEN;
uint16_t COLOR_CYAN   = ST77XX_CYAN;
uint16_t COLOR_YELLOW = ST77XX_YELLOW;

uint16_t COLOR_BG     = ST77XX_BLUE;
uint16_t COLOR_TEXT   = ST77XX_WHITE;
uint16_t COLOR_ACCENT = ST77XX_WHITE;

void applyTheme() {
    switch (g_settings.theme) {
        case Theme::BLUE:
            COLOR_BG     = ST77XX_BLUE;
            COLOR_TEXT   = ST77XX_WHITE;
            COLOR_ACCENT = ST77XX_WHITE;
            break;
            
        case Theme::RED:
            COLOR_BG     = 0x5000; 
            COLOR_TEXT   = ST77XX_WHITE;
            COLOR_ACCENT = ST77XX_YELLOW;
            break;
            
        case Theme::PURPLE:
            COLOR_BG     = 0x3006; 
            COLOR_TEXT   = ST77XX_WHITE;
            COLOR_ACCENT = 0xF81F; 
            break;
            
        case Theme::GREEN:
            COLOR_BG     = ST77XX_BLACK;
            COLOR_TEXT   = 0x07E0; 
            COLOR_ACCENT = ST77XX_WHITE;
            break;
            
        case Theme::DARK:
            COLOR_BG     = ST77XX_BLACK;
            COLOR_TEXT   = 0xCE79; 
            COLOR_ACCENT = 0xFBE0;
            break;
    }
}
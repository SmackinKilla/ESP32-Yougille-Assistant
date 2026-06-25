#pragma once
#include "Page.h"
#include "Card.h"

class CardPage : public Page {
    public:
        CardPage(Adafruit_ILI9341* tft, Adafruit_SSD1306* oled, uint8_t pageNumber)
        : Page(tft, oled), _pageNumber(pageNumber) {}

    void loadCard(uint8_t index, Card card);
    void setCardCount(uint8_t count);
    void clearCards();
    void OnEnter() override;
    void Update(uint32_t dt) override;
    void OnExit() override;
    void Draw() override;

    private:
        Card _cards[6];
        uint8_t _cardcount = 0;
        uint8_t _pageNumber;
        bool _needsRedraw = true;
};
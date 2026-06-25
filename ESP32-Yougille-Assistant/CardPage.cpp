#include "CardPage.h"
#include <Adafruit_ILI9341.h>
#include <Adafruit_SSD1306.h>

void CardPage::loadCard(uint8_t index, Card card) {
    if(index < 6) {
        _cards[index] = card;
        _needsRedraw = true;
    }
}
void CardPage::setCardCount(uint8_t count) {
    if(count <= 6) {
        _cardcount = count;
        _needsRedraw = true;
    }
}
void CardPage::clearCards() {
    _cardcount = 0;
    _needsRedraw = true;
}
void CardPage::OnEnter() {
    _needsRedraw = true;
}
void CardPage::Update(uint32_t dt) {

}
void CardPage::OnExit () {

}
void CardPage::Draw() {
    if(!_needsRedraw) return;
}
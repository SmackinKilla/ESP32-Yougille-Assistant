#ifdef NATIVE_SIM
#include "Arduino.h"
#include "Adafruit_ST7735.h"
#include "OneButton.h"
#include <SFML/Graphics.hpp>

extern Adafruit_ST7735 tft;
extern OneButton button;
extern void setup();
extern void loop();   // Твой loop() из core.cpp

int main() {
    setup();

    sf::RenderWindow* win = tft.getWindow();

    while (win->isOpen()) {
        while (auto event = win->pollEvent()) {
            if (event->is<sf::Event::Closed>()) win->close();
        }

        // ПРОБЕЛ = кнопка (удержание = long click)
        bool pressed = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space);
        button.simulateState(pressed);

        loop();          // Вся твоя логика: button.tick(), pm.Update() и т.д.
        tft.display();   // Вывод фреймбуфера в окно

        sf::sleep(sf::milliseconds(16)); // ~60 FPS, не грузим CPU
    }
    return 0;
}
#endif
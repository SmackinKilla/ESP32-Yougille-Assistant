#ifdef NATIVE_SIM

#include "Arduino.h"
#include "DisplayManager.h"
#include "EmuDisplay.h"
#include "OneButton.h"

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <vector>
#include <cstdint>
#include <optional>

extern DisplayManager displays;
extern OneButton button;

extern void setup();
extern void loop();

static void rgb565ToRgba(uint16_t color, std::uint8_t *out) {
    std::uint8_t r5 = (color >> 11) & 0x1F;
    std::uint8_t g6 = (color >> 5) & 0x3F;
    std::uint8_t b5 = color & 0x1F;

    out[0] = (r5 << 3) | (r5 >> 2);
    out[1] = (g6 << 2) | (g6 >> 4);
    out[2] = (b5 << 3) | (b5 >> 2);
    out[3] = 255;
}

int main() {
    setup();

    EmuDisplay *mainDisplay = dynamic_cast<EmuDisplay *>(displays.get("main"));
    if (!mainDisplay) {
        Serial.println("[Emu] Main display is not EmuDisplay");
        return 1;
    }

    const unsigned int width = (unsigned int)mainDisplay->width();
    const unsigned int height = (unsigned int)mainDisplay->height();
    const unsigned int scale = 1;

    sf::RenderWindow window(
        sf::VideoMode({width * scale, height * scale}),
        "ESP32 UI Emulator"
    );

    window.setFramerateLimit(60);

    sf::Texture texture({width, height});
    texture.setSmooth(false);

    std::vector<std::uint8_t> pixels((size_t)width * height * 4);

    while (window.isOpen()) {
        while (const std::optional event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>()) {
                window.close();
            }
        }

        bool pressed = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space);

        button.simulateState(pressed);

        loop();

        const uint16_t *fb = mainDisplay->framebuffer();

        for (size_t i = 0; i < (size_t)width * height; ++i) {
            rgb565ToRgba(fb[i], &pixels[i * 4]);
        }

        texture.update(pixels.data());

        sf::Sprite sprite(texture);
        sprite.setScale({(float)scale, (float)scale});

        window.clear(sf::Color::Black);
        window.draw(sprite);
        window.display();
    }

    return 0;
}

#endif // NATIVE_SIM
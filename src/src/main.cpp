#include <SFML/Graphics.hpp>
#include "ImageClass.hpp"
#include <iostream>
#include "Transform.h"

int main(int argc, char* argv[]) {
    // Load image or create blank
    Image* img;
    if (argc > 1) {
        std::cout << "Loading image: " << argv[1] << std::endl;
        img = new Image(argv[1]);
    } else {
        std::cout << "No image provided. Creating blank canvas." << std::endl;
        img = new Image(800, 600, sf::Color::White);
    }

    sf::RenderWindow window(
        sf::VideoMode({img->getWidth(), img->getHeight()}),
        "SFML Image Test"
    );
    window.setFramerateLimit(60);

    Transform trans(*img);
    bool isDrawing = false;

    while (window.isOpen()) {

        while (auto event = window.pollEvent()) {

            // Window close
            if (event->is<sf::Event::Closed>()) {
                window.close();
            }

            // Mouse pressed
            if (const auto* mousePressed = event->getIf<sf::Event::MouseButtonPressed>()) {
                if (mousePressed->button == sf::Mouse::Button::Left) {
                    isDrawing = true;
                }
            }

            // Mouse released
            if (const auto* mouseReleased = event->getIf<sf::Event::MouseButtonReleased>()) {
                if (mouseReleased->button == sf::Mouse::Button::Left) {
                    isDrawing = false;
                }
            }

            // Keyboard input
            if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>()) {

                // Brightness
                if (keyPressed->code == sf::Keyboard::Key::P) {
                    trans.adjustBrightness(20);
                }

                // Rotate CW
                if (keyPressed->code == sf::Keyboard::Key::R) {
                    trans.Rotate(90);
                    window.create(
                        sf::VideoMode({img->getWidth(), img->getHeight()}),
                        "SFML Image Test"
                    );
                }

                // Rotate CCW
                if (keyPressed->code == sf::Keyboard::Key::T) {
                    trans.Rotate(270);
                    window.create(
                        sf::VideoMode({img->getWidth(), img->getHeight()}),
                        "SFML Image Test"
                    );
                }
            }
        }

        // Drawing while mouse is held
        if (isDrawing) {
            sf::Vector2i mousePos = sf::Mouse::getPosition(window);
            if (mousePos.x >= 0 && mousePos.x < img->getWidth() &&
                mousePos.y >= 0 && mousePos.y < img->getHeight()) {

                for (int dy = -1; dy <= 1; dy++) {
                    for (int dx = -1; dx <= 1; dx++) {
                        img->setPixel(mousePos.x + dx, mousePos.y + dy, sf::Color::Black);
                    }
                }
            }
        }

        // Rendering
        window.clear();
        img->draw(window);
        window.display();
    }

    delete img;
    return 0;
}

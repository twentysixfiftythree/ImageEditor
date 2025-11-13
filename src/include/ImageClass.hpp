#pragma once
#include <SFML/Graphics.hpp>

class Image {
private:
    sf::Image image;
    sf::Texture texture;
    sf::Sprite sprite;
    unsigned int width;
    unsigned int height;
    bool needsUpdate;

public:
    Image(unsigned int w, unsigned int h, const sf::Color& fillColor = sf::Color::White) 
        : width(w), height(h), needsUpdate(true), 
          image({w, h}, fillColor),
          texture(sf::Vector2u(w, h)),
          sprite(texture) {
    }

    // constructor to load from file
    Image(const std::string& filename) 
        : needsUpdate(false), texture(sf::Vector2u(1, 1)), sprite(texture) {
        if (!image.loadFromFile(filename)) {
            // If loading fails, create a blank 800x600 image
            width = 800;
            height = 600;
            image = sf::Image({width, height}, sf::Color::White);
        } else {
            width = image.getSize().x;
            height = image.getSize().y;
        }
        texture = sf::Texture(sf::Vector2u(width, height));
        texture.update(image);
        sprite.setTexture(texture, true);
    }

    // set a single pixel
    void setPixel(unsigned int x, unsigned int y, const sf::Color& color) {
        if (x < width && y < height) {
            image.setPixel({x, y}, color);
            needsUpdate = true;
        }
    }

    // get the pixel color
    sf::Color getPixel(unsigned int x, unsigned int y) const {
        if (x < width && y < height) {
            return image.getPixel({x, y});
        }
        return sf::Color::Black;
    }

    // update the texture from the image data
    // the texture in sfml is like the thing that is rendered in graphics.
    void updateTexture() {
        if (needsUpdate) {
            texture.update(image);
            needsUpdate = false;
        }
    }

    // draw to a render target
    void draw(sf::RenderTarget& target) {
        updateTexture();
        target.draw(sprite);
    }

    // Get dimensions
    unsigned int getWidth() const { return width; }
    unsigned int getHeight() const { return height; }
};
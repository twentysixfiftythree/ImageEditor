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
    void updateTexture() {
        if (needsUpdate) {
            texture.update(image);
            needsUpdate = false;
        }
    }

    // draw image to the screen (target)
    void draw(sf::RenderTarget& target) {
        updateTexture();
        // this is probably jank cause it's hardcodedish , but we can fix later. this sets the image position
        // the reason the formula is like this is because sfml places the sprite's position at its top-left corner
        //also for whatever reason, set position takes in floats and not ints.
        sf::FloatRect bounds = sprite.getLocalBounds();
        
        sf::Vector2u targetSize = target.getSize();
        float centerX = targetSize.x / 2.f;
        float centerY = targetSize.y / 2.f;

        sprite.setOrigin({bounds.size.x / 2.f, bounds.size.y / 2.f});
        sprite.setPosition({centerX, centerY});

        target.draw(sprite);

    }

    // Get dimensions
    unsigned int getWidth() const { return width; }
    unsigned int getHeight() const { return height; }


    //  SAFE COPY FUNCTION REQUIRED FOR ROTATION

    void copyFrom(const Image& other) {
        width = other.width;
        height = other.height;

        // deep copy pixel data
        image = other.image;

        // recreate texture with new size
        texture = sf::Texture(sf::Vector2u(width, height));
        texture.update(image);

        // rebind sprite
        sprite.setTexture(texture, true);

        needsUpdate = false;
    }
};

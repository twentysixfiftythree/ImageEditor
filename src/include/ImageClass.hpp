#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

class Image {
private:
    sf::Image image;
    sf::Texture texture;
    sf::Sprite sprite;
    unsigned int width;
    unsigned int height;
    bool needsUpdate;
    bool grayscaleApplied = false;

public:
    Image(unsigned int w, unsigned int h, const sf::Color& fillColor = sf::Color::White) 
        : width(w), height(h), needsUpdate(true), 
          image({w, h}, fillColor),
          sprite(texture) {
        if (!texture.resize(sf::Vector2u(w, h))) {
            std::cerr << "Failed to create texture of size " << w << "x" << h << std::endl;
        }
        texture.update(image);
    }

    // constructor to load from file
    Image(const std::string& filename) 
        : needsUpdate(false), sprite(texture) {
        if (!image.loadFromFile(filename)) {
            // If loading fails, create a blank 800x600 image
            width = 800;
            height = 600;
            image = sf::Image({width, height}, sf::Color::White);
        } else {
            width = image.getSize().x;
            height = image.getSize().y;
        }

        if (!texture.resize(sf::Vector2u(width, height))) {
            std::cerr << "Failed to create texture of size " << width << "x" << height << std::endl;
        }
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

    // Save image to file
    bool saveToFile(const std::string& filename) {
        updateTexture(); // Ensure texture is up to date
        return image.saveToFile(filename);
    }

    // Draw a circle at a position (for brush drawing)
    void drawBrush(int centerX, int centerY, int brushSize, const sf::Color& color) {
        int radius = brushSize / 2;
        for (int dy = -radius; dy <= radius; ++dy) {
            for (int dx = -radius; dx <= radius; ++dx) {
                if (dx * dx + dy * dy <= radius * radius) {
                    int x = centerX + dx;
                    int y = centerY + dy;
                    if (x >= 0 && x < static_cast<int>(width) && y >= 0 && y < static_cast<int>(height)) {
                        setPixel(x, y, color);
                    }
                }
            }
        }
    }

    // Convert window coordinates to image coordinates
    bool windowToImageCoords(const sf::Vector2f& windowPos, const sf::Vector2u& windowSize, int& imageX, int& imageY) const {
        // Get sprite position and bounds
        sf::FloatRect bounds = sprite.getLocalBounds();
        float centerX = windowSize.x / 2.f;
        float centerY = windowSize.y / 2.f;
        
        // Calculate sprite position (top-left corner)
        float spriteLeft = centerX - bounds.size.x / 2.f;
        float spriteTop = centerY - bounds.size.y / 2.f;
        
        // Convert to image coordinates
        float relX = windowPos.x - spriteLeft;
        float relY = windowPos.y - spriteTop;
        
        // Check if within bounds
        if (relX >= 0 && relX < bounds.size.x && relY >= 0 && relY < bounds.size.y) {
            imageX = static_cast<int>(relX);
            imageY = static_cast<int>(relY);
            return true;
        }
        return false;
    }

    //  SAFE COPY FUNCTION REQUIRED FOR ROTATION

    void copyFrom(const Image& other) {
        width = other.width;
        height = other.height;

        // deep copy pixel data
        image = other.image;

        // recreate texture with new size
        if (!texture.resize(sf::Vector2u(width, height))) {
            std::cerr << "Failed to resize texture to " << width << "x" << height << std::endl;
        }
        texture.update(image);

        // rebind sprite
        sprite.setTexture(texture, true);

        needsUpdate = false;
    }
};

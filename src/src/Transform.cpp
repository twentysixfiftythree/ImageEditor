#include "Transform.h"
#include <iostream>
#include <SFML/Graphics.hpp>


// Brightness


void Transform::adjustBrightness(signed int coefficient) {
    unsigned int width = image.getWidth();
    unsigned int height = image.getHeight();

    for (unsigned int y = 0; y < height; ++y) {
        for (unsigned int x = 0; x < width; ++x) {

            sf::Color pixel = image.getPixel(x, y);

            int r = static_cast<int>(pixel.r) + coefficient;
            int g = static_cast<int>(pixel.g) + coefficient;
            int b = static_cast<int>(pixel.b) + coefficient;

            // manual clamp (min/max)
            pixel.r = (r < 0 ? 0 : (r > 255 ? 255 : r));
            pixel.g = (g < 0 ? 0 : (g > 255 ? 255 : g));
            pixel.b = (b < 0 ? 0 : (b > 255 ? 255 : b));

            image.setPixel(x, y, pixel);
        }
    }

    image.updateTexture();
}

// 90-degree Rotation


void Transform::Rotate(int rotation) {
    // Normalize: 0, 90, 180, 270
    rotation = ((rotation % 360) + 360) % 360;

    unsigned int w = image.getWidth();
    unsigned int h = image.getHeight();

    // Create new rotated image with swapped w/h when needed
    Image rotated(
        (rotation == 90 || rotation == 270) ? h : w,
        (rotation == 90 || rotation == 270) ? w : h,
        sf::Color::White
    );

    if (rotation == 0)
        return;

    for (unsigned int y = 0; y < h; ++y) {
        for (unsigned int x = 0; x < w; ++x) {

            sf::Color c = image.getPixel(x, y);

            if (rotation == 90) {
                rotated.setPixel(h - 1 - y, x, c);
            }
            else if (rotation == 180) {
                rotated.setPixel(w - 1 - x, h - 1 - y, c);
            }
            else if (rotation == 270) {
                rotated.setPixel(y, w - 1 - x, c);
            }
        }
    }

    // Copy into existing Image
    image.copyFrom(rotated);
    image.updateTexture();
}

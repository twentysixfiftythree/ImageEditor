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

void Transform::saveOriginalImage() {
    if (!originalImage) {
        originalImage = std::make_unique<Image>(image.getWidth(), image.getHeight());
        originalImage->copyFrom(image);
    }
}

void Transform::GrayScale(float amount = 1.0f) {
    if (amount < 0.0f)
        amount = 0.0f;
    else if (amount > 1.0f)
        amount = 1.0f;

    // Save original before first grayscale application
    if (!grayScaleActive) {
        saveOriginalImage();
    }

    unsigned int width = image.getWidth();
    unsigned int height = image.getHeight();

    const float minVal = 0.0f;
    const float maxVal = 255.0f;

    for (unsigned int y = 0; y < height; ++y) {
        for (unsigned int x = 0; x < width; ++x) {
            sf::Color c = image.getPixel(x, y);

            // accumulate grayscale
            float gray = 0.299f * static_cast<float>(c.r) + 0.587f * static_cast<float>(c.g) +
                         0.114f * static_cast<float>(c.b);

            // R
            float r = (1.0f - amount) * static_cast<float>(c.r) + amount * gray;
            if (r < minVal)
                r = minVal;
            else if (r > maxVal)
                r = maxVal;

            // G
            float g = (1.0f - amount) * static_cast<float>(c.g) + amount * gray;
            if (g < minVal)
                g = minVal;
            else if (g > maxVal)
                g = maxVal;

            // B
            float b = (1.0f - amount) * static_cast<float>(c.b) + amount * gray;
            if (b < minVal)
                b = minVal;
            else if (b > maxVal)
                b = maxVal;

            sf::Color out(static_cast<std::uint8_t>(r + 0.5f), static_cast<std::uint8_t>(g + 0.5f),
                          static_cast<std::uint8_t>(b + 0.5f), c.a);

            image.setPixel(x, y, out);
        }
    }

    grayScaleActive = true;
    // texture update
    image.updateTexture();
}

void Transform::revertGrayScale() {
    if (originalImage && grayScaleActive) {
        image.copyFrom(*originalImage);
        image.updateTexture();
        grayScaleActive = false;
        originalImage.reset();
    }
}


// contrast transform
void Transform::adjustContrast(int coefficient) {
    unsigned int width = image.getWidth();
    unsigned int height = image.getHeight();
    float factor = (259.0f * (coefficient + 255.0f)) / (255.0f * (259.0f - coefficient));
    for (unsigned int y = 0; y < height; ++y) {
        for (unsigned int x = 0; x < width; ++x) {

            sf::Color pixel = image.getPixel(x, y);

            int r = static_cast<int>(factor * (static_cast<int>(pixel.r) - 128) + 128);
            int g = static_cast<int>(factor * (static_cast<int>(pixel.g) - 128) + 128);
            int b = static_cast<int>(factor * (static_cast<int>(pixel.b) - 128) + 128);

            // manual clamp (min/max)
            pixel.r = (r < 0 ? 0 : (r > 255 ? 255 : r));
            pixel.g = (g < 0 ? 0 : (g > 255 ? 255 : g));
            pixel.b = (b < 0 ? 0 : (b > 255 ? 255 : b));

            image.setPixel(x, y, pixel);
        }
    }

    image.updateTexture();
}
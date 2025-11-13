#include "Transform.h"
#include <iostream>
#include <algorithm>


#include "Transform.h"
#include <SFML/Graphics.hpp>

// fix this whomever was the person who was gonna take on the brightness function.
// this is broken af rn. i think you probably have to make sure that the rgb values stay in bounds.

void Transform::adjustBrightness(signed int coefficient) {
    unsigned int width = image.getWidth();
    unsigned int height = image.getHeight();

    for (unsigned int y = 0; y < height; ++y) {
        for (unsigned int x = 0; x < width; ++x) {
            sf::Color pixel = image.getPixel(x, y);

            // add brightness coefficient to each channel
            int r = static_cast<int>(pixel.r) + coefficient;
            int g = static_cast<int>(pixel.g) + coefficient;
            int b = static_cast<int>(pixel.b) + coefficient;

            // this part is definitely super super broken: fix
            pixel.r = r;
            pixel.g = g;
            pixel.b = b;

            image.setPixel(x, y, pixel);
        }
    }

    // texture that then gets rendered
    image.updateTexture();
}


// group members: all the transformation functions can go in here.



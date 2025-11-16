#include "ImageClass.hpp"
#include <iostream>

Image* loadimage(int argc, char* argv[]) {
    Image* img;
    if (argc > 1) {
        std::cout << "Loading image: " << argv[1] << std::endl;
        img = new Image(argv[1]);
    } else {
        std::cout << "No image provided. Creating blank canvas." << std::endl;
        img = new Image(800, 600, sf::Color::White);
    }
    return img;
}


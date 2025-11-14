#pragma once
#include "ImageClass.hpp"

class Transform {
public:
    Transform(Image& img) : image(img) {}

    void GrayScale();
    void Rotate(int rotation);
    void adjustBrightness(int coefficient);
    void adjustContrast(int coefficient);
	void Crop(int x, int y, int width, int height);

private:
    Image& image;
    void adjustPixelBrightness(int coefficient);
};

#pragma once
#include "ImageClass.hpp"
#include <memory>

class Transform {
public:
    Transform(Image& img) : image(img), originalImage(nullptr), grayScaleActive(false) {}

    void GrayScale(float amount);
    void Rotate(int rotation);
    void adjustBrightness(int coefficient);
    void adjustContrast(int coefficient);
	void Crop(int x, int y, int width, int height);
    void revertGrayScale();
    bool isGrayScaleActive() const { return grayScaleActive; }

private:
    Image& image;
    std::unique_ptr<Image> originalImage;
    bool grayScaleActive;
    void adjustPixelBrightness(int coefficient);
    void saveOriginalImage();
};

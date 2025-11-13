#include "ImageClass.hpp"
#pragma once

class Transform {
public:
// constructor
	Transform(Image& img) : image(img) {};
	//implement these in the transform.cpp file
	void GrayScale();
	void Rotate(int rotation);
	void adjustBrightness(signed int coefficient);
	void adjustContrast(signed int coefficient);
private:
	Image& image;
	void adjustPixelBrightness(signed int coeffient);
};
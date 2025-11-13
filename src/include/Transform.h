class Transform {
public:
	Transform(Image& img);
	void GrayScale();
	void Rotate(int rotation);
	void adjustBrightness(signed int coefficient);
	void adjustContrast(signed int coefficient);
private:
	void adjustPixelBrightness()
}
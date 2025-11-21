#include "ResourceManager.hpp"
#include "Transform.h"
struct FilterState{
    float* brightness;
    float* contrast;
    bool* greyScale;
    float* prev_brightness;
    float* prev_contrast;
    bool* showFilterMenu;
};

class Toolbar {
public:
    Toolbar(ResourceManager& rm, FilterState& st, Transform& tr, Image& img) 
        : resourceManager(rm), state(st), transform(tr), image(img) {}
    void Filter();
    void Draw();
    void Rotate();
    void buildToolbar();
private:
    ResourceManager& resourceManager;
    FilterState& state;
    Transform& transform;
    Image& image;
    bool grayScaleApplied = false;
};
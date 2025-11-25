#include "ResourceManager.hpp"
#include "Transform.h"
struct FilterState{
    float* brightness;
    float* contrast;
    bool* greyScale;
    float* prev_brightness;
    float* prev_contrast;
    bool* showFilterMenu;
    bool* drawingEnabled;
};

class Toolbar {
public:
    Toolbar(ResourceManager& rm, FilterState& st, Transform& tr, Image& img) 
        : resourceManager(rm), state(st), transform(tr), image(img) {}
    void Filter();
    void Draw();
    void Rotate();
    void Save();
    void buildToolbar();
private:
    ResourceManager& resourceManager;
    FilterState& state;
    Transform& transform;
    Image& image;
    bool grayScaleApplied = false;
    bool showSaveDialog = false;
    char saveFilename[256] = "output.png";
public:
    bool isDrawingEnabled() const { return *state.drawingEnabled; }
};
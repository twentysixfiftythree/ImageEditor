#include "ResourceManager.hpp"
#include "Transform.h"
struct FilterState{
    float* brightness;
    float* contrast;
    bool* greyScale;
    float* prev_brightness;
    bool* showFilterMenu;
};

class Toolbar {
public:
    Toolbar(ResourceManager* rm, FilterState* st, Transform* tr) 
        : resourceManager(rm), state(st), transform(tr) {}
    void Filter();
    void Draw();
    void buildToolbar();
private:
    ResourceManager* resourceManager;
    FilterState* state;
    Transform* transform;
};
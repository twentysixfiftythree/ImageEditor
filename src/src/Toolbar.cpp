#include "Toolbar.hpp"
#include <imgui-SFML.h>
#include <imgui.h>



void Toolbar::Filter() {
    // implementation for Filter toolbar
    ImGui::SetNextWindowPos(ImVec2(10, 10));
    ImGui::Begin("##Toolbar", nullptr,
        ImGuiWindowFlags_NoDecoration |
        ImGuiWindowFlags_NoBackground |
        ImGuiWindowFlags_AlwaysAutoResize |
        ImGuiWindowFlags_NoMove |
        ImGuiWindowFlags_NoSavedSettings);
        
    
    if (resourceManager.textureExists("FilterIcon")) {
        const sf::Vector2 FILTER_ICON_SIZE = {50.0f, 50.0f};
        if (ImGui::ImageButton("Filter Button", resourceManager.getTexture("FilterIcon"), {50.0f, 50.0f})) {
            *state.showFilterMenu = !*state.showFilterMenu;
        }
    }

    ImGui::End();
    
    if(*state.showFilterMenu){
            ImGui::SetNextWindowPos(ImVec2(410, 65.0f));
            ImGui::Begin("Filter settings", state.showFilterMenu, ImGuiWindowFlags_AlwaysAutoResize| ImGuiWindowFlags_NoMove);
            ImGui::Text("Filters");
            ImGui::Separator();

            //brightness
            ImGui::SetNextItemWidth(200.0f);
            if (ImGui::SliderFloat("Brightness", state.brightness, 0.0f, 1.0f)) {
                float delta = *state.brightness - *state.prev_brightness;
                int coeff = static_cast<int>(delta * 255.0f);
                if (coeff != 0) {
                    transform.adjustBrightness(coeff);
                }
                *state.prev_brightness = *state.brightness;
            };

            //contrast -- team!! implement!!!
            ImGui::SetNextItemWidth(200.0f);
            ImGui::SliderFloat("Contrast", state.contrast, 0.0f, 1.0f);
            // implement slider here.
            ImGui::Separator();
            ImGui::Checkbox("Greyscale", state.greyScale);
            if (*state.greyScale) {
                // whoever is implementing grayscale functionality, uncomment below once done.
                // transform->GrayScale();
            }

            ImGui::End();
        }
}


void Toolbar::buildToolbar() {
    // implementation for building the toolbar
    // as we add more tools, we will expand this function
    Filter();
    // Draw()
};
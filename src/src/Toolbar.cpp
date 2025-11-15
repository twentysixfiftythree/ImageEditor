#include "Toolbar.hpp"
#include <imgui-SFML.h>
#include <imgui.h>


void Toolbar::Filter() {
    // Implementation for Filter toolbar
    if (ImGui::ImageButton("Filter Button", resourceManager->getTexture("FilterIcon"), {50.0f, 50.0f}))
        {
            *(state->showFilterMenu) = !(*(state->showFilterMenu));
        };
        if(*(state->showFilterMenu)){
            ImGui::SetNextWindowPos(ImVec2(410, 65.0f));
            ImGui::Begin("Filter settings", state->showFilterMenu, ImGuiWindowFlags_AlwaysAutoResize| ImGuiWindowFlags_NoMove);
            ImGui::Text("Filters");
            ImGui::Separator();

            //Brightness
            ImGui::SetNextItemWidth(200.0f);
            if (ImGui::SliderFloat("Brightness", state->brightness, 0.0f, 1.0f)) {
                float delta = *(state->brightness) - *(state->prev_brightness);
                int coeff = static_cast<int>(delta * 255.0f);
                if (coeff != 0) {
                    transform->adjustBrightness(coeff);
                }
                state->prev_brightness = state->brightness;
            };

            //Contrast
            ImGui::SetNextItemWidth(200.0f);
            ImGui::SliderFloat("Contrast", state->contrast, 0.0f, 1.0f);

            ImGui::Separator();
            ImGui::Checkbox("Greyscale", state->greyScale);

            ImGui::End();
        }
}
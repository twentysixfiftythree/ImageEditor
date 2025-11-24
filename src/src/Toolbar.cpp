#include "Toolbar.hpp"
#include <imgui-SFML.h>
#include <imgui.h>
#include <iostream>

void Toolbar::Filter()
{
    // implementation for Filter toolbar
    ImGui::SetNextWindowPos(ImVec2(10, 100));
    ImGui::Begin("##Toolbar", nullptr,
                 ImGuiWindowFlags_NoDecoration |
                     ImGuiWindowFlags_NoBackground |
                     ImGuiWindowFlags_AlwaysAutoResize |
                     ImGuiWindowFlags_NoMove |
                     ImGuiWindowFlags_NoSavedSettings);

    if (resourceManager.textureExists("FilterIcon"))
    {
        const sf::Vector2 FILTER_ICON_SIZE = {50.0f, 50.0f};
        if (ImGui::ImageButton("Filter Button", resourceManager.getTexture("FilterIcon"), {50.0f, 50.0f}))
        {
            *state.showFilterMenu = !*state.showFilterMenu;
        }
    }

    if (*state.showFilterMenu)
    {
        ImGui::SetNextWindowPos(ImVec2(410, 65.0f));
        ImGui::Begin("Filter settings", state.showFilterMenu, ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoMove);
        ImGui::Text("Filters");
        ImGui::Separator();

        // brightness
        ImGui::SetNextItemWidth(200.0f);
        if (ImGui::SliderFloat("Brightness", state.brightness, 0.0f, 1.0f))
        {
            float delta = *state.brightness - *state.prev_brightness;
            int coeff = static_cast<int>(delta * 255.0f);
            if (coeff != 0)
            {
                transform.adjustBrightness(coeff);
            }
            *state.prev_brightness = *state.brightness;
        };

        // contrast -- team!! implement!!!
        ImGui::SetNextItemWidth(200.0f);
        if (ImGui::SliderFloat("Contrast", state.contrast, 0.0f, 1.0f))
        {

            float delta = *state.contrast - *state.prev_contrast;
            int coeff = static_cast<int>(delta * 255.0f);

            if (coeff != 0)
            {
                transform.adjustContrast(coeff);
            }

            *state.prev_contrast = *state.contrast;
        }

        // implement slider here.

        ImGui::Separator();
        ImGui::Checkbox("Greyscale", state.greyScale);
        if (*state.greyScale)
        {
            if (!transform.isGrayScaleActive())
            {
                transform.GrayScale(1.0f); // full grayscale
            }
        }
        else
        {
            if (transform.isGrayScaleActive())
            {
                transform.revertGrayScale();
            }
        }

        ImGui::End();
    }
}

void Toolbar::Draw()
{
    ImGui::SameLine();

    if (resourceManager.textureExists("DrawActiveIcon"))
    {
        const sf::Vector2 DRAW_ICON_SIZE = {50.0f, 50.0f};
        if (ImGui::ImageButton("Draw Button", resourceManager.getTexture("DrawActiveIcon"), {50.0f, 50.0f}))
        {
            // implement drawing. do not put all the drawing logic in here though.
            std::cout << "draw button pressed" << std::endl;
        }
    }
}

void Toolbar::Rotate()
{
    ImGui::SameLine();

    if (resourceManager.textureExists("RotateIcon"))
    {
        const sf::Vector2 DRAW_ICON_SIZE = {50.0f, 50.0f};
        if (ImGui::ImageButton("Rotate Button", resourceManager.getTexture("RotateIcon"), {50.0f, 50.0f}))
        {
            // implement drawing. do not put all the drawing logic in here though.
            std::cout << "Rotate button pressed" << std::endl;
            transform.Rotate(90); // rotate 90 degrees clockwise on each press
        }
    }
}

void Toolbar::buildToolbar()
{
    // implementation for building the toolbar
    // as we add more tools, we will expand this function
    // do not change order!
    Filter();
    Draw();
    Rotate();
    ImGui::End();
};
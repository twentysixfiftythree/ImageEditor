#include <SFML/Graphics.hpp>
#include <imgui-SFML.h>
#include <imgui.h>
#include <memory>
#include "Transform.h"
#include "ImageClass.hpp"
#include <iostream>
#include "ResourceManager.hpp"
#include "Toolbar.hpp"
#include "Scripts.hpp"


void setBackground(sf::RenderWindow& window) {
    // keep texture and sprite alive across frames using heap objects
    static std::unique_ptr<sf::Texture> backgroundTexture;
    static std::unique_ptr<sf::Sprite> backgroundSprite;

    if (!backgroundTexture) {
        backgroundTexture = std::make_unique<sf::Texture>();
        if (!backgroundTexture->loadFromFile("assets/background.png")) {
            std::cerr << "Error loading background.png" << std::endl;
            backgroundTexture.reset();
            backgroundSprite.reset();
            return;
        }

        sf::Vector2u backgroundTextureSize = backgroundTexture->getSize();


        const float MAX_WIDTH = 2.7f * 1280.0f;
        const float MAX_HEIGHT = 2.7f * 720.0f;

        // base scale factor
        float scale = 1.0f;

        // adjust scale if the image exceeds maximum dimensions
        if (static_cast<float>(backgroundTextureSize.x) > MAX_WIDTH) {
            scale = MAX_WIDTH / static_cast<float>(backgroundTextureSize.x);
        }
        if (static_cast<float>(backgroundTextureSize.y) * scale > MAX_HEIGHT) {
            scale = MAX_HEIGHT / static_cast<float>(backgroundTextureSize.y);
        }

        backgroundSprite = std::make_unique<sf::Sprite>(*backgroundTexture);
        backgroundSprite->setScale(sf::Vector2f(scale, scale));
    }

    if (backgroundSprite) {
        window.draw(*backgroundSprite);
    }
}


int main(int argc, char* argv[])
{
    auto window = sf::RenderWindow(sf::VideoMode({1920u, 1080u}), "CMake SFML Project");
    window.setFramerateLimit(60);
    if (!ImGui::SFML::Init(window))
        return -1;
        
    Image* img = loadimage(argc, argv);

   // managers and state
    bool showFilterMenu = false;
    float brightness = 0.5f;
    float contrast = 0.5f;
    bool greyScale = false;

 
    ResourceManager resourceManager;
    Transform transform(*img);
    float prev_brightness = brightness;
    float prev_contrast = contrast;


    sf::Clock clock;
    while (window.isOpen())
    {
        while (const std::optional event = window.pollEvent())
        {
            ImGui::SFML::ProcessEvent(window, *event);
            
            if (event->is<sf::Event::Closed>())
            {
                window.close();
            }
        }

        ImGui::SFML::Update(window, clock.restart());
        
        
        FilterState filterState{
            &brightness,
            &contrast,
            &greyScale,
            &prev_brightness,
            &prev_contrast,
            &showFilterMenu
        };
        Toolbar toolbar(resourceManager, filterState, transform, *img);
        toolbar.buildToolbar();


        // Rendering
        window.clear();
        // Draw background (if loaded) each frame
        setBackground(window);
        // draw image in the middle of screen

        img->draw(window);

        ImGui::SFML::Render(window);
        window.display();
    }
    
    ImGui::SFML::Shutdown();
    delete img;
    return 0;
}
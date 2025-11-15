#include <SFML/Graphics.hpp>
#include <imgui-SFML.h>
#include <imgui.h>
#include "Transform.h"
#include "ImageClass.hpp"
#include <iostream>
#include "ResourceManager.hpp"
#include "Toolbar.hpp"

int main(int argc, char* argv[])
{
    auto window = sf::RenderWindow(sf::VideoMode({1920u, 1080u}), "CMake SFML Project");
    window.setFramerateLimit(60);
    if (!ImGui::SFML::Init(window))
        return -1;

    Image* img;
    if (argc > 1) {
        std::cout << "Loading image: " << argv[1] << std::endl;
        img = new Image(argv[1]);
    } else {
        std::cout << "No image provided. Creating blank canvas." << std::endl;
        img = new Image(800, 600, sf::Color::White);
    }


    bool showFilterMenu = false;
    float brightness = 0.5f;
    float contrast = 0.5f;
    bool greyScale = false;

    // Managers and state
    ResourceManager resourceManager;
    Transform transform(*img);
    float prev_brightness = brightness;


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
            &showFilterMenu
        };
        Toolbar toolbar(&resourceManager, &filterState, &transform);
        toolbar.buildToolbar();


        // Rendering
        window.clear();
        ImGui::SFML::Render(window);
        img->draw(window);
        window.display();
    }
    
    ImGui::SFML::Shutdown();
    delete img;
    return 0;
}
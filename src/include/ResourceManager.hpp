#include <iostream>
#include <unordered_map>
#include <string>
#include <SFML/Graphics.hpp>
#pragma once

class ResourceManager{
public:
    ResourceManager();
    ~ResourceManager();
    
    // Texture management
    void addTexture(const std::string& name, const std::string& filePath);
    sf::Texture& getTexture(const std::string& name);
    bool textureExists(const std::string& name) const;
    void loadDefaultResources();

private:
    std::unordered_map<std::string, sf::Texture> textures;
};
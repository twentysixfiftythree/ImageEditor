#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Texture.hpp>
#include "ResourceManager.hpp"
ResourceManager::ResourceManager() {
    loadDefaultResources();
}

ResourceManager::~ResourceManager() {
    // Destructor
}

void ResourceManager::addTexture(const std::string& name, const std::string& filepath){
    sf::Texture texture;
    texture.loadFromFile(filepath);
    textures[name] = texture;
}

sf::Texture& ResourceManager::getTexture(const std::string& name) {
    return textures.at(name);
}

bool ResourceManager::textureExists(const std::string& name) const {
    return textures.find(name) != textures.end();
}
void ResourceManager::loadDefaultResources() {
    // Load default textures
    addTexture("DrawActiveIcon", "assets/DrawActiveIcon.png");
    addTexture("FilterIcon", "assets/FilterIcon.png");
    addTexture("RotateIcon", "assets/RotateIcon.png");
}
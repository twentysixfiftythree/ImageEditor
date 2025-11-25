#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Texture.hpp>
#include "ResourceManager.hpp"
ResourceManager::ResourceManager() {
    loadDefaultResources();
}

ResourceManager::~ResourceManager() {
    // destructor
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
    addTexture("DrawActiveIcon", "assets/DrawActiveIcon.jpg");
    addTexture("FilterIcon", "assets/FilterIcon.jpg");
    addTexture("RotateIcon", "assets/RotateIcon.jpg");
    addTexture("SaveExportIcon", "assets/SaveExportIcon.jpg");
}
//
//  UserInterface.hpp
//  WorldBuilder
//
//  Created by Bartosz Osowski on 18/09/2018.
//  Copyright © 2018 Bartosz Osowski. All rights reserved.
//

#ifndef UserInterface_hpp
#define UserInterface_hpp

#include <stdio.h>
#include "AssetManager.hpp"
#include <map>
#include <math.h>
#include "TextureContainer.hpp"
#include "DataManager.hpp"

class UserInterface{
public:
    static UserInterface& instance();
    RenderWindow mainWindow{VideoMode(1600, 1200), "Asset Manager"};
    map<sfg::Button*, sf::Texture*> buttonMap;
    const sf::Texture* currentlyPickedImage = nullptr;
    void displayAvailableSprites(vector<Sprite*> sprites);
    void render();
    static void adjustSprite(sf::Sprite *sprite, sf::Texture& texture, Vector2f position);
private:
    AssetManager assetManager{};
    UserInterface();
    void createRotateButtons(std::shared_ptr<sfg::Box> box);
    const float padding = 20;
    vector<sf::Sprite*> world;
    static sf::Vector2f* roundTo(const sf::Vector2i& position, const sf::Vector2<int>& roundTo);
};
#endif /* UserInterface_hpp */

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

class UserInterface{
public:
    static UserInterface& instance();
    RenderWindow mainWindow{VideoMode(1600, 1200), "Asset Manager"};
    map<sfg::Button*, sf::Texture> buttonMap;
    const sf::Texture* currentlyPickedImage = nullptr;
    void displayAvailableSprites(vector<Sprite*> sprites);
    void render();
private:
    AssetManager assetManager{};
    UserInterface();
    const float padding = 20;
    vector<sf::Sprite*> world;
    sf::Vector2f* roundTo(const sf::Vector2i& position, const sf::Vector2<unsigned int>& roundTo);
};
#endif /* UserInterface_hpp */

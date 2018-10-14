//
//  DataManager.hpp
//  WorldBuilder
//
//  Created by Bartosz Osowski on 21/09/2018.
//  Copyright © 2018 Bartosz Osowski. All rights reserved.
//

#ifndef DataManager_hpp
#define DataManager_hpp

#include <stdio.h>
#include <vector>
#include <SFML/Graphics.hpp>
#include "TextureContainer.hpp"
#include "AssetManager.hpp"
#include "UserInterface.hpp"
#include "rapidxml.hpp"
#include "rapidxml_print.hpp"
#include <sstream>
#include <fstream>
#include <iostream>
#include <string>

using namespace std;

class DataManager{
public:
    static bool exportWorld(const vector<sf::Sprite*>& worldData, const vector<TextureContainer*>& textureContainers);
    static bool importWorld(vector<sf::Sprite*>& worldData, vector<TextureContainer*>& textureContainers);
private:
    static int* getSpriteIndex(const vector<TextureContainer*>& textureContainers, sf::Sprite& sprite);
};
#endif /* DataManager_hpp */

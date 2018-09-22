//
//  WorldExporter.hpp
//  WorldBuilder
//
//  Created by Bartosz Osowski on 21/09/2018.
//  Copyright © 2018 Bartosz Osowski. All rights reserved.
//

#ifndef WorldExporter_hpp
#define WorldExporter_hpp

#include <stdio.h>
#include <vector>
#include <SFML/Graphics.hpp>
#include <TextureContainer.hpp>
#include <AssetManager.hpp>
#include <rapidxml.hpp>
#include "rapidxml_print.hpp"
#include <sstream>
#include <fstream>

using namespace std;

#endif /* WorldExporter_hpp */
class WorldExporter{
public:
    static bool exportWorld(const vector<sf::Sprite*>& worldData, const vector<TextureContainer*>& textureContainers);
private:
    static int* getSpriteIndex(const vector<TextureContainer*>& textureContainers, sf::Sprite& sprite);
};

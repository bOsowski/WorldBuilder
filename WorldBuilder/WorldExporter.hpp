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
#include <rapidxml.hpp>
#include <TextureContainer.hpp>

using namespace std;

#endif /* WorldExporter_hpp */
class WorldExporter{
public:
    static bool exportWorld(const vector<sf::Sprite*> world, const vector<TextureContainer*> textureContainer);
private:
};

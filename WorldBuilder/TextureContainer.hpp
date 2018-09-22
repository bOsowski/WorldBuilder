//
//  Texture.hpp
//  WorldBuilder
//
//  Created by Bartosz Osowski on 21/09/2018.
//  Copyright © 2018 Bartosz Osowski. All rights reserved.
//

#ifndef TextureContainer_hpp
#define TextureContainer_hpp

#include <stdio.h>
#include <iostream>
#include <SFML/Graphics.hpp>

class TextureContainer{
public:
    sf::Texture texture;
    sf::Image image;
    std::string imageLocation;
};

#endif /* TextureContainer_hpp */

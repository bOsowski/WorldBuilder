//
//  Tile.hpp
//  WorldBuilder
//
//  Created by Bartosz Osowski on 21/09/2018.
//  Copyright © 2018 Bartosz Osowski. All rights reserved.
//

#ifndef Tile_hpp
#define Tile_hpp

#include <stdio.h>
#include <SFML/Graphics.hpp>



class Tile{
public:
    Tile(sf::Sprite _sprite, std::string _imageLocation);
    sf::Sprite& getSprite();
    std::string& getImageLocation();
    
private:
    sf::Sprite sprite;
    std::string imageLocation;
};


#endif /* Tile_hpp */

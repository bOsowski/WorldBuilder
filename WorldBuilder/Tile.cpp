//
//  Tile.cpp
//  WorldBuilder
//
//  Created by Bartosz Osowski on 21/09/2018.
//  Copyright © 2018 Bartosz Osowski. All rights reserved.
//

#include "Tile.hpp"

Tile::Tile(sf::Sprite _sprite, std::string _imageLocation){
    sprite = _sprite;
    imageLocation = _imageLocation;
}

sf::Sprite& Tile::getSprite(){
    return sprite;
}

std::string& Tile::getImageLocation(){
    return imageLocation;
}

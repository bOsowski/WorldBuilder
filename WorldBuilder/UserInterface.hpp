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

#endif /* UserInterface_hpp */

class UserInterface{
public:
    static UserInterface& instance();
    RenderWindow mainWindow{VideoMode(800, 600), "Asset Manager"};
    void displayAvailableSprites(vector<Sprite*> sprites);
    void render();
private:
    AssetManager assetManager{};
    UserInterface();
    const float padding = 20;
};

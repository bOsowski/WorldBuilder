//
//  AssetManager.hpp
//  AssetManager
//
//  Created by Bartosz Osowski on 17/09/2018.
//  Copyright © 2018 Bartosz Osowski. All rights reserved.
//

#ifndef AssetManager_hpp
#define AssetManager_hpp

#include <stdio.h>
#include <vector>
#include <SFML/Graphics.hpp>
#include "ResourcePath.hpp"
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <sstream>
#include <dirent.h>

using namespace std;
using namespace sf;

class AssetManager{
public:
    static AssetManager& instance();
    vector<Texture*> textures;
    
private:
    AssetManager();
    void loadTextures();
};

#endif /* AssetManager_hpp */



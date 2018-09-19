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
#include <SFGUI/SFGUI.hpp>
#include <SFGUI/Widgets.hpp>

using namespace std;
using namespace sf;

class AssetManager{
public:
    AssetManager();
    vector<string*> imageAbsolutePaths;
    
private:
    void loadTextures();
    static const char* RESOURCE_FOLDER_PATH;
};

#endif /* AssetManager_hpp */



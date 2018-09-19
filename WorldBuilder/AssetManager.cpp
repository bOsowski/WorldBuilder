//
//  AssetManager.cpp
//  AssetManager
//
//  Created by Bartosz Osowski on 17/09/2018.
//  Copyright © 2018 Bartosz Osowski. All rights reserved.
//

#include "AssetManager.hpp"

const char* AssetManager::RESOURCE_FOLDER_PATH = "/Users/bOsowski/Documents/XCode/WorldBuilder/WorldBuilder/Resources";

AssetManager::AssetManager(){
    DIR *dir;
    struct dirent *ent;
    if ((dir = opendir (RESOURCE_FOLDER_PATH)) != NULL) {
        while ((ent = readdir (dir)) != NULL) {
            if(string(ent->d_name) == "." || string(ent->d_name) == "..")continue;
            
            string full_path = string(RESOURCE_FOLDER_PATH)+ "/" + string(ent->d_name);
            cout << "Trying to load from " + full_path << endl;
            sf::Texture* texture = new Texture();
            if (texture->loadFromFile(full_path)) {
                Sprite* sprite = new Sprite(*texture, *new IntRect(*new Vector2i(10,10), *new Vector2i(100,100)));
                sprites.push_back(sprite);
                cout << "Loaded " + full_path << endl;
            }
        }
        closedir (dir);
    } else {
        /* could not open directory */
        perror ("");
        return EXIT_FAILURE;
    }
}



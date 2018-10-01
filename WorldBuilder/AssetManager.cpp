//
//  AssetManager.cpp
//  AssetManager
//
//  Created by Bartosz Osowski on 17/09/2018.
//  Copyright © 2018 Bartosz Osowski. All rights reserved.
//

#include "AssetManager.hpp"

const char* AssetManager::RESOURCE_FOLDER_PATH = "/Users/bOsowski/Documents/XCode/WorldBuilder/WorldBuilder/Resources/Textures";

AssetManager::AssetManager(){
    DIR *dir;
    struct dirent *ent;
    if ((dir = opendir (RESOURCE_FOLDER_PATH)) != NULL) {
        while ((ent = readdir (dir)) != NULL) {
            if(string(ent->d_name) == "." || string(ent->d_name) == "..")continue;
            
            string *full_path = new string();
            *full_path = string(RESOURCE_FOLDER_PATH)+ "/" + string(ent->d_name);
            cout << "Trying to load from " + *full_path << endl;
            TextureContainer* textureContainer = new TextureContainer();
            if ( textureContainer->image.loadFromFile(*full_path)) {
                textureContainer->texture.loadFromImage(textureContainer->image);
                textureContainer->imageLocation = *full_path;
                textureContainers.push_back(textureContainer);
                cout << "Loaded " + *full_path << endl;
            }
        }
        sort(textureContainers.begin(),textureContainers.end(),[](TextureContainer* a, TextureContainer* b){
            return a->imageLocation.compare(b->imageLocation);
        });
        refreshIndexOfTextureContainers();

        closedir (dir);
    } else {
        /* could not open directory */
        perror ("");
    }
}

void AssetManager::refreshIndexOfTextureContainers(){
    int counter = 0;
    for(TextureContainer* container: textureContainers){
        container->index = counter++;
    }
}

const vector<TextureContainer*>& AssetManager::getTextureContainers(){
    return textureContainers;
}





//
//  AssetManager.cpp
//  AssetManager
//
//  Created by Bartosz Osowski on 17/09/2018.
//  Copyright © 2018 Bartosz Osowski. All rights reserved.
//

#include "AssetManager.hpp"

AssetManager::AssetManager(){
    DIR *dir;
    struct dirent *ent;
    if ((dir = opendir ("")) != NULL) {
        /* print all the files and directories within directory */
        while ((ent = readdir (dir)) != NULL) {
            printf ("%s\n", ent->d_name);
        }
        closedir (dir);
    } else {
        /* could not open directory */
        perror ("");
        return EXIT_FAILURE;
    }
}

AssetManager& AssetManager::instance(){
    static AssetManager* instance = new AssetManager();
    return *instance;
}

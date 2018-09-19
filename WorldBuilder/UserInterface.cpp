//
//  UserInterface.cpp
//  WorldBuilder
//
//  Created by Bartosz Osowski on 18/09/2018.
//  Copyright © 2018 Bartosz Osowski. All rights reserved.
//

#include "UserInterface.hpp"

UserInterface::UserInterface(){
    render();
}

void UserInterface::displayAvailableSprites(vector<sf::Sprite*> sprites){

}

UserInterface& UserInterface::instance(){
    static UserInterface* instance = new UserInterface();
    return *instance;
}


void UserInterface::render(){
    // Set the Icon
    sf::Image icon;
    if (!icon.loadFromFile(resourcePath() + "icon.png")) {return EXIT_FAILURE;}
    mainWindow.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());
    
    while (mainWindow.isOpen())
    {
        // Process events
        sf::Event event;
        while (mainWindow.pollEvent(event))
        {
            if (event.type == sf::Event::Closed) {
                mainWindow.close();
            }
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) {
                mainWindow.close();
            }
        }
        mainWindow.clear();
        //draw here.
        mainWindow.display();
    }
}

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
    SFGUI sfgui;
    mainWindow.resetGLStates();
    auto window = sfg::Window::Create();
    window->SetTitle( "World Builder");
    window->SetRequisition(Vector2f(mainWindow.getSize().x,mainWindow.getSize().y));
    sf::View view( sf::Vector2f( 100.f, 100.f ), sf::Vector2f( mainWindow.getSize().x, mainWindow.getSize().y ) );
    
    
    // Create a box with 20 pixels spacing.
    auto box = sfg::Box::Create( sfg::Box::Orientation::HORIZONTAL, 5.f );
    auto frame = sfg::Frame::Create( "Available Tiles" );
    //auto separator = sfg::Separator::Create( sfg::Separator::Orientation::HORIZONTAL );
    auto alignment = sfg::Alignment::Create();
    auto alignment_box = sfg::Box::Create( sfg::Box::Orientation::VERTICAL );
    auto canvas = sfg::Canvas::Create();
    auto table = sfg::Table::Create();
    
    // Set scaling parameters.
    // Scaling sets how much of the total space in the alignment
    // the child gets to fill up. 1.0f for x and y would mean the
    // child gets to use the whole space. Setting it to 0.0f for
    // x and y makes the child get as little space as possible.
    alignment->SetScale( sf::Vector2f( .0f, .0f ) );
    
    alignment_box->Pack( alignment, false, false );
    box->Pack( frame, false, false );
    //box->Pack( separator, false, false );
    
    for(string* path: assetManager.imageAbsolutePaths){
        cout << "path = " + *path << endl;
        sf::Image imageSource;
        auto image = sfg::Image::Create();
        if( imageSource.loadFromFile( *path ) ) {
            image->SetImage( imageSource );
        }
        alignment_box->Pack( image);
    }

    
    alignment->SetAlignment( sf::Vector2f( .8f, .8f ) );
    frame->SetAlignment( sf::Vector2f( .8f, .5f ) );
    
    frame->Add( alignment_box );
    window->Add( box );
    
    
    
    
    

    //table->Attach(canvas, sf::Rect<sf::Uint32>( 0, 0, 1, 1 ));
    //window->Add(canvas);
    while (mainWindow.isOpen())
    {
        // Process events
        sf::Event event;
        while (mainWindow.pollEvent(event))
        {
            window->HandleEvent( event );
            if (event.type == sf::Event::Closed) {
                mainWindow.close();
            }
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) {
                mainWindow.close();
            }
        }
        // Update the GUI, note that you shouldn't normally
        // pass 0 seconds to the update method.
        window->Update( 0.f );
        mainWindow.clear();
        // After drawing the rest of your game, you have to let the GUI
        // render itself. If you don't do this you will never be able
        // to see it ;)
        sfgui.Display( mainWindow );
        // Then the scrollable Canvas for SFML rendering.
        
//        canvas->Bind();
//        canvas->Clear( sf::Color( 0, 0, 0, 0 ) );
//        canvas->SetView(view);
//        for(int i = 0; i<assetManager.sprites.size(); i++){
//            canvas->Draw(*assetManager.sprites[i]);
//        }
//        canvas->Display();
//        canvas->Unbind();
//
        //displayAvailableSprites(assetManager.sprites);
        mainWindow.display();
    }
}

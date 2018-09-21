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

sf::Vector2f* UserInterface::roundTo(const sf::Vector2i& position, const sf::Vector2<unsigned int>& roundTo){
    cout << "(" << position.x << ", " << position.y << ")" << endl;
    sf::Vector2f* rounded = new Vector2f();
    rounded->x = roundTo.x * (int)round(position.x / roundTo.x);
    rounded->y = roundTo.y * (int)round(position.y / roundTo.y);
    cout << "(" << rounded->x << ", " << rounded->y << ")" << endl;
    return rounded;
}


void UserInterface::displayAvailableSprites(vector<sf::Sprite*> sprites){
    
}

UserInterface& UserInterface::instance(){
    static UserInterface* instance = new UserInterface();
    return *instance;
}


void UserInterface::render(){
    
    mainWindow.resetGLStates();
    sfg::SFGUI sfgui;
    
    auto window = sfg::Window::Create();
    window->SetRequisition(Vector2f(mainWindow.getSize().x, mainWindow.getSize().y));
    
    auto box = sfg::Box::Create( sfg::Box::Orientation::HORIZONTAL, 5.f );
    auto scrolled_window_box = sfg::Box::Create( sfg::Box::Orientation::VERTICAL);
    
    
    auto scrolledWindow = sfg::ScrolledWindow::Create();
    scrolledWindow->SetScrollbarPolicy( sfg::ScrolledWindow::VERTICAL_AUTOMATIC | sfg::ScrolledWindow::HORIZONTAL_NEVER );
    scrolledWindow->AddWithViewport(scrolled_window_box);
    
    auto canvasWindow = sfg::Window::Create(sfg::Window::Style::BACKGROUND);
    //canvasWindow->SetParent(box);
    auto canvas = sfg::Canvas::Create(true);
    canvasWindow->Add( canvas );
    box->Pack(canvasWindow);
    auto table = sfg::Table::Create();
    
    for(string* path: assetManager.imageAbsolutePaths){
        cout << "path = " + *path << endl;
        sf::Image imageSource;
        auto image = sfg::Image::Create();
        if( imageSource.loadFromFile( *path ) ) {
            image->SetImage( imageSource );
            auto button = sfg::Button::Create();
            //currentlyPickedImage = (const sf::Image*)button->GetImage().get();
            button->SetImage(image);
            button->GetSignal( sfg::Widget::OnLeftClick ).Connect( [button, this] {
                std::map<sfg::Button*, sf::Texture>::iterator it = buttonMap.find(button.get());
                currentlyPickedImage = &it->second;
            });
            sf::Texture texture;
            texture.loadFromImage(imageSource);
            buttonMap.emplace(button.get(), texture);
            scrolled_window_box->Pack(button);
        }
    }
    

    scrolledWindow->SetRequisition(Vector2f(64, mainWindow.getSize().y/2));
    box->Pack(scrolledWindow, false, false);
    
    
    window->Add( box );
    cout<<"Window size = ("<<mainWindow.getSize().x << ", " << mainWindow.getSize().y << ")\n";

    Vector2i* originalMousePosition = nullptr;
    
    
    Vector2i* originalWorldPosition = new Vector2i(canvas->GetAbsolutePosition());
    while (mainWindow.isOpen())
    {
        // Process events
        sf::Event event;
        while (mainWindow.pollEvent(event))
        {
            window->HandleEvent( event );
           // cout << "Pressing key" << event.key.code<<endl;

            if (event.type == sf::Event::Closed) {
                mainWindow.close();
            }
            if(event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape){
                for(Sprite* sprite: world){
                    sprite->setPosition(*roundTo(*originalWorldPosition + (Vector2i)sprite->getPosition(), currentlyPickedImage->getSize()));
                    canvas->Draw(*sprite);
                }
            }
            if(event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Space){
                originalMousePosition = new Vector2i(sf::Mouse::getPosition(mainWindow));
            }
            else if(event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::Space){
                for(Sprite* sprite: world){
                    sprite->setPosition(*roundTo((sf::Mouse::getPosition(mainWindow) - *originalMousePosition) + (Vector2i)sprite->getPosition(), currentlyPickedImage->getSize()));
                    canvas->Draw(*sprite);
                }
            }
            else if(sf::Mouse::isButtonPressed(sf::Mouse::Left) && currentlyPickedImage != nullptr){
                sf::Sprite* sprite = new Sprite();
                sprite->setTexture(*currentlyPickedImage);
                sprite->setOrigin(sprite->getTexture()->getSize().x-7, sprite->getTexture()->getSize().y+18.5f);
                sprite->setPosition(*roundTo(sf::Mouse::getPosition(mainWindow), currentlyPickedImage->getSize()));
                world.push_back(sprite);
            }
        }
        
        window->Update( 0.f );
        mainWindow.clear();
        
        canvas->Bind();
        canvas->Clear( sf::Color( 0, 0, 0, 0 ), true );
        
        for(Sprite* sprite: world){
            canvas->Draw(*sprite);
        }
        
        canvas->Display();
        canvas->Unbind();
        sfgui.Display( mainWindow );
        mainWindow.display();
    }
}


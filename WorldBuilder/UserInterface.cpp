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

sf::Vector2f* UserInterface::roundTo(const sf::Vector2i& position, const sf::Vector2<int>& roundTo){
    sf::Vector2f* rounded = new Vector2f();
    rounded->x = roundTo.x * (int)round(position.x / roundTo.x);
    rounded->y = roundTo.y * (int)round(position.y / roundTo.y);
    //return rounded;
    sf::Vector2f* original = new Vector2f(position);
    return rounded;
}

UserInterface& UserInterface::instance(){
    static UserInterface* instance = new UserInterface();
    return *instance;
}

void UserInterface::createRotateButtons(std::shared_ptr<sfg::Box> box){
    //top: flip horizontal to the right
    //right: rotate to clockwise
    //bottom: flip vertical top to bottom
    //left: rotate counterclockwise
    
    auto horizontalGridTop = sfg::Box::Create();
    auto horizontalGridMiddle = sfg::Box::Create();
    auto horizontalGridBottom = sfg::Box::Create();
    
    box->Pack(horizontalGridTop);
    box->Pack(horizontalGridMiddle);
    box->Pack(horizontalGridBottom);

    auto buttonTopLeft = sfg::Button::Create();
    auto buttonTop = sfg::Button::Create();
    auto buttonTopRight = sfg::Button::Create();
    
    auto buttonRight = sfg::Button::Create();
    auto buttonLeft = sfg::Button::Create();
    auto buttonCenterCenter = sfg::Button::Create();
    
    auto buttonBottomLeft = sfg::Button::Create();
    auto buttonBottom = sfg::Button::Create();
    auto buttonBottomRight = sfg::Button::Create();
    
    buttonTop->SetLabel("Button Top");
    buttonRight->SetLabel("Button Right");
    buttonBottom->SetLabel("Button Bottom");
    buttonLeft->SetLabel("Button Left");
    
    
    horizontalGridTop->Pack(buttonTopLeft);
    horizontalGridTop->Pack(buttonTop);
    horizontalGridTop->Pack(buttonTopRight);
    
    horizontalGridMiddle->Pack(buttonLeft);
    horizontalGridMiddle->Pack(buttonCenterCenter);
    horizontalGridMiddle->Pack(buttonRight);
    
    horizontalGridBottom->Pack(buttonBottomLeft);
    horizontalGridBottom->Pack(buttonBottom);
    horizontalGridBottom->Pack(buttonBottomRight);
}


void UserInterface::render(){
    
    mainWindow.resetGLStates();
    sfg::SFGUI sfgui;
    
    auto window = sfg::Window::Create();
    window->SetRequisition(Vector2f(mainWindow.getSize().x, mainWindow.getSize().y));
    
    auto box = sfg::Box::Create( sfg::Box::Orientation::HORIZONTAL, 5.f );
    auto scrolled_window_box = sfg::Box::Create( sfg::Box::Orientation::VERTICAL);
    
    createRotateButtons(scrolled_window_box);
    auto scrolledWindow = sfg::ScrolledWindow::Create();
    scrolledWindow->SetScrollbarPolicy( sfg::ScrolledWindow::VERTICAL_AUTOMATIC | sfg::ScrolledWindow::HORIZONTAL_AUTOMATIC );
    scrolledWindow->AddWithViewport(scrolled_window_box);
    
    auto canvasWindow = sfg::Window::Create(sfg::Window::Style::BACKGROUND);
    //canvasWindow->SetParent(box);
    auto canvas = sfg::Canvas::Create(true);
    canvasWindow->Add( canvas );
    box->Pack(canvasWindow);
    auto table = sfg::Table::Create();
    
    auto loose_sprite_window_box_internal = sfg::Box::Create( sfg::Box::Orientation::HORIZONTAL);
    
    auto looseSpriteWindowInternal = sfg::ScrolledWindow::Create();
    looseSpriteWindowInternal->SetScrollbarPolicy( sfg::ScrolledWindow::VERTICAL_NEVER | sfg::ScrolledWindow::HORIZONTAL_NEVER );
    looseSpriteWindowInternal->AddWithViewport(loose_sprite_window_box_internal);
    int counter = 0;
    for(TextureContainer* container : assetManager.getTextureContainers()){
        auto button = sfg::Button::Create();
        auto image = sfg::Image::Create();
        image->SetImage(container->image);
        button->SetImage(image);
        button->GetSignal( sfg::Widget::OnLeftClick ).Connect( [button, this] {
            std::map<sfg::Button*, sf::Texture*>::iterator it = buttonMap.find(button.get());
            currentlyPickedImage = it->second;
        });
        
        buttonMap.emplace(button.get(), &container->texture);
        
        if(counter > 10){
            loose_sprite_window_box_internal = sfg::Box::Create( sfg::Box::Orientation::HORIZONTAL);
            looseSpriteWindowInternal = sfg::ScrolledWindow::Create();
            looseSpriteWindowInternal->SetScrollbarPolicy( sfg::ScrolledWindow::VERTICAL_NEVER | sfg::ScrolledWindow::HORIZONTAL_NEVER );
            looseSpriteWindowInternal->AddWithViewport(loose_sprite_window_box_internal);
            scrolled_window_box->Pack(loose_sprite_window_box_internal);
            counter = 0;
        }
        loose_sprite_window_box_internal->Pack(button);
        counter++;
        
    }
    
    scrolledWindow->SetRequisition(Vector2f(462, mainWindow.getSize().y/2));
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
                WorldExporter::exportWorld(world, assetManager.getTextureContainers());
                cout << "World Exported!" << endl;
            }
            if(event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Right){
                originalMousePosition = new Vector2i(sf::Mouse::getPosition(mainWindow));
            }
            else if(event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Right){
                for(Sprite* sprite: world){
                    sprite->setPosition(*roundTo((sf::Mouse::getPosition(mainWindow) - *originalMousePosition) + (Vector2i)sprite->getPosition(), (Vector2i)currentlyPickedImage->getSize()));
                }
                cout<<"position of first sprite = ("<<world[0]->getPosition().x<<", " << world[0]->getPosition().y<< ")"<<endl;
            }
            else if(sf::Mouse::isButtonPressed(sf::Mouse::Left) && currentlyPickedImage != nullptr){
                sf::Sprite* sprite = new Sprite();
                sprite->setTexture(*currentlyPickedImage);
                sprite->setOrigin(sprite->getTexture()->getSize().x-7, sprite->getTexture()->getSize().y+18.5f);
                sprite->setPosition(*roundTo(sf::Mouse::getPosition(mainWindow), (Vector2i)currentlyPickedImage->getSize()));
                world.push_back(sprite);
                cout << "Added a tile at (" << sprite->getPosition().x << ", " << sprite->getPosition().y << ")" << endl;
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


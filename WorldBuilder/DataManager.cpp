//
//  DataManager.cpp
//  WorldBuilder
//
//  Created by Bartosz Osowski on 21/09/2018.
//  Copyright © 2018 Bartosz Osowski. All rights reserved.
//

#include "DataManager.hpp"

bool DataManager::exportWorld(const vector<sf::Sprite*>& worldData, const vector<TextureContainer*>& textureContainers){
    rapidxml::xml_document<> doc;
    rapidxml::xml_node<>* decl = doc.allocate_node(rapidxml::node_declaration);
    decl->append_attribute(doc.allocate_attribute("version", "1.0"));
    decl->append_attribute(doc.allocate_attribute("encoding", "UTF-8"));
    doc.append_node(decl);
    rapidxml::xml_node<>* root = doc.allocate_node(rapidxml::node_element, "root");
    rapidxml::xml_node<>* legend = doc.allocate_node(rapidxml::node_element, "legend");
    for(const TextureContainer* container: textureContainers){
        rapidxml::xml_node<>* legendNode = doc.allocate_node(rapidxml::node_element, "legendNode");
        legendNode->append_attribute(doc.allocate_attribute("index", (new string(to_string(container->index).c_str()))->c_str()));
        legendNode->append_attribute(doc.allocate_attribute("location", container->imageLocation.c_str()));
        legend->append_node(legendNode);
    }
    
    rapidxml::xml_node<>* world = doc.allocate_node(rapidxml::node_element, "world");
    for(sf::Sprite* sprite: worldData){
        rapidxml::xml_node<>* tile = doc.allocate_node(rapidxml::node_element, "tile");
        tile->append_attribute(doc.allocate_attribute("index", (new string(to_string(*getSpriteIndex(textureContainers, *sprite))))->c_str()));
        rapidxml::xml_node<>* position = doc.allocate_node(rapidxml::node_element, "position");
        position->append_attribute(doc.allocate_attribute("x", (new string(to_string(sprite->getPosition().x)))->c_str()));
        position->append_attribute(doc.allocate_attribute("y", (new string(to_string(sprite->getPosition().y)))->c_str()));
        tile->append_node(position);
        world->append_node(tile);
    }
    
    root->append_node(legend);
    root->append_node(world);
    doc.append_node(root);
    
    std::ofstream file_stored("/Users/bOsowski/Desktop/world_data.xml");
    file_stored << doc;
    file_stored.close();
    doc.clear();
    
    return true;
}

bool DataManager::importWorld(vector<sf::Sprite *> &worldData, vector<TextureContainer *> &textureContainers){
    worldData.clear();
    textureContainers.clear();
    
    std::ifstream file_stored("/Users/bOsowski/Desktop/world_data.xml");
    rapidxml::xml_document<> doc;
    string stringFileContents = "";
    string line;
    while(getline(file_stored, line)){
        stringFileContents += line+"\n";
    }
    
    doc.parse<0>((char*)stringFileContents.c_str());
    cout << "Name of my first node is: " << doc.first_node()->name() << "\n";
    rapidxml::xml_node<> *firstNode = doc.first_node(doc.first_node()->name())->first_node();
    cout << "Node root has value '" << firstNode->value() << "'\n";
    
    //images
    for(rapidxml::xml_node<> *node = firstNode->first_node(); node; node = node->next_sibling()){
        TextureContainer* container = new TextureContainer();
        container->index = stoi(string(node->first_attribute("index")->value()));
        container->imageLocation = string(node->first_attribute("location")->value());
        if (container->image.loadFromFile(container->imageLocation)) {
            container->texture.loadFromImage(container->image);
        }
        cout << container->index << " " << container->imageLocation << endl;
        textureContainers.push_back(container);
    }
    
    //positions
    for(rapidxml::xml_node<> *node = firstNode->next_sibling()->first_node(); node; node = node->next_sibling()){
        int index = stoi(string(node->first_attribute("index")->value()));
        float x = stof(string(node->first_node()->first_attribute("x")->value()));
        float y = stof(string(node->first_node()->first_attribute("y")->value()));
        sf::Sprite* sprite = new Sprite();
        UserInterface::adjustSprite(sprite, textureContainers.at(index)->texture, *new sf::Vector2f(x,y));
        worldData.push_back(sprite);
    }
    return true;
}

int* DataManager::getSpriteIndex(const vector<TextureContainer*>& textureContainers, sf::Sprite& sprite){
    for(TextureContainer* container: textureContainers){
        if(&(container->texture) == &(*sprite.getTexture())){
            return new int(container->index);
        }
    }
    return new int(-1);
}


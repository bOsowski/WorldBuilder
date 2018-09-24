//
//  WorldExporter.cpp
//  WorldBuilder
//
//  Created by Bartosz Osowski on 21/09/2018.
//  Copyright © 2018 Bartosz Osowski. All rights reserved.
//

#include "WorldExporter.hpp"

bool WorldExporter::exportWorld(const vector<sf::Sprite*>& worldData, const vector<TextureContainer*>& textureContainers){
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

int* WorldExporter::getSpriteIndex(const vector<TextureContainer*>& textureContainers, sf::Sprite& sprite){
    for(TextureContainer* container: textureContainers){
        if(&(container->texture) == &(*sprite.getTexture())){
            return new int(container->index);
        }
    }
    return new int(-1);
}


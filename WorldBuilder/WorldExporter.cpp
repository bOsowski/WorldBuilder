//
//  WorldExporter.cpp
//  WorldBuilder
//
//  Created by Bartosz Osowski on 21/09/2018.
//  Copyright © 2018 Bartosz Osowski. All rights reserved.
//

#include "WorldExporter.hpp"

static bool exportWorld(const vector<sf::Sprite*> world, const vector<TextureContainer*> textureContainer){
    rapidxml::xml_document<> doc;
    rapidxml::xml_node<>* decl = doc.allocate_node(rapidxml::node_declaration);
    decl->append_attribute(doc.allocate_attribute("version", "1.0"));
    decl->append_attribute(doc.allocate_attribute("encoding", "UTF-8"));
    doc.append_node(decl);
    rapidxml::xml_node<>* root = doc.allocate_node(rapidxml::node_element, "page");
    root->append_attribute(doc.allocate_attribute("Number of lines", "10"));
    doc.append_node(root);
    
    for(sf::Sprite* sprite: world){
        
    }
}

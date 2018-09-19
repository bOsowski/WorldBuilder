#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include "AssetManager.hpp"
#include "UserInterface.hpp"

// Here is a small helper for you! Have a look.
#include "ResourcePath.hpp"

int main(int, char const**)
{
    
    UserInterface::instance();

    return EXIT_SUCCESS;
}


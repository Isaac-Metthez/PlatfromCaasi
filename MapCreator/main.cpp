#include "../PlatfromCaasi/PlatfromCaasi/Platfrom.h"
#include <SFML/Graphics.hpp>
#include "Map.h"

int main()
{
    platfrom::map::POC map;
    map.walk();
    map.web();
    map.air();
    map.pole();
    return 0;
}

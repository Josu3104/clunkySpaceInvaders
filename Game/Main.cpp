#include <iostream>
#include "TextConsole.h"
#include "MyGame.h"
#include "invaders.h"

std::string squid ="\x7\x8\x9";
std::string crab ="\x1\x2\x3";
std::string octopus ="\x4\x5\x6";

int main(int argc, char *argv[])
{
    std::vector<std::string> sprites = {squid, crab, crab , octopus, octopus};
    //Esto setea la consola como un arreglo, se le indican las dimensiones
    TextConsole con(120,40);

    if (!con.activate()) {
        return 1;
    }
    MyGame game(con,sprites);

    con.run(game);
    
    return 0;
}
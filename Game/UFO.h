#pragma once
#include "TextConsole.h"
#include <iostream>
#include <vector>


class ship;
class UFO
{
public:
    UFO(TextConsole &cs, std::string sprite)
        :speed(3), alive(false), sprite(sprite), KON(cs),UFOkilled(false) {}

    void move();

    void spawn();

    void drawUFO(); 

    void clearUFO();

    void checkCollisions(ship& nave);

    bool isAlive() { return alive; }
    void reset() { alive = false; }
    int getX(){return x;}
    bool wasUfoKilled(){return UFOkilled;}
    void resetUFOkill(){UFOkilled=false;}

private:
    int x, y, speed;
    bool alive;
    std::string sprite;
    TextConsole& KON;
    bool UFOkilled;
};
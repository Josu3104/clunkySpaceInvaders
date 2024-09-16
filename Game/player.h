
#pragma once
#include "TextConsole.h"
#include <iostream>
#include <vector>

class invaders;

class Beam
{
public:
    Beam(int x, int y, bool who)
        : x(x), y(y), active(true), alienShoots(who) {}

    void move()
    {
        if (alienShoots)
        {
            y++;
        }
        else
        {
            --y;
        }

        if (y < 2 || y >= 40)
        {
            active = false;
        }
    }

    int getX() const
    {
        return x;
    }

    int getY() const
    {
        return y;
    }

    bool isActive() const
    {
        return active;
    }

    void deactivate()
    {
        active = false;
    }

private:
    int x, y;
    bool active;
    bool alienShoots;
};

class ship
{

public:
    ship(TextConsole &cons) : KON(cons), X(20), Y(30), lives(3)
    {
        KON.setCursor(Y, X);
        KON << "\xB\xC\xD";
    }

    void move(uint32_t tecla);

    void shootPlayerBeams()
    {
        playerBeams.emplace_back(X + 1, Y - 1, false);
    }

    int getX() { return X; }

    int getY() { return Y; }
    int& getLives() { return lives; }
    bool isPlayerDead() { return lives == 0; }
    void revivePlayer(){lives=3;}
    void resetBeams(){playerBeams.clear();}
    void receiveDmg() { lives -= 1; }
    int getKilledAlien(){return shotAlien;}
    void resetShotAlien(){shotAlien=0;}
    void updatePlayerBeams();

    void checkCollisions(invaders &invs);

    std::vector<Beam> playerBeams;

private:
    int X, Y;
    int lives;
    int shotAlien;

    TextConsole &KON;
    std::string squid = "\x7\x8\x9";
    std::string crab = "\x1\x2\x3";
    std::string octopus = "\x4\x5\x6";
    
    int spriteType(std::string sprt)
    {
        if (sprt ==squid)
        {
            return 1;
        }
        else if (sprt==crab)
        {
            return 2;
        }
        else if (sprt == octopus)
        {
            return 3;
        }else
        return 0;

    }
};

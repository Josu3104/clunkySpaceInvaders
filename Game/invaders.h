#pragma once
#include "TextConsole.h"
#include <iostream>
#include "player.h"
#include <vector>
#include <array>
#include <ctime>
#include <random>

class Alien
{

public:
    Alien(int x, int y, const std::string &sprite) : X(x), Y(y), sprite(sprite), alive(true) {}

    void moveHorizontal(int direction)
    {
        if (direction == 1)
        {
            X += 3;
        }
        else
        {
            X -= 3;
        }
    }

    void moveDown()
    {
        Y += 1;
    }

    void clear()
    {
        sprite = "   ";
    }

    bool isAlive() const { return alive; }
    void kill() { alive = false; }

    int getX() const { return X; }
    int getY() const { return Y; }
    const std::string &getSprite() const { return sprite; }

private:
    int X, Y;
    std::string sprite;
    bool alive;
};
/*TODO


    -puntajes por invasor
    -vidas
    -menu
*/
class invaders
{
public:
    invaders(TextConsole &console, int startX, int startY, std::vector<std::string> rS)
        : KON(console), startX(startX), startY(startY), direction(1), grid(5, std::vector<Alien>(11, Alien(0, 0, ""))), allAliensAreDead(false), hitOnplayer(false), collisionHappened(false)
    {
        initializeAliens(rS);
        currentBottomRow = 4;
    }

    void initializeAliens(const std::vector<std::string> &rowSprites);

    void move();

    void drawAliens();

    void clearAliens();

    void removeDeadAliens();

    void shootAlienBeam();
    void updateAlienBeams(ship &player);
    void resetAlienBeams() { alienBeams.clear(); }
    void checkAlienCollisions(ship &player);
    int getBottomRow() { return currentBottomRow; }
    void updateBottomRow();
    void collisionBREAK();
    bool aliensReachedBottom() { return collisionHappened; }

    std::vector<std::vector<Alien>> &getGrid() { return grid; };
    bool &getallAliensAreDead() { return allAliensAreDead; }
    void reviveAliens()
    {
        allAliensAreDead = false;
        currentBottomRow = 4;
        direction = 1;
        startX = 5, startY = 5;
        collisionHappened = false;
    }

private:
    bool hitRightCorner() const
    {
        for (int r = 0; r < 5; ++r)
        {
            for (int c = 0; c < 11; ++c)
            {
                if (grid[r][c].isAlive() && grid[r][c].getX() + 6 >= KON.getColCount())
                {
                    return true;
                }
            }
        }
        return false;
    }

    bool hitLeftCorner() const
    {
        for (int r = 0; r < 5; ++r)
        {
            for (int c = 0; c < 11; ++c)
            {
                if (grid[r][c].isAlive() && grid[r][c].getX() - 3 <= 0)
                {
                    return true;
                }
            }
        }
        return false;
    }

    void moveDown()
    {
        for (int r = 0; r < 5; ++r)
        {
            for (int c = 0; c < 11; ++c)
            {
                if (grid[r][c].isAlive())
                {
                    grid[r][c].moveDown();
                }
            }
        }
    }

    TextConsole &KON;
    int startX, startY;
    int direction; // 1 right -1op
    bool allAliensAreDead;
    std::vector<std::vector<Alien>> grid;
    std::vector<Beam> alienBeams;
    int currentBottomRow;
    bool hitOnplayer;
    bool collisionHappened;
};

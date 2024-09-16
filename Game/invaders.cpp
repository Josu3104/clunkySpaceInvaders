#include "invaders.h"
#include "player.h"

void invaders::initializeAliens(const std::vector<std::string> &rowSprites)
{
    for (int r = 0; r < 5; ++r)
    {
        for (int c = 0; c < 11; ++c)
        {
            grid[r][c] = Alien(startX + c * 5, startY + r * 2, rowSprites[r]);
        }
    }
}

void invaders::move()
{

    clearAliens();

    for (int r = 0; r < 5; ++r)
    {
        for (int c = 0; c < 11; ++c)
        {
            if (grid[r][c].isAlive())
            {
                grid[r][c].moveHorizontal(direction);
            }
        }
    }

    if (direction == 1 && hitRightCorner())
    {
        direction = -1;
        moveDown();
    }
    else if (direction == -1 && hitLeftCorner())
    {
        direction = 1;
        moveDown();
    }

    drawAliens();
    // updateBottomRow();
}

void invaders::drawAliens()
{
    for (int r = 0; r < 5; ++r)
    {
        for (int c = 0; c < 11; ++c)
        {
            if (grid[r][c].isAlive())
            {
                KON.setForecolor(CColor::White);
                KON.setCursor(grid[r][c].getY(), grid[r][c].getX());
                KON << grid[r][c].getSprite();
            }
        }
    }
}

void invaders::clearAliens()
{
    for (int r = 0; r < 5; ++r)
    {
        for (int c = 0; c < 11; ++c)
        {
            if (grid[r][c].isAlive())
            {
                KON.setCursor(grid[r][c].getY(), grid[r][c].getX());
                KON << "   ";
            }
        }
    }
}

void invaders::removeDeadAliens()
{
    for (int r = 0; r < 5; ++r)
    {
        for (int c = 0; c < 11; ++c)
        {
            if (!grid[r][c].isAlive())
            {
                grid[r][c].clear();
            }
        }
    }
    updateBottomRow();
}

void invaders::shootAlienBeam()
{
    // Demencia
    if (currentBottomRow == -1)
        return;
    bool hasRemains = true;
    std::vector<int> aliveAliens;
    for (int c = 0; c < 11; ++c)
    {
        if (grid[currentBottomRow][c].isAlive())
        {
            aliveAliens.push_back(c);
        }
    }

    if (!aliveAliens.empty())
    {
        std::random_device rd;
        std::uniform_int_distribution<int> dist(0, aliveAliens.size() - 1);
        int chosenAlien = aliveAliens[dist(rd)];

        alienBeams.emplace_back(grid[currentBottomRow][chosenAlien].getX() + 1, grid[currentBottomRow][chosenAlien].getY() + 1, true);
    }
}

void invaders::updateAlienBeams(ship &player)
{
    for (auto &beam : alienBeams)
    {
        if (!beam.isActive())
            continue;

        KON.setCursor(beam.getY(), beam.getX());
        KON << ' ';

        beam.move();

        if (beam.isActive())
        {

            KON.setCursor(beam.getY(), beam.getX());
            KON << '|';
        }
    }
}

void invaders::checkAlienCollisions(ship &player)
{
    for (auto &beam : alienBeams)
    {
        if (!beam.isActive())
            continue;

        if (beam.getX() >= player.getX() && beam.getX() < player.getX() + 3 &&
            beam.getY() == player.getY())
        {
            beam.deactivate();
            player.receiveDmg();
            hitOnplayer = true;
        }
    }
}

void invaders::updateBottomRow()
{
    bool rowFound = false;
    for (int r = currentBottomRow; r >= 0; --r)
    {
        for (int c = 0; c < 11; c++)
        {
            if (grid[r][c].isAlive())
            {
                currentBottomRow = r;
                rowFound = true;
                break;
            }
        }
        if (rowFound)
            break;
    }

    if (!rowFound)
    {
        if(currentBottomRow==0)
        currentBottomRow -= 1;
        
        allAliensAreDead = true;
    }
}

void invaders::collisionBREAK()
{
    //first Alive
    if(currentBottomRow<0||currentBottomRow>=5){return;} //last found crash (Hope so :) )
    int pos = -1;
    for (int i = 0; i < 5; ++i)
    {
        if (grid[currentBottomRow][i].isAlive())
        {
            pos = i;
            break;
        }
    }
    if (pos == -1) { return; }
    Alien bottom = grid[currentBottomRow][pos];

    if (bottom.getY() > 28)
    {
        collisionHappened = true;
    }
}

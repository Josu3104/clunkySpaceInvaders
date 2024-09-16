#include "UFO.h"
#include "player.h"
void UFO::move()
{
    if (alive)
    {
        clearUFO();
        x += speed;
        if (x+3>KON.getColCount())
        {
            alive = false;
        }
    }
}

void UFO::spawn()
{
    if (!alive)
    {
        x = 0;
        y = 2;
        alive = true;
        UFOkilled = false;
        //std::cout<<">>Ta vivo";
    }
}

void UFO::drawUFO()
{

    if (alive)
    {
        KON.setForecolor(CColor::White);
        KON.setCursor(y, x);
        KON << sprite;
        KON.refresh();
    }
    
}

void UFO::clearUFO()
{
  
        KON.setCursor(y, x);
        KON << "   ";
    
}

void UFO::checkCollisions(ship &nave)
{

    for (auto beam : nave.playerBeams)
    {
        if (beam.getX() >= x && beam.getX() < x+2 && beam.getY() == y)
        {
            reset();
            beam.deactivate();
            UFOkilled=true;
            std::cout << "BULLSEYE\n";
        }
    }
}


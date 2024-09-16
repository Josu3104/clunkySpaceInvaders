#include "invaders.h"
#include "player.h"

void ship::move(uint32_t tecla)
{
    if (tecla != SDLK_UNKNOWN)
    {

        KON.setCursor(Y, X);
        KON << "   ";

        switch (tecla)
        {
        case SDLK_a:

            if (X - 2 >= 1)
                X -= 2;
            break;
        case SDLK_d:

            if (X + 3 < KON.getColCount() - 3)
                X += 2;

            break;
        case SDLK_SPACE:
            shootPlayerBeams();
            break;
        }
        KON.setForecolor(CColor::Green1);
        KON.setCursor(Y, X);
        KON << "\xB\xC\xD";
    }
}

void ship::updatePlayerBeams()
{
    for (auto &beam : playerBeams)
    {
        if (!beam.isActive())
            continue;

        KON.setCursor(beam.getY(), beam.getX());
        KON << ' ';

        beam.move();

        if (beam.isActive())
        {
            KON.setForecolor(CColor::White);
            KON.setCursor(beam.getY(), beam.getX());
            KON << '|';
        }
    }

    // purga
    for (auto it = playerBeams.begin(); it != playerBeams.end();)
    {
        if (!it->isActive())
        {
            it = playerBeams.erase(it);
        }
        else
        {
            ++it; // skip
        }
    }
}

void ship::checkCollisions(invaders &invs)
{

    for (auto &beam : playerBeams)
    {
        if (!beam.isActive())
        {
            continue;
        }

        int beamX = beam.getX();
        int beamY = beam.getY();

        for (int r = 0; r < 5; ++r)
        {
            for (int c = 0; c < 11; ++c)
            {

                Alien &alien = invs.getGrid()[r][c];

                if (alien.isAlive() && beamX >= alien.getX() && beamX < alien.getX() + 3 &&
                    beamY == alien.getY())
                {
                    shotAlien = spriteType(alien.getSprite());
                    alien.kill();
                    beam.deactivate();

                    KON.setCursor(alien.getY(), alien.getX());
                    KON << "   ";
                    // Demencia check
                    invs.removeDeadAliens();
                    
                }
            }
        }
    }

    // Purga de beams que hacian overlap al alien
    for (auto it = playerBeams.begin(); it != playerBeams.end();)
    {
        if (!it->isActive())
        {
            it = playerBeams.erase(it);
        }
        else
        {
            ++it;
        }
    }
}

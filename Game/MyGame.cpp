#include "MyGame.h"
#include <vector>

// inicia en 0
// Limite es 120-3  (3 espacios que toma el alien)
// Y, X
void MyGame::run()
{
  while (true)
  {
    con.setBackcolor(CRGBColor(0x00, 0x00, 0x00));
    con.clearScreen();
    con.setForecolor(CColor::Red1);
  con.setForecolor(CColor::White);
    con.setCursor(10, 43);
    con << "\x1\x2\x3 S P A C E  I N V A D E R S \x1\x2\x3";
    con.setForecolor(CColor::White);
    con.setCursor(15, 44);
    con << "PRESS ANY KEY TO DEFEND EARTH";

    con.refresh();

    while (con.getKey() == SDLK_UNKNOWN)
    {
      std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }

    con.clearScreen();
    resetGame();
    con.setForecolor(CColor::White);
    con.setCursor(1, 5);
    con << "SCORE: ";
    con.setForecolor(CColor::White);
    con.setCursor(1, 100);
    con << "LIVES: ";

    alienThread = std::thread(&MyGame::moveAliens, this);
    playerThread = std::thread(&MyGame::playerControl, this);
    ufoThread = std::thread(&MyGame::moveUFO, this);

    if (ufoThread.joinable())
      ufoThread.join();
    if (alienThread.joinable())
      alienThread.join();
    if (playerThread.joinable())
      playerThread.join();

  con.refresh();
    con.clearScreen();
    con.setCursor(10, 52);
    if (nave.getLives() == 0 || attackers.aliensReachedBottom())
    {
      con.setForecolor(CColor::White);
      con << "G A M E   O V E R ";
      con.setCursor(12, 53);
      con << "EARTH IS LOST";
    }
    else if (attackers.getallAliensAreDead())
    {
      con.setForecolor(CColor::White);
      con << " W E L L   D O N E ";
      con.setCursor(12, 53);
      con << "EARTH IS SAVED";
    }
    con.refresh();
    std::this_thread::sleep_for(std::chrono::milliseconds(3000));

    con.flushKeybuffer();
  }
}

#ifndef __GAME_H__
#define __GAME_H__
#include "TextConsole.h"
#include <algorithm>
#include "invaders.h"
#include "player.h"
#include "UFO.h"
#include <iostream>
#include <thread>
#include <mutex>

class MyGame : public CClient
{
    friend class invaders;
    friend class ship;

public:
    MyGame(TextConsole &con, std::vector<std::string> sprites) : CClient(con), nave(con), attackers(con, 5, 5, sprites),
                                                                 exit(false), start(false), ovni(con, "\x010\x011\x012"),
                                                                 scoreCoords(1, 11),score(0), revivalSprites(sprites) {}
    void run() override;

private:
    invaders attackers;
    ship nave;
    UFO ovni;
    std::thread alienThread;
    std::thread playerThread;
    std::thread ufoThread;
    std::mutex mtx;
    bool exit, start;
    std::pair<int, int> scoreCoords;
    int prevLives;
    std::vector<std::string> revivalSprites;
    int score;

    void updateScore()
    {
        con.setForecolor(CColor::White);
        con.setCursor(scoreCoords.first, scoreCoords.second);
        con << score;
        int result = nave.getKilledAlien();

        std::random_device rand;
        std::uniform_int_distribution<int> randy(50, 300);

        if (ovni.wasUfoKilled())
        {
            score += randy(rand);
            ovni.resetUFOkill();
        }
        
        if (result > 0)
        {
            switch (result)
            {
            case 1: // SQUID 30 PTS
                score += 30;
                break;
            case 2: // CRAB 10 PTS
                score += 10;
                break;
            case 3: // OCTOPUS 10 PTS
                score += 10;
                break;
            default:
                std::cout << "Retirando la clase  . . .";
                break;
            }
        }
           nave.resetShotAlien();
           
    }

    void clearLives()
    {
        int y = 1;
    int x = 107;
    for (int i = 0; i < prevLives; ++i)
    {
        con.setCursor(y, x);
        con << "   "; 
        x += 4;
    }
    }
    void updateLives()
    {
        clearLives();
         int y=1;
        int x=107;
        int& countLives = nave.getLives();
        prevLives = countLives;
        std::vector<std::string> temp(countLives,"\x0B\x0C\x0D");
       
         for(auto &icon:temp)
         {
             con.setForecolor(CColor::Green1);
             con.setCursor(y,x);
             con<<icon;
             x+=4;
         }
         

    }

    bool GameOver()
    {
        return attackers.getallAliensAreDead() || nave.isPlayerDead()|| attackers.aliensReachedBottom();
    }

    void resetGame()
    {
    
        attackers.reviveAliens();
        nave.revivePlayer();
        attackers.initializeAliens(revivalSprites);
        nave.resetBeams();
        attackers.resetAlienBeams();
        score=0;
    }

    void playerControl()
    {
        while (!GameOver())
        {
            if(GameOver())
            {
                break;
            }
            std::this_thread::sleep_for(std::chrono::milliseconds(90));

            nave.move(con.getKey());
            nave.updatePlayerBeams();
            nave.checkCollisions(attackers);
            con.flushKeybuffer();
            updateScore();
            con.refresh();
        }
        
    }


    void moveAliens()
    {

        while (!GameOver())
        {
          
            std::this_thread::sleep_for(std::chrono::milliseconds(600));
            // std::lock_guard<std::mutex> lock(mtx);
            attackers.drawAliens();
            attackers.move();
            attackers.shootAlienBeam();
            attackers.updateAlienBeams(nave);
            attackers.checkAlienCollisions(nave);
            attackers.collisionBREAK();
            updateLives();
            con.refresh();
        }
    }

    void moveUFO()
    {
        std::random_device rand;
        std::uniform_int_distribution<int> randy(3, 20);

        while (!GameOver())
        {

            std::this_thread::sleep_for(std::chrono::seconds(randy(rand)));
            if (GameOver())
            {
                break;
            }
            ovni.spawn();
            // std::cout<<"Is this even reached";
            // Missed the & at KON
            while (ovni.isAlive())
            {
                std::this_thread::sleep_for(std::chrono::milliseconds(500));
                if (GameOver())
                {
                    break;
                }
                ovni.move();
                ovni.drawUFO();
                 ovni.checkCollisions(nave);

                // std::cout<<ovni.getX()<<"\n";
            }
            ovni.clearUFO();
        }
        con.refresh();
    }

   
};

#endif
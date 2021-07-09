#ifndef GAME_H
#define GAME_H

#include "../include/Player.h"
#include "../include/Bullet.h"
#include "../include/Enemy.h"
#include <map>
#include <list>


class Game
{
public:

                                            Game();
                                            ~Game();
    void                                    run();

private:

                                            // Window
    sf::RenderWindow                        window;

                                            // Player
    Player*                                 player;
    std::list<Bullet*>                      bullets;
    unsigned                                playerPoints;
                                            
                                            // Resources
    std::map<std::string, sf::Texture*>     textures;
                                            
                                            // Background
    sf::Sprite                              backgroundSprite;

                                            // Enemies
    std::list<Enemy*>                       enemies;
    int                                     enemySpawnTimer;
    const int                               MAX_ENEMY_SPAWN_TIMER;

                                            // GUI
    sf::Font                                font;
    sf::Text                                pointsText;
    sf::RectangleShape                      playerHealthBar;
    sf::RectangleShape                      playerHealthBarBackground;

                                            // Action methods
    void                                    processEvents();

    void                                    update();
    void                                    updateInput();
    void                                    updateBullets();
    void                                    updateEnemiesAndCombat();
    void                                    updateGUI();
    void                                    updateWindowBoundsCollision();

    void                                    render();
    void                                    renderGUI();
    void                                    renderBackground();

                                            // Initialization methods
    void                                    initTextures();
    void                                    initPlayer();
    void                                    initGUI();
    void                                    initBackground();
};


#endif // GAME_H




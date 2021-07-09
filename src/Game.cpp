#include "../include/Game.h"
#include <sstream>


Game::Game()
    : window(sf::VideoMode(800, 600), "Space conqueror", sf::Style::Close),
     MAX_ENEMY_SPAWN_TIMER(105), enemySpawnTimer(130), playerPoints(0)
{
    window.setFramerateLimit(60);
    
    initTextures();
    initPlayer();
    initGUI();
    initBackground();

    player->setPosition(window.getSize().x / 2 - player->getBounds().width / 2, window.getSize().y / 2);
}


Game::~Game()
{
    // Removing textures
    for (auto el = textures.begin(); el != textures.end(); ++el)
    {
        delete el->second;
    }
    textures.clear();

    // Removing bullets
    for (auto b = bullets.begin(); b != bullets.end(); ++b)
    {
        delete *b;
    }
    bullets.clear();

    // Removing enemies
    for (auto e = enemies.begin(); e != enemies.end(); ++e)
    {
        delete *e;
    }

    delete player;
}


void Game::run()
{
    while (window.isOpen())
    {
        processEvents();
        update();
        render();
    }
}


void Game::processEvents()
{
    sf::Event event;
    while (window.pollEvent(event))
    {
        switch (event.type)
        {
        case sf::Event::Closed:
            {
                window.close();
                break;
            }
        case sf::Event::KeyPressed:
            {
                if (event.key.code == sf::Keyboard::Escape)
                {
                    window.close();
                }
                break;
            }
        }
    }
}


void Game::update()
{
    updateInput();

    player->update();

    updateWindowBoundsCollision();

    updateBullets();

    updateEnemiesAndCombat();
    
    updateGUI();
}


void Game::updateInput()
{
    // Moving player
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
    {
        player->move(-1.f, 0.f);
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
    {
        player->move(1.f, 0.f);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
    {
        player->move(0.f, -1.f);
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
    {
        player->move(0.f, 1.f);
    }

    // Player's attack
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && player->canAttack())
    {
        bullets.push_back(
            new Bullet(
                *textures["BULLET"], 
                player->getPosition().x + player->getBounds().width / 2 - 5.f, 
                player->getPosition().y
            )
        );
    }
}


void Game::updateBullets()
{
    auto b = bullets.begin();
    while (b != bullets.end())
    {
        (*b)->move(0.f, -1.f);

        if ((*b)->getPosition().y < 0.f - (*b)->getBounds().height) // Bullet is outside the screen
        {
            delete *b;
            b = bullets.erase(b);
        }
        else
        {
            ++b;
        }
    }
}


void Game::updateEnemiesAndCombat()
{
    if (enemySpawnTimer < MAX_ENEMY_SPAWN_TIMER)
    {
        ++enemySpawnTimer;
    }

    if (enemySpawnTimer >= MAX_ENEMY_SPAWN_TIMER)
    {
        enemySpawnTimer = 0;
        enemies.push_back(
            new Enemy(
                rand() % (int)(window.getSize().x - Enemy::MAX_RADIUS * 2), 
                -(Enemy::MAX_RADIUS * 2)
            )
        );
    }

    auto e = enemies.begin();
    while (e != enemies.end())
    {
        (*e)->move(0.f, 1.f);
        
        bool enemyIsDestroyed   = false;
        auto b                  = bullets.begin();
        while (b != bullets.end() && !enemyIsDestroyed)
        {
            if ((*e)->getBounds().intersects((*b)->getBounds())) // Collision between bullet and enemy
            {
                playerPoints += (*e)->getPoints();

                delete *e;
                delete *b;
                e = enemies.erase(e);
                b = bullets.erase(b);

                enemyIsDestroyed = true;
            }
            else
            {
                ++b;
            }
        }
        

        if (!enemyIsDestroyed)
        {
            if ((*e)->getBounds().top > window.getSize().y ||
                (*e)->getBounds().intersects(player->getBounds()))
            {
                delete *e;
                e = enemies.erase(e);
            }
            else
            {
                ++e;
            }
        }
    }
}


void Game::updateGUI()
{
    std::stringstream msg;
    msg << "Points: " << playerPoints << '\n';
    pointsText.setString(msg.str());


    playerHealthBar.setSize(
        sf::Vector2f(
            playerHealthBarBackground.getSize().x * ((float)player->getHealth() / player->getMaxHealth()), 
            playerHealthBarBackground.getSize().y
        )
    );
}


void Game::updateWindowBoundsCollision()
{
    // Left collision
    if (player->getPosition().x < 0.f)
    {
        player->setPosition(0.f, player->getPosition().y);
    }

    // Right collision
    else if (player->getPosition().x + player->getBounds().width > window.getSize().x)
    {
        player->setPosition(window.getSize().x - player->getBounds().width, player->getPosition().y);
    }

    // Top collision
    if (player->getPosition().y < 0.f)
    {
        player->setPosition(player->getPosition().x, 0.f);
    }

    // Bottom collision
    else if (player->getPosition().y + player->getBounds().height > window.getSize().y)
    {
        player->setPosition(player->getPosition().x, window.getSize().y - player->getBounds().height);
    }
}


void Game::render()
{
    // Clear, draw, display
    window.clear();

    renderBackground();

    player->render(window);

    for (auto b = bullets.begin(); b != bullets.end(); ++b)
    {
        (*b)->render(window);
    }
    
    for (auto e = enemies.begin(); e != enemies.end(); ++e)
    {
        (*e)->render(window);
    }

    renderGUI();

    window.display();
}


void Game::renderGUI()
{
    window.draw(pointsText);
    window.draw(playerHealthBarBackground);
    window.draw(playerHealthBar);
}


void Game::renderBackground()
{
    window.draw(backgroundSprite);
}


void Game::initTextures()
{
    textures["BULLET"] = new sf::Texture();
    textures["PLAYER"] = new sf::Texture();
    textures["BACKGROUND"] = new sf::Texture();

    textures["BULLET"]->loadFromFile("Textures/bullet.png");
    textures["PLAYER"]->loadFromFile("Textures/ship.png");
    textures["BACKGROUND"]->loadFromFile("Textures/background.jpg");
}


void Game::initPlayer()
{
    player = new Player(*textures["PLAYER"]);
}


void Game::initGUI()
{
    font.loadFromFile("Fonts/PixellettersFull.ttf");
    
    pointsText.setFont(font);
    pointsText.setCharacterSize(24);
    pointsText.setPosition(20.f, 20.f);


    playerHealthBar.setSize(sf::Vector2f(100.f, 20.f));
    playerHealthBar.setPosition(20.f, 60.f);
    playerHealthBarBackground = playerHealthBar;
    playerHealthBarBackground.setFillColor(sf::Color(15, 15, 15, 180));

    playerHealthBar.setFillColor(sf::Color::Red);
}


void Game::initBackground()
{
    backgroundSprite.setTexture(*textures["BACKGROUND"]);
}
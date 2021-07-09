#ifndef PLAYER_H
#define PLAYER_H

#include <SFML\Graphics.hpp>
#include <iostream>


class Player
{
public:

                            Player(const sf::Texture& texture);
    void                    update();
    void                    move(const float dirX, const float dirY);
    void                    render(sf::RenderTarget& target) const;
    const bool              canAttack();
    const bool              isDead() const;
    void                    reduceHealth(const int value);

    const sf::Vector2f      getPosition() const;
    const sf::FloatRect     getBounds() const;
    const int               getHealth() const;
    const int               getMaxHealth() const;

    void                    setPosition(const float x, const float y);

private:

    sf::Sprite              sprite;
    float                   movementSpeed;
    int                     attackCooldown;
    const int               MAX_ATTACK_COOLDOWN;
    int                     health;
    const int               MAX_HEALTH;

    void                    initSprite(const sf::Texture& texture);
    void                    initVariables();
};


#endif // PLAYER_H

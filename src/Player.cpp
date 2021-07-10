#include "../include/Player.h"


Player::Player(const sf::Texture& texture)
    : MAX_ATTACK_COOLDOWN(10), MAX_HEALTH(50)
{
    initSprite(texture);
    initVariables();
}


void Player::update()
{
    if (attackCooldown < MAX_ATTACK_COOLDOWN)
    {
        ++attackCooldown;
    }
}


void Player::move(const float dirX, const float dirY)
{
    sprite.move(movementSpeed * dirX, movementSpeed * dirY);
}


void Player::render(sf::RenderTarget& target) const
{
    target.draw(sprite);
}


const bool Player::canAttack()
{
    if (attackCooldown >= MAX_ATTACK_COOLDOWN)
    {
        attackCooldown = 0;
        return true;
    }
    return false;
}


const bool Player::isDead() const
{
    return health <= 0;
}


void Player::reduceHealth(const int value)
{
    health -= value;
    if (health < 0)
    {
        health = 0;
    }
}


const sf::Vector2f Player::getPosition() const
{
    return sprite.getPosition();
}


const sf::FloatRect Player::getBounds() const
{
    return sprite.getGlobalBounds();
}


const int Player::getHealth() const
{
    return health;
}


const int Player::getMaxHealth() const
{
    return MAX_HEALTH;
}


void Player::setPosition(const float x, const float y)
{
    sprite.setPosition(x, y);
}


void Player::initSprite(const sf::Texture& texture)
{
    sprite.setTexture(texture);
    sprite.setScale(0.1f, 0.1f);
}


void Player::initVariables()
{
    movementSpeed = 7.f;
    attackCooldown = MAX_ATTACK_COOLDOWN;
    health = MAX_HEALTH;
}


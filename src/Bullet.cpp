#include "../include/Bullet.h"


Bullet::Bullet(const sf::Texture& texture, const float positionX, const float positionY)
    : movementSpeed(7.f)
{
    sprite.setTexture(texture);
    sprite.setPosition(positionX, positionY);
}


void Bullet::move(const float dirX, const float dirY)
{
    sprite.move(movementSpeed * dirX, movementSpeed * dirY);
}


void Bullet::render(sf::RenderTarget& target)
{
    target.draw(sprite);
}


const sf::Vector2f Bullet::getPosition() const
{
    return sprite.getPosition();
}


const sf::FloatRect Bullet::getBounds() const
{
    return sprite.getGlobalBounds();
}
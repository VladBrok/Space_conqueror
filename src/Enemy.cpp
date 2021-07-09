#include "../include/Enemy.h"


const float Enemy::MAX_RADIUS = 50.f;


Enemy::Enemy(const float positionX, const float positionY)
    : MAX_DAMAGE(5)
{
    initShape(positionX, positionY);
    initVariables();
}


void Enemy::render(sf::RenderTarget& target) const
{
    target.draw(shape);
}


void Enemy::move(const float dirX, const float dirY)
{
    shape.move(movementSpeed * dirX, movementSpeed * dirY);
}


const sf::FloatRect Enemy::getBounds() const
{
    return shape.getGlobalBounds();
}


const int Enemy::getPoints() const
{
    return points;
}


void Enemy::initShape(const float posX, const float posY)
{
    shape.setPointCount(rand() % 8 + 3);
    shape.setRadius(shape.getPointCount() * 4);
    shape.setFillColor(sf::Color(rand() % 176 + 75, rand() % 176 + 75, rand() % 176 + 75, rand() % 101 + 155));
    shape.setPosition(posX, posY);
}


void Enemy::initVariables()
{
    damage          = 0;
    movementSpeed   = shape.getPointCount() / 2.f;
    points          = shape.getPointCount();
}


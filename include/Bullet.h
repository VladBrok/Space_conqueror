#ifndef BULLET_H
#define BULLET_H

#include <SFML/Graphics.hpp>


class Bullet
{
public:

                         Bullet(const sf::Texture& texture, const float positionX, const float positionY);
    void                 move(const float dirX, const float dirY);
    void                 render(sf::RenderTarget& target);
    const sf::Vector2f   getPosition() const;
    const sf::FloatRect  getBounds() const;

private:

    sf::Sprite           sprite;
    float                movementSpeed;
};


#endif // BULLET_H


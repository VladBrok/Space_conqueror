#ifndef ENEMY_H
#define ENEMY_H

#include <SFML/Graphics.hpp>


class Enemy
{
public:

    static const float      MAX_RADIUS;
                            Enemy(const float positionX, const float positionY);
    void                    render(sf::RenderTarget& target) const;
    void                    move(const float dirX, const float dirY);
    const sf::FloatRect     getBounds() const;
    const int               getPoints() const;

private:

    sf::CircleShape         shape;
    int                     damage;
    float                   movementSpeed;
    int                     points;
    const int               MAX_DAMAGE;

    void                    initShape(const float posX, const float posY);
    void                    initVariables();
};


#endif // ENEMY_H

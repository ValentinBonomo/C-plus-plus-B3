#include <iostream>
#include "enemy.h"

// Constructeur de l'ennemi, initialise la texture, la position et l'échelle.
Enemy::Enemy(float _axisX, float _addAxisY)
{
    enemy_texture.loadFromFile("img/mob.png");
    m_enemy.setTexture(enemy_texture);
    m_enemy.setPosition(sf::Vector2f(_axisX, (100.f + _addAxisY)));
    m_enemy.setScale(sf::Vector2f(.15f, .15f));
}

// Déplace l'ennemi selon les valeurs fournies en paramètres.
void Enemy::addPositonManual(float _x, float _y)
{
    m_enemy.setPosition(m_enemy.getPosition().x + _x, m_enemy.getPosition().y + _y);
}

// Affiche la position x et y de l'ennemi dans la console.
void Enemy::debug()
{
    std::cout << "Position(" << m_enemy.getPosition().x << ", " << m_enemy.getPosition().y << ")" << std::endl;
}

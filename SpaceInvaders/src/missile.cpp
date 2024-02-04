#include "missile.h"

// Constructeur du missile, initialise la taille et la couleur.
Missile::Missile()
{
    m_missile.setSize(sf::Vector2f(10.f, 35.f));
    m_missile.setFillColor(sf::Color::Red);
}

// D�finit la position du rectangle du missile.
void Missile::setPositionRectangle(sf::Vector2f _vectorpos)
{
    m_missile.setPosition(_vectorpos);
}

// D�place le missile selon le vecteur de d�placement fourni en param�tre.
void Missile::moveToPos(sf::Vector2f _move)
{
    m_missile.move(_move);
}

// D�finit si le missile est lanc� ou non.
void Missile::setMissileLauched(bool _value)
{
    m_missileLauched = _value;
}

// D�finit la vitesse du missile.
void Missile::setMissilespeed(float _value)
{
    m_missileSpeed = _value;
}

// D�finit si le missile est d�truit ou non.
void Missile::setMissileDestroyed(float _value)
{
    m_isMissileDestroyed = _value;
}

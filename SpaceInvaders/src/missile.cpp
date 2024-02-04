#include "missile.h"

// Constructeur du missile, initialise la taille et la couleur.
Missile::Missile()
{
    m_missile.setSize(sf::Vector2f(10.f, 35.f));
    m_missile.setFillColor(sf::Color::Red);
}

// Définit la position du rectangle du missile.
void Missile::setPositionRectangle(sf::Vector2f _vectorpos)
{
    m_missile.setPosition(_vectorpos);
}

// Déplace le missile selon le vecteur de déplacement fourni en paramètre.
void Missile::moveToPos(sf::Vector2f _move)
{
    m_missile.move(_move);
}

// Définit si le missile est lancé ou non.
void Missile::setMissileLauched(bool _value)
{
    m_missileLauched = _value;
}

// Définit la vitesse du missile.
void Missile::setMissilespeed(float _value)
{
    m_missileSpeed = _value;
}

// Définit si le missile est détruit ou non.
void Missile::setMissileDestroyed(float _value)
{
    m_isMissileDestroyed = _value;
}

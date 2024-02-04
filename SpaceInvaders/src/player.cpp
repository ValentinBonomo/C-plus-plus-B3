#include "player.h"

// Constructeur du joueur, charge la texture du joueur et initialise le sprite.
Player::Player()
{
    player_texture.loadFromFile("img/ship.png");
    m_sprite.setTexture(player_texture);
}

// D�place le joueur vers la gauche avec une vitesse donn�e.
void Player::moveLeft(float speed)
{
    if (m_sprite.getPosition().x - speed >= -m_sprite.getGlobalBounds().left)
    {
        m_sprite.move(sf::Vector2f(-speed, 0.f));
    }
}

// D�place le joueur vers la droite avec une vitesse donn�e en �vitant de d�passer la fen�tre.
void Player::moveRight(float speed, float windowWidth)
{
    if (m_sprite.getPosition().x + m_sprite.getGlobalBounds().width + speed <= windowWidth)
    {
        m_sprite.move(sf::Vector2f(speed, 0.f));
    }
}

// Initialise la position et l'�chelle du joueur en fonction de la taille de la fen�tre.
void Player::setPostionAndScale(float windowWidth, float windowHeight)
{
    sf::Vector2u textureSize = player_texture.getSize();
    m_sprite.setPosition(sf::Vector2f(0.5f * (windowWidth - textureSize.x * 0.2f), 0.9f * windowHeight - textureSize.y * 0.2f));
    m_sprite.scale(sf::Vector2f(.2f, 0.2f));
}

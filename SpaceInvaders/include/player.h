#pragma once
#include <SFML/Graphics.hpp>
#include "missile.h"

class Player
{
public:
	Player();
	void moveLeft(float speed);
	void moveRight(float speed, float windowWidth);
	const sf::Sprite& getSprite() { return m_sprite; }
	const float getFirerate() { return m_firerate; }
	void makeFirerateSmaller(int nbr) { m_firerate -= nbr; }
	void setPostionAndScale(float windowWidth, float windowHeight);

private:
	sf::Sprite m_sprite;
	sf::Texture player_texture;
	float m_firerate = .7f;
};
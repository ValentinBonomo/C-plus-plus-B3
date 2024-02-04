#pragma once
#include <SFML/Graphics.hpp>

class Enemy
{
public:
	Enemy(float _axisX, float _addAxisY);
	const sf::Sprite& getSprite() { return m_enemy; }
	void setEnemyDestroyed(){ m_isEnemyDestroyed = true; }
	bool isEnemyDestroyed() { return m_isEnemyDestroyed; }
	void addPositonManual(float _x, float _y);

	void debug();

	float getSpritePositionX() { return m_enemy.getPosition().x; }
	float getSpritePositionY() { return m_enemy.getPosition().y; }
	float getSpriteColliderWidth() { return m_enemy.getGlobalBounds().width; }

private:
	sf::Sprite m_enemy;
	sf::Texture enemy_texture;
	bool m_isEnemyDestroyed = false;
};
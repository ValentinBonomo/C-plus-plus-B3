#pragma once
#include <SFML/Graphics.hpp>

class Missile
{
public:
	Missile();
	void setPositionRectangle(sf::Vector2f _vectorpos);
	void moveToPos(sf::Vector2f _move);
	const sf::RectangleShape& getRectangle() { return m_missile; };
	bool getMissileLauched() { return m_missileLauched; }
	void setMissileLauched(bool _value);
	float getMissileSpeed() { return m_missileSpeed; }
	void setMissilespeed(float _value);
	float getMissileDestroyed() { return m_isMissileDestroyed; }
	void setMissileDestroyed(float _value);	

	

private:
	sf::RectangleShape m_missile;
	bool m_missileLauched = false;
	float m_missileSpeed = 1250.0f;
	bool m_isMissileDestroyed = false;
};
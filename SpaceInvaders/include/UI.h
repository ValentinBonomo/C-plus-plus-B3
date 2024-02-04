#pragma once
#include <SFML/Graphics.hpp>

class UI
{
public:
	UI(float windowWidth, float windowHeight, sf::RenderWindow& window);

	void setScoreNum(int num);
	int getScoreNum() { return m_scoreNum; }
	sf::Text& getScoreText();
	void updateScoreText();
	sf::Text& getEndText();
	void updateEndText();
	sf::Text& getEndCongratsText();
	sf::FloatRect getGlobalBoundPlayText() { return m_playText.getGlobalBounds(); };
	void setPlayTextColor(sf::Color color) { m_playText.setFillColor(color); };
	sf::FloatRect getGlobalBoundQuitText() { return m_quitText.getGlobalBounds(); };
	void setQuitTextColor(sf::Color color) { m_quitText.setFillColor(color); };
	sf::Text getPlayText() { return m_playText; };
	sf::Text getQuitText() { return m_quitText; };
	sf::Text getTitleText() { return m_titleText; };


private:
	sf::Font font;
	sf::Text scoreText;
	sf::Text endText;
	sf::Text endCongratsText;
	sf::Text endDeathText;
	int m_scoreNum=0;
	sf::Text m_titleText;
	sf::Text m_playText;
	sf::Text m_quitText;
	float m_windowWidth;
	float m_windowHeight;
};
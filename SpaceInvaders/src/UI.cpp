#include "UI.h"
#include <iostream>
#include <SFML/Graphics.hpp>

// Constructeur de l'interface utilisateur (UI), initialise les éléments de l'interface.
UI::UI(float windowWidth, float windowHeight, sf::RenderWindow& window)
{
    m_windowWidth = windowWidth;
    m_windowHeight = windowHeight;
    m_scoreNum = 0;
    if (!font.loadFromFile("FontSFML\\Exo-Regular.ttf"))
    {
        std::cerr << "error loading police for text !" << std::endl;
    }

    // Score Text
    scoreText.setFont(font);
    scoreText.setCharacterSize(24);
    scoreText.setFillColor(sf::Color::White);
    updateScoreText();

    // End Text
    endText.setFont(font);
    endText.setCharacterSize(48);
    endText.setFillColor(sf::Color::Green);
    endText.setString("Congrats you finish my game !");
    updateEndText();

    // End Congrats Text
    endCongratsText.setFont(font);
    endCongratsText.setCharacterSize(48);
    endCongratsText.setFillColor(sf::Color::Green);
    endCongratsText.setString("You died ! Try again to improve your score !!");
    endCongratsText.setPosition((m_windowWidth - endCongratsText.getLocalBounds().width) / 2, m_windowHeight * 0.35f - 50.f);

    // Title Text
    m_titleText.setFont(font);
    m_titleText.setCharacterSize(60);
    m_titleText.setFillColor(sf::Color::White);
    m_titleText.setStyle(sf::Text::Bold);
    m_titleText.setString("Space Invaders");
    m_titleText.setPosition((window.getSize().x - m_titleText.getLocalBounds().width) / 2, 150);

    // Play Text
    m_playText.setFont(font);
    m_playText.setCharacterSize(40);
    m_playText.setFillColor(sf::Color::White);
    m_playText.setString("Play");
    m_playText.setPosition((window.getSize().x - m_playText.getLocalBounds().width) / 2, 450);

    // Quit Text
    m_quitText.setFont(font);
    m_quitText.setCharacterSize(40);
    m_quitText.setFillColor(sf::Color::White);
    m_quitText.setString("Quitt Game");
    m_quitText.setPosition((window.getSize().x - m_quitText.getLocalBounds().width) / 2, 600);
}

// Met à jour le score affiché.
void UI::setScoreNum(int _value)
{
    m_scoreNum = _value;
    updateScoreText();
}

// Renvoie le texte du score.
sf::Text& UI::getScoreText()
{
    return scoreText;
}

// Met à jour le texte de fin.
void UI::updateScoreText()
{
    scoreText.setString("Score: " + std::to_string(m_scoreNum));
    scoreText.setPosition(m_windowWidth * 0.01f, m_windowHeight * 0.01f);
}

// Renvoie le texte de fin.
sf::Text& UI::getEndText()
{
    return endText;
}

// Met à jour le texte de fin.
void UI::updateEndText()
{
    endText.setString("Score: " + std::to_string(m_scoreNum));
    endText.setPosition((m_windowWidth - endText.getLocalBounds().width) / 2, m_windowHeight * 0.5f);
}

// Renvoie le texte de félicitations de fin.
sf::Text& UI::getEndCongratsText()
{
    return endCongratsText;
}

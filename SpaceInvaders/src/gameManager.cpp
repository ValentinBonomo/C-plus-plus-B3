#include "gameManager.h"
#include <iostream>


// Constructeur du GameManager, initialise les variables.
GameManager::GameManager()
    : m_isDeathPlayer(false),
    m_direction(-50),
    m_Speed(15.0f),
    m_nbrEnemy(5),
    m_moveDownAxisY(30.f),
    m_speedMovementEnemy(1.f),
    m_isMainMenu(true),
    m_reductionFireratePlayer(.05f),
    m_isPlayButtonPressed(false),
    m_isQuittButtonPressed(false)
{
}

// Fonction principale pour exécuter le jeu.
void GameManager::run()
{
    // Initialisation de la fenêtre de rendu et des paramètres du jeu.
    sf::RenderWindow window(sf::VideoMode::getDesktopMode(), "Simple 2D Game"/*, sf::Style::Fullscreen*/);
    sf::Vector2u windowSize = window.getSize();
    float windowWidth = static_cast<float>(windowSize.x);
    float windowHeight = static_cast<float>(windowSize.y);
    m_player.setPostionAndScale(windowWidth, windowHeight);

    sf::Clock timer;
       
    // Initialisation des listes d'ennemis et de missiles.
    m_enemyList = initEnemyList();
    sf::Clock missileTimer;
    sf::Clock moveEnemy;

    // Initialisation de l'interface utilisateur.
    UI ui(windowWidth,windowHeight,window);

    // Boucle principale du jeu.
    while (window.isOpen())
    {
        // Gestion des entrées et des événements.
        handleInput(window, m_Speed, missileTimer,m_missiles,ui);

        // Logique de jeu en fonction de l'état du jeu.(Menu, Jeu et Mort)
        if (m_isMainMenu)
        {
            // Affichage de l'état actuel du jeu.
            drawingEverything(window, m_enemyList, m_missiles, ui, m_isDeathPlayer);

        }
        else if (!m_enemyList.empty() && !m_isDeathPlayer && !m_isMainMenu)
        {
            // Logique de jeu principale (déplacement, collisions, etc.)
            sf::Time elapsed = timer.restart();
            sf::Time missileElapsed = missileTimer.getElapsedTime();

            /*func*/

            // Vérifie les missiles à détruire + collision avec ennemis
            std::vector<int> missilesToErase;
            std::vector<int> enemyToErase;
            
            /*func*/
            checkCollision(m_missiles, missilesToErase, enemyToErase, m_enemyList,elapsed,ui);

            sf::Time moveEnemyTimer = moveEnemy.getElapsedTime();
            bool isMovingDown = false;

            if (moveEnemyTimer.asSeconds() >= m_speedMovementEnemy)
            {
                moveEnemyPos(m_enemyList, isMovingDown, windowWidth);
                moveEnemy.restart();
            }
            // Affichage de l'état actuel du jeu.
            drawingEverything(window, m_enemyList, m_missiles, ui, m_isDeathPlayer);
        }
        // Nettoyage des ennemis et affichage du message de fin en cas de mort du joueur.
        else if (m_isDeathPlayer && !m_isMainMenu)
        {
            removeEnemyIsDeath(m_enemyList);
            drawingEverything(window, m_enemyList, m_missiles, ui, m_isDeathPlayer);
        }
        // Augmentation de la difficulté et réinitialisation des ennemis.
        else if (m_enemyList.empty())
        {
            m_speedMovementEnemy -= 0.025f;
            if (m_nbrEnemy<20)
            {
                m_nbrEnemy++;
            }
            m_enemyList = initEnemyList();
            if (m_player.getFirerate()>0.25)
            {
                m_player.makeFirerateSmaller(m_reductionFireratePlayer);
            }
        }
    }

    // Libération de la mémoire allouée pour les ennemis.
    for (auto enemy : m_enemyList)
    {
        delete enemy;
    }
    // Libération de la mémoire allouée pour les missiles.
    for (auto missile : m_missiles)
    {
        delete missile;
    }
}

// Initialisation de la liste d'ennemis.
std::vector<Enemy*> GameManager::initEnemyList()
{
    std::vector<Enemy*> enemies;
    float addAxisX = 100;
    float addAxisX2 = 100;

    for (int i = 0; i <= (m_nbrEnemy-1); i++)
    {
        if (i<=9)
        {
            addAxisX += 100.f;
            Enemy* enemy = new Enemy(addAxisX, 0.f);
            enemies.push_back(enemy);
        }
        else if (i >= 10 && i<=20)
        {
            addAxisX2 += 100.f;
            Enemy* enemy = new Enemy(addAxisX2, 100.f);
            enemies.push_back(enemy);
        }
    }
    return enemies;
}

// Vérifie les collisions entre missiles et ennemis.
void GameManager::checkCollision(std::vector<Missile*>& missileList, std::vector<int>& missilesToErase, std::vector<int>& enemyToErase, std::vector<Enemy*>& enemyList, sf::Time elapsed, UI& ui)
{
    for (int i = 0; i < missileList.size(); i++)
    {
        Missile* missile = missileList[i];
        missile->moveToPos(sf::Vector2f(0.f, -missile->getMissileSpeed() * elapsed.asSeconds()));

        for (int y = 0; y < enemyList.size(); y++)
        {
            Enemy* enemy = enemyList[y];

            sf::FloatRect missileBox = missile->getRectangle().getGlobalBounds();
            sf::FloatRect otherBox = enemy->getSprite().getGlobalBounds();
            if (missileBox.intersects(otherBox))
            {
                // Score incrementation.
                ui.setScoreNum(ui.getScoreNum() + 1);

                // Prépare la suppression des ennemis et missiles qui se sont entrechoqués.
                missilesToErase.push_back(i);
                enemyToErase.push_back(y);
            }
            if (m_player.getSprite().getGlobalBounds().intersects(otherBox))
            {
                m_isDeathPlayer = true;
            }
        }

        // Vérifie si le missile sort du cadre
        if (missile->getRectangle().getPosition().y + missile->getRectangle().getSize().y < 0)
        {
            missilesToErase.push_back(i);
        }
    }

    // Supprime les missiles et les ennemis concernés.
    for (int missileIndex : missilesToErase)
    {
        delete missileList[missileIndex];
        missileList.erase(missileList.begin() + missileIndex);
    }
    for (int enemyIndex : enemyToErase)
    {
        delete enemyList[enemyIndex];
        enemyList.erase(enemyList.begin() + enemyIndex);
    }
}

// Affiche les éléments du jeu en fonction de l'état actuel.
void GameManager::drawingEverything(sf::RenderWindow& window, std::vector<Enemy*>& enemyList, std::vector<Missile*>& missiles, UI& ui, bool isDeathPlayer)
{
    if (!isDeathPlayer && !m_isMainMenu)
    {
        window.clear();

        for (auto enemy : enemyList)
        {
            if (!enemy->isEnemyDestroyed())
                window.draw(enemy->getSprite());
        }

        window.draw(m_player.getSprite());

        for (auto missile : missiles)
        {
            window.draw(missile->getRectangle());
        }

        window.draw(ui.getScoreText());

        window.display();
    }
    else if (isDeathPlayer && !m_isMainMenu)
    {
        window.clear();
        ui.updateEndText();
        window.draw(ui.getEndText());
        window.draw(ui.getEndCongratsText());
        window.display();
    }
    else if (m_isMainMenu)
    {
        window.clear();
        window.draw(ui.getTitleText());
        window.draw(ui.getPlayText());
        window.draw(ui.getQuitText());
        window.display();
    }
}

// Supprime les ennemis en cas de mort du joueur.
void GameManager::removeEnemyIsDeath(std::vector<Enemy*>& enemyList)
{
    if (!enemyList.empty())
    {
        for (size_t i = 0; i < enemyList.size(); i++)
        {
            delete enemyList[i];
            enemyList.erase(enemyList.begin() + i);
        }
    }
}

// Déplace les ennemis en fonction de la direction et du déplacement vertical.
void GameManager::moveEnemyPos(std::vector<Enemy*>& enemyList, bool isMovingDown, float windowWidth)
{
    for (int i = 0; i < enemyList.size(); i++)
    {
        Enemy* enemy = enemyList[i];

        if (enemy->getSpritePositionY() >= 900)
        {
            m_isDeathPlayer = true;
            break;
        }
        if (m_direction < 0) // to left
        {
            if ((enemy->getSpritePositionX() + m_direction) < 0 )
            {
                isMovingDown = true;
                m_direction *= -1;
                if (m_speedMovementEnemy > 0.25)
                {
                    m_speedMovementEnemy -= 0.05f;
                }
                break;
            }
            else
            {
                isMovingDown = false;
            }
        }
        else if (m_direction > 0) // to right
        {
            if (enemy->getSpritePositionX() + enemy->getSpriteColliderWidth() + m_direction > windowWidth)
            {
                isMovingDown = true;
                m_direction *= -1;
                if (m_speedMovementEnemy > 0.25)
                {
                    m_speedMovementEnemy -= 0.05f;
                }
                break;

            }
            else
            {
                isMovingDown = false;
            }
        }
    }

    if (isMovingDown)
    {
        for (int y = 0; y < enemyList.size(); y++)
        {
            enemyList[y]->addPositonManual(0.f, m_moveDownAxisY);
        }
        if (m_moveDownAxisY <100)
        {
            m_moveDownAxisY += 10.f;
        }
    }
    else
    {
        for (int i = 0; i < enemyList.size(); i++)
        {
            enemyList[i]->addPositonManual(m_direction, 0);
        }
    }
};

// Gestion des input utilisateur.
void GameManager::handleInput(sf::RenderWindow& window, float Speed, sf::Clock& missileTimer, std::vector<Missile*>& missiles, UI& ui)
{
    sf::Event event;
    while (window.pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
        {
            window.close();
        }
        else if (event.type == sf::Event::KeyPressed)
        {
            if (event.key.code == sf::Keyboard::Escape)
            {
                window.close();
            }
            if (!m_isDeathPlayer)
            {
                if (event.key.code == sf::Keyboard::Q)
                {
                    m_player.moveLeft(Speed);
                }
                else if (event.key.code == sf::Keyboard::D)
                {
                    m_player.moveRight(Speed, window.getSize().x);
                }
                else if (event.key.code == sf::Keyboard::Space)
                {
                    if (missileTimer.getElapsedTime().asSeconds() >= m_player.getFirerate())
                    {
                        startMissileAndMoveIt(missiles);
                        missileTimer.restart();
                    }
                }
            }
        }
        else if (event.type == sf::Event::MouseMoved && m_isMainMenu)
        {
            // Vérifie si la souris est sur le texte Play
            if (ui.getGlobalBoundPlayText().contains(sf::Vector2f(event.mouseMove.x, event.mouseMove.y)))
            {
                ui.setPlayTextColor(sf::Color::Red);
                ui.setQuitTextColor(sf::Color::White);
                m_isPlayButtonPressed = true;
                m_isQuittButtonPressed = false;
            }
            // Vérifie si la souris est sur le texte Quit Game
            else if (ui.getGlobalBoundQuitText().contains(sf::Vector2f(event.mouseMove.x, event.mouseMove.y)))
            {
                ui.setPlayTextColor(sf::Color::White);
                ui.setQuitTextColor(sf::Color::Blue);
                m_isQuittButtonPressed = true;
                m_isPlayButtonPressed = false;
            }
            else
            {
                ui.setPlayTextColor(sf::Color::White);
                ui.setQuitTextColor(sf::Color::White);
                m_isPlayButtonPressed = false;
                m_isQuittButtonPressed = false;
            }
        }
        else if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
        {
            if (m_isPlayButtonPressed)
            {
                m_isMainMenu = false;
            }
            else if (m_isQuittButtonPressed)
            {
                window.close();

            }

        }
    }
}

// Crée un nouveau missile et le déplace.
void GameManager::startMissileAndMoveIt(std::vector<Missile*>& missileList)
{
    Missile* newMissile = new Missile();
    newMissile->setPositionRectangle(sf::Vector2f(m_player.getSprite().getPosition().x + m_player.getSprite().getGlobalBounds().width / 2.f - newMissile->getRectangle().getSize().x / 2.f, m_player.getSprite().getPosition().y));
    missileList.push_back(newMissile);
};


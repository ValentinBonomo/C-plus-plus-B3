#pragma once
#include <SFML/Graphics.hpp>
#include "missile.h"
#include "enemy.h"
#include "UI.h"
#include "player.h"


class GameManager
{
public:
    GameManager();
    void run();
    std::vector<Enemy*> initEnemyList();
    void checkCollision(std::vector<Missile*>& missileList, std::vector<int>& missilesToErase, std::vector<int>& enemyToErase, std::vector<Enemy*>& enemyList, sf::Time elapsed, UI& ui);
    void drawingEverything(sf::RenderWindow& window, std::vector<Enemy*>& enemyList, std::vector<Missile*>& missiles, UI& ui, bool isDeathPlayer);
    void removeEnemyIsDeath(std::vector<Enemy*>& enemyList);
    void moveEnemyPos(std::vector<Enemy*>& enemyList, bool isMovingDown, float windowWidth);
    void handleInput(sf::RenderWindow& window, float Speed, sf::Clock& missileTimer, std::vector<Missile*>& missiles,UI& ui);
    void startMissileAndMoveIt(std::vector<Missile*>& missileList);


private:
    Player m_player;
    bool m_isDeathPlayer;
    float m_direction;
    float m_Speed;
    int m_nbrEnemy;
    float m_moveDownAxisY;
    float m_speedMovementEnemy;
    std::vector<Enemy*> m_enemyList;
    std::vector<Missile*> m_missiles;
    bool m_isMainMenu;
    float m_reductionFireratePlayer;
    bool m_isPlayButtonPressed;
    bool m_isQuittButtonPressed;
};

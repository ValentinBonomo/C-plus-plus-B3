#include <iostream>
#include "SFML/Graphics.hpp"
#include "player.h"
#include "enemy.h"
#include "missile.h"
#include "UI.h"
#include "gameManager.h"


int main()
{
    GameManager gameManager;
    gameManager.run(); //fonction de la classe gamemanager lançant le jeu

    return 0;
}
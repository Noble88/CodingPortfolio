#ifndef PLAYER_H
#define PLAYER_H

#include <iostream>
using namespace std;


class Player{
  public: 
    Player();
    ~Player();

    void SpawnPlayer();
    void MovePlayerRandomly();
      std::pair<int, int> GetNextPosition(char direction);
    bool CollisionDetection(std::pair<int,int> destination, char sym);

    void MushroomLogic(std::pair<int,int> location);
    void CoinLogic(std::pair<int,int> location);
    void HurtPlayer();
    void LoseLife();
    bool EnemyLogic(std::pair<int,int> location, int killPrecent, int damage);
    bool BossLogic(std::pair<int,int> location);
    void WarpPipeLogic();
    
  
    static std::pair<int, int> playerPos;
    static int coins;
    static string direction;
    static int killStreak;
    static int powerLevel;
    static int lives;
};

#endif
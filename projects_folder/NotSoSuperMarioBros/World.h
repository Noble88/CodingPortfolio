#ifndef WORLD_H
#define WORLD_H

#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib> // For atoi function, rand() and srand() functions
#include <sstream>
#include <random>




using namespace std;

class World{
  public:
    World();
    ~World();
    void DeclareWorldValues();

    void GenerateAllLevels();
    char GetRandomGameIcon();
    static int GetRandomNumber(int max, int min);
    static void ReplaceCharOnCurLevel(int y, int x, char sym);
    static void PrintCurrentLevel();

    static int currentLevel;
    int precentProbabilityOfItems[5] = {0,0,0,0,0};
    static int gridDimension;
    static int numOfLevels;
    static char*** WorldLayout;
    static bool isGameOver;

    static char recentCollision;
};

#endif
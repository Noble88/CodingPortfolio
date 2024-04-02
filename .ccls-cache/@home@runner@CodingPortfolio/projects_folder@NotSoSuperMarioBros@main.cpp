#include "World.h"
#include "Player.h"

#include <chrono>   // For std::chrono::seconds
#include <thread>   // For std::this_thread::sleep_for

char GetUserInput() {
  string userInput;
  std::cin >> userInput;
  return userInput[0];
}

int main() {  
  cout << "START PROGRAM"<<endl;
  World world;
  Player player;
  
  world.PrintCurrentLevel();

  int tempCount=0;
  while(!world.isGameOver){
    player.MovePlayerRandomly();
    world.PrintCurrentLevel();
    std::this_thread::sleep_for(std::chrono::milliseconds(2));
    /*
    switch(GetUserInput()){
      case 'q': world.isGameOver=true;
    }
  */
    tempCount++;
    if(tempCount==10000){world.isGameOver=true;}
  }
  return 0;
}
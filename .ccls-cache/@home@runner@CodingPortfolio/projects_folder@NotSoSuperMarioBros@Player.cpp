#include "Player.h"
#include "World.h"

int Player::lives;
int Player::coins;
int Player::killStreak;
int Player::powerLevel;
string Player::direction;

std::pair<int, int> Player::playerPos;

Player::Player(){
  coins=0;
  killStreak=0;
  powerLevel=0;
  SpawnPlayer();
}
Player::~Player(){}

void Player::SpawnPlayer(){ //Make stuff static just to do this seems bad, TALK TO TEACHER!
  playerPos.first= World::GetRandomNumber(0,World::gridDimension-1); //[0] = y
  playerPos.second= World::GetRandomNumber(0,World::gridDimension-1); //[0] = x

  //Need to do collision 
  char charAtDesitnation = World::WorldLayout[World::currentLevel][playerPos.first][playerPos.second];
  CollisionDetection(playerPos, charAtDesitnation);
  World::recentCollision=charAtDesitnation;

  //can't overide
  if(charAtDesitnation == 'x' || charAtDesitnation == 'm' || charAtDesitnation == 'c' || charAtDesitnation == 'w'){
    World::WorldLayout[World::currentLevel][playerPos.first][playerPos.second] = 'x'; //remove player sym
    World::WorldLayout[World::currentLevel][playerPos.first][playerPos.second] = 'H'; //move to new location
  }
}

pair<int, int> Player::GetNextPosition(char direction) {
    int newY = playerPos.first;
    int newX = playerPos.second;
    switch (direction) {
        case 'U':
            --newY;
            break;
        case 'D':
            ++newY;
            break;
        case 'L':
            --newX;
            break;
        case 'R':
            ++newX;
            break;
    }
    return std::make_pair(newY, newX);
}

void Player::MovePlayerRandomly(){
  std::pair<int,int> destination;

  //get Random direction Destination
  switch(World::GetRandomNumber(0,3)){
    case 0: destination = GetNextPosition('U'); Player::direction="UP"; break;
    case 1: destination = GetNextPosition('D'); Player::direction="DOWN"; break;
    case 2: destination = GetNextPosition('L'); Player::direction="LEFT"; break;
    case 3: destination = GetNextPosition('R'); Player::direction="RIGHT"; break;
  }


  if(destination.first >= 0 && destination.first < World::gridDimension &&
    destination.second >= 0 && destination.second < World::gridDimension){
    
    char charAtDesitnation = World::WorldLayout[World::currentLevel][destination.first][destination.second];
    if(CollisionDetection(destination, charAtDesitnation) && World::recentCollision!='w' && World::recentCollision!='b'){

    World::WorldLayout[World::currentLevel][playerPos.first][playerPos.second] = 'x'; //remove player sym
    World::WorldLayout[World::currentLevel][destination.first][destination.second] = 'H'; //move to new location

    playerPos = destination; //Update Player pos
    }

  }
  else{
    World::recentCollision=' ';
  }
}

//Will return false if Can not move from distination
bool Player::CollisionDetection(std::pair<int,int> destination, char sym){
  World::recentCollision = sym;
  switch (sym){
    case 'x': return true;
    case 'm': MushroomLogic(destination); return true;
    case 'c': CoinLogic(destination); return true;
    case 'g': return EnemyLogic(destination, 80, 1);
    case 'k': return EnemyLogic(destination, 65, 1);
    
    case 'w': WarpPipeLogic(); return true;
    case 'b': return BossLogic(destination);

    default: cout<<"UNKNOWN CHARACTER DETECTED: ["<<sym<<"]"<<endl; return false;
  }
}

void Player::CoinLogic(std::pair<int,int> location){
  coins++;
  if(coins==20){ lives++; coins=0;}
  World::ReplaceCharOnCurLevel(location.first,location.second,'x');

  string coinPhrase="";
  switch(World::GetRandomNumber(1,2)){
    case 1: coinPhrase="YIPPEE";
    case 2: coinPhrase="I LOVE-A SHINY COINS";
  }
  cout <<coinPhrase<<endl;
}
void Player::MushroomLogic(std::pair<int,int> location){
  if(powerLevel!=2){ powerLevel++;}
  World::ReplaceCharOnCurLevel(location.first,location.second,'x');
  
  string mushroomPhrase="";
  switch(World::GetRandomNumber(1,2)){
    case 1: mushroomPhrase="MUSHROOM TIME!!!";
    case 2: mushroomPhrase="MUSHROOM POWERING UP!";
  }
  cout <<mushroomPhrase<<endl;
}
void Player::HurtPlayer(){
  powerLevel--;
  if(powerLevel==-1){ LoseLife(); powerLevel=0;}

  string hurtPhrase="";
  switch(World::GetRandomNumber(0,2)){
    case 0: hurtPhrase="OUCH";
    case 1: hurtPhrase="OOF";
    case 2: hurtPhrase="MA MA MIA";
  }
  cout <<hurtPhrase<<endl;
}
void Player::LoseLife(){
  lives--; killStreak=0;
  if(lives==-1){
    cout<<"GAME OVER"<<endl; //DO SOMETHING MORE!!!
    World::isGameOver=true;
  }
}
bool Player::EnemyLogic(std::pair<int,int> location, int killPrecent, int damage){
  if(World::GetRandomNumber(1,100)<=killPrecent){ 
    World::ReplaceCharOnCurLevel(location.first,location.second,'x');
    if(World::recentCollision!='b'){killStreak++;} //Bowswer doesn't count as normal enemy!
    cout <<"STOMPY TIME";
    return true; //true means enemy is killed
  }
  else{
    for(int i=0; i<damage; ++i){ HurtPlayer(); }
    return false; 
  }
}
bool Player::BossLogic(std::pair<int,int> location){
  //The boss will use a while loop to keep the player at location until it kills the boss
  cout <<"BWAH HA HA, TIME TO DIE MARIO!" << endl;
  if(World::currentLevel+1 == World::numOfLevels){ //LAST LEVEL CONDITION
    while(!EnemyLogic(location, 50, 2) && !World::isGameOver);//whil loosing and not game over
    if(World::isGameOver==false){
      cout<<"YOU WIN"<<endl;
      World::isGameOver=true;
    }
  }
  else{
    if(EnemyLogic(location, 50, 2)){
      World::PrintCurrentLevel();
      World::currentLevel++;
      CollisionDetection(location, World::WorldLayout[World::currentLevel][location.first][location.second]);
      World::WorldLayout[World::currentLevel][location.first][location.second] = 'H';
      return true;
    }
  }
  return false;
}
void Player::WarpPipeLogic(){
  cout <<"BLOOP BLOOP BLOOP"<<endl;
  World::PrintCurrentLevel();
  World::currentLevel++;
  SpawnPlayer();
}

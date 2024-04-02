#include "World.h"
#include "Player.h"

int World::currentLevel;
int World::gridDimension;
int World::numOfLevels;
char*** World::WorldLayout;
bool World::isGameOver;
char World::recentCollision;

World::World() {
  currentLevel=0;
  DeclareWorldValues();

  WorldLayout = new char**[numOfLevels]; //declaring WorldLayout bounderies
  for (int k = 0; k < numOfLevels; ++k) {
      WorldLayout[k] = new char*[gridDimension];
      for (int i = 0; i < gridDimension; ++i) {
          WorldLayout[k][i] = new char[gridDimension];
      }
  }
  GenerateAllLevels();
}

World::~World() {
  // Deallocate memory for WorldLayout
  for (int k = 0; k < numOfLevels; ++k) {
      for (int i = 0; i < gridDimension; ++i) {
          delete[] WorldLayout[k][i];
      }
      delete[] WorldLayout[k];
  }
  delete[] WorldLayout;
}


void World::GenerateAllLevels(){
  // Find an empty slot in WorldLayout and add the generated level
  for(int levelIndex=0; levelIndex<numOfLevels; ++levelIndex){
    if (levelIndex < numOfLevels) {
      for (int i = 0; i < gridDimension; ++i) {
        for (int j = 0; j < gridDimension; ++j) {
          WorldLayout[levelIndex][i][j] = GetRandomGameIcon();
          
          //Debugging every entry
          /*
          cout<<"Assigning Var: ["<<levelIndex<<"]["<<i<<"]["<<j<<"]"<<endl;
          char randomChar = GetRandomGameIcon();
          if(randomChar=='z'){
            i=gridDimension; j=gridDimension;gridDimension=numOfLevels;
          }
          else{
            WorldLayout[levelIndex][i][j] = randomChar;
          }
          */
        }
      }
      //spawn warp pipe
      if( levelIndex!=(numOfLevels-1) ){//If isn't last level
        WorldLayout[levelIndex][GetRandomNumber(0,gridDimension-1)][GetRandomNumber(0,gridDimension-1)] = 'w';
      }
      //spawn boss
      WorldLayout[levelIndex][GetRandomNumber(0,gridDimension-1)][GetRandomNumber(0,gridDimension-1)]='b';
    }
  }
}

int World::GetRandomNumber(int min, int max) {
  static std::random_device rd;
  static std::mt19937 gen(rd());
  std::uniform_int_distribution<int> distrib(min, max); // Correct range without adjustments
  int randomNumber = distrib(gen);
  if(randomNumber>max || randomNumber<min){
    cout<<"BIG FUCKING PROBLEM"<<endl;
  }
  /*)
  cout << "Max: "<<max<<" | Min: "<<min<<" | generated: "<<randomNumber<<endl;
  return randomNumber;
  */
  return distrib(gen);
}

char World::GetRandomGameIcon(){
  int ranNum = GetRandomNumber(1,100); //Random Generation from 1 to 100
  for(int i=0; i<5; ++i){
    //cout<<"CALCUALTION ("<<i<<"): ranNum = ["<<ranNum<<"] & precentProbabilityOfItems[i] = "<<precentProbabilityOfItems[i]<<" Equations Outcome: ["<< ranNum-precentProbabilityOfItems[i]<<"]  & Other condition: "<< to_string(precentProbabilityOfItems[i]!=0)<<endl;
    
    if( (ranNum-precentProbabilityOfItems[i]) <=0 && precentProbabilityOfItems[i]!=0){
      switch(i){
        case 0: return 'c'; 
        case 1: return 'x'; 
        case 2: return 'g'; 
        case 3: return 'k'; 
        case 4: return 'm'; 
      }
    }
    else{
      ranNum-=precentProbabilityOfItems[i];
    }
  }
  cout <<"ERROR IN GET RANDOM GAME ICON METHOD, EQUATIONS FUCKED"<<endl;
  return 'z';
}

void World::DeclareWorldValues() {
    
  string gameSettingsFileLocation = "GameSettings.txt";
  ifstream file(gameSettingsFileLocation); // Begin to read file

  if (!file.is_open()) {
    std::cerr << "Error opening file!" << std::endl;
  }

  int currentIndex = 0;

  std::string line;
  int currentLine = 0;

  while (std::getline(file, line) && currentLine < 8) {
    ++currentLine;
    //Readers Note: the whole "size_t pos = line.find(": ");" and "std::string substring = line.substr(pos + 2);" is to bypass the way I formatted the GameSettings.txt file.

    if (currentLine >= 4) {//Assign the perecent values.
      // Find the position of the delimiter ": "
      size_t pos = line.find(": ");
      if (pos != std::string::npos) {
        std::string substring = line.substr(pos + 2);

        //cout << "DATA VALUE TEST: "<< substring.c_str()<< "Current Line = "<<currentLine<< endl;
        precentProbabilityOfItems[(currentLine-4)] = std::atoi(substring.c_str());
      } else {
        std::cerr << "Delimiter not found in line " << currentLine << std::endl;
      }
    } 
    else if (currentLine == 3) { //Assign the Dimentions to LevelTileGrid
      size_t pos = line.find(": ");
      std::string substring = line.substr(pos + 2);
      Player::lives = std::atoi(substring.c_str());
      //cout << "stored num of levels: ["<<numOfLevels<<"]"<<endl;
    }
    else if (currentLine == 2) { //Assign the Dimentions to LevelTileGrid
      size_t pos = line.find(": ");
      std::string substring = line.substr(pos + 2);
      cout <<"GRID DIMENSION: ["<<substring.c_str()<<"]"<<endl;
      gridDimension = std::atoi(substring.c_str());
    }
    else if (currentLine == 1) { //Assign the Dimentions to LevelTileGrid
      size_t pos = line.find(": ");
      std::string substring = line.substr(pos + 2);
      numOfLevels = std::atoi(substring.c_str());
      //cout << "stored num of levels: ["<<numOfLevels<<"]"<<endl;
    }
  }

  file.close(); // Close the file
  //cout << "File closed." << endl;
}

void World::ReplaceCharOnCurLevel(int y, int x, char sym){
  WorldLayout[currentLevel][y][x]=sym;
}



void World::PrintCurrentLevel() {
  if(!(recentCollision==' ')){//Ignors moves that don't actually do anything 
    if (currentLevel >= 0 && currentLevel < numOfLevels) {
        // Open the file for appending
        std::ofstream outFile("GameLog.txt", std::ios::app);
        if (!outFile.is_open()) {
            std::cerr << "Unable to open file GameLog.txt" << std::endl;
            return;
        }

        //Debug Header Message
        outFile << 
          "Level " << (currentLevel+1) << "/"<<numOfLevels<<" | "<<
          "Lives: "<<Player::lives<< " | "<<
          "coins: "<<Player::coins<<" | "<<
          "killStreak: "<<Player::killStreak<<" | "<<
          "powerLevel: "<<Player::powerLevel<<" | \n"<<
          "recentCollision: "<<recentCollision<<" | "<<
          "isGameOver: "<<World::isGameOver<<" | "<<
          "Player Location: ["<<(Player::playerPos.first+1)<<","<<(Player::playerPos.second+1) <<"] | " <<
          std::endl;
        for (int i = 0; i < gridDimension; ++i) {
            for (int j = 0; j < gridDimension; ++j) {
                //std::cout << WorldLayout[currentLevel][i][j] << " ";
                outFile << WorldLayout[currentLevel][i][j] << " ";
            }
            //std::cout << std::endl;
            outFile << endl;
        }
      outFile << "\n";
        // Get the latest line from the terminal and append it to the bottom of the array and write it to the file
      /*
        std::string latestLine;
        std::getline(std::cin, latestLine);
        if (!latestLine.empty()) {
            std::istringstream iss(latestLine);
            std::string token;
            int row = gridDimension - 1; // Append to the bottom row
            int col = 0;
            while (iss >> token && col < gridDimension) {
                WorldLayout[currentLevel][row][col] = token[0]; // Assuming each token is a single character
                col++;
            }

            // Write the latest line to the file
            outFile << latestLine << std::endl;
        }
      */
        // Close the file
        outFile.close();
    } else {
        std::cout << "Invalid level index." << std::endl;
    }
  }
}




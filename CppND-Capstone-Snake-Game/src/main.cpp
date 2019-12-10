#include <iostream>
#include "controller.h"
#include "game.h"
#include "renderer.h"


/**
 Main Function of the Game
 */

int main() {
  constexpr std::size_t kFramesPerSecond{60};
  constexpr std::size_t kMsPerFrame{1000 / kFramesPerSecond};
  constexpr std::size_t kScreenWidth{640};
  constexpr std::size_t kScreenHeight{640};
  constexpr std::size_t kGridWidth{32};
  constexpr std::size_t kGridHeight{32};

  //Renderer renderer(kScreenWidth, kScreenHeight, kGridWidth, kGridHeight);
 
  Game game(kScreenWidth, kScreenHeight, kGridWidth, kGridHeight);
    
  //Spawn Splash Screen For Game Start
  //Game Will begin With Small Snake and Multiple Foods
  //BckGrnd Will Keep Flashing With Different Colors When Game is in Progress.
  //BckGrnd Will Go Red When game Finishes and Green When Game Begins
  //Have to See to Passing the Window and Other Param to the BackGround Thread now.
  game.Initiate(kMsPerFrame);
    
  //Spawn Splash Screen For Game End
  
  std::cout << "Game has terminated successfully!\n";
  std::cout << "Score: " << game.GetScore() << "\n";
  std::cout << "Size: " << game.GetSize() << "\n";
  return 0;
}

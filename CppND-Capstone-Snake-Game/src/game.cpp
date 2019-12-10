#include "game.h"
#include <iostream>
//#include "SDL2/SDL.h"
#include "SDL.h"
#include <thread>
#include <chrono>



SDL_Color Game::bcolor = blue;

//Game Constructor
//Initializes Snake Object
//Initializes Renderer and Controller as well As part of Creation
Game::Game(const std::size_t screen_width,
           const std::size_t screen_height,
           std::size_t grid_width, std::size_t grid_height)
    : snake(grid_width, grid_height),
      renderer(screen_width, screen_height,grid_width, grid_height),
      engine(dev()),
      random_w(0, static_cast<int>(grid_width-1)),
      random_h(0, static_cast<int>(grid_height-1)) {
  PlaceFood();
}

Game::~Game()
{
    int ind = 0xFF;
    // set up thread barrier before this object is destroyed
    _msgq.send(std::move(ind));
   
    b_thread.join();
    
}

//Update Game BckGrnd Color Periodically
void Game::UpdateBckgrnd()
{
    int cnt = 0;
    while (snake.alive)
    {
        // sleep for 500msec for every iteration to reduce CPU usage
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
        
        //When Food is Eaten
        int food_eaten = _msgq.receive();
        PlaceFood();
        cnt++;
        if(cnt == 1)
            Game::bcolor = blue;
        else if (cnt == 2)
            Game::bcolor = red;
        else if (cnt == 3)
            Game::bcolor = grn;
        else if (cnt == 4)
            Game::bcolor = blk;
        else
            cnt = 0;
        
        //Update BckGrnd Color Here
        std::cout << "UpdateBckGrnd: Updating Color Here " << std::endl;

    }
}

void Game::Initiate(std::size_t ltarget_frame_duration)
{
    target_frame_duration = ltarget_frame_duration;
    
    // launch vehicle queue processing in a thread
    //SDL Can be only be Rendered and User Input COntrolled from Main Thread
    //Have to Use Backgrnd Thread for processing User Inputs Only
    //threads.emplace_back(std::thread(&Game::Run, this ));
    b_thread = (std::thread(&Game::UpdateBckgrnd, this ));
    
    //Run The Rendering on SDL
    Run();
}

void Game::Run() {
  Uint32 title_timestamp = SDL_GetTicks();
  Uint32 frame_start;
  Uint32 frame_end;
  Uint32 frame_duration;
  int frame_count = 0;
  bool running = true;

   //renderer.Start();
    
  while (running) {
    frame_start = SDL_GetTicks();
    std::unique_lock<std::mutex> lck(gmutex);
      lck.unlock();
    // Input, Update, Render - the main game loop.
    controller.HandleInput(running, snake);
      
    Update();
      
      lck.lock();
    renderer.Render(snake, food);
      lck.unlock();
    frame_end = SDL_GetTicks();

    // Keep track of how long each loop through the input/update/render cycle
    // takes.
    frame_count++;
    frame_duration = frame_end - frame_start;

    // After every second, update the window title.
    if (frame_end - title_timestamp >= 1000) {
      renderer.UpdateWindowTitle(score, frame_count);
      frame_count = 0;
      title_timestamp = frame_end;
    }

    // If the time for this frame is too small (i.e. frame_duration is
    // smaller than the target ms_per_frame), delay the loop to
    // achieve the correct frame rate.
    if (frame_duration < target_frame_duration) {
      SDL_Delay(target_frame_duration - frame_duration);
    }
      //Update Running With Snake.Alive to Exit When Snake Dies.
      running = running && snake.alive;
      if(!snake.alive)
      {
          SDL_Delay(5000);
      }
  }//WHile Loop
    snake.alive = false;
    //renderer.End();
}

void Game::PlaceFood() {
    
  std::lock_guard<std::mutex> lock(gmutex);
  int x, y;
  while (true) {
    x = random_w(engine);
    y = random_h(engine);
    // Check that the location is not occupied by a snake item before placing
    // food.
    if (!snake.SnakeCell(x, y)) {
      food.x = x;
      food.y = y;
        
        std::cout <<"PlaceFood: x:" << food.x << " y:" << food.y << std::endl;
      return;
    }
  }//While Loop
}

void Game::Update() {
  if (!snake.alive) return;

  snake.Update();

  int new_x = static_cast<int>(snake.head_x);
  int new_y = static_cast<int>(snake.head_y);

  // Check if there's food over here
  if (food.x == new_x && food.y == new_y) {
      int ind = 1;
    score++;
    //PlaceFood();
      _msgq.send(std::move(ind));
    // Grow snake and increase speed.
    snake.GrowBody();
    snake.speed += 0.02;
  }
}

int Game::GetScore() const { return score; }
int Game::GetSize() const { return snake.size; }

#include "renderer.h"
#include <iostream>
#include <string>
#include "game.h"
//#include "SDL_image.h"
#include "SDL.h"

Renderer::Renderer(const std::size_t screen_width,
                   const std::size_t screen_height,
                   const std::size_t grid_width, const std::size_t grid_height)
    : screen_width(screen_width),
      screen_height(screen_height),
      grid_width(grid_width),
      grid_height(grid_height) {

  // Initialize SDL
  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    std::cerr << "SDL could not initialize.\n";
    std::cerr << "SDL_Error: " << SDL_GetError() << "\n";
  }
#if 0
            // Image Formats
    int imgFlags = IMG_INIT_PNG;
    if(!(IMG_Init(imgFlags) & imgFlags)){
      std::cerr << "SDL IMG could not initialize.\n";
      std::cerr << "SDL_Error: " << SDL_GetError() << "\n";
    }
#endif        
  // Create Window
  sdl_window = SDL_CreateWindow("Snake Game SS0", SDL_WINDOWPOS_CENTERED,
                                SDL_WINDOWPOS_CENTERED, screen_width,
                                screen_height, SDL_WINDOW_SHOWN);

  if (nullptr == sdl_window) {
    std::cerr << "Window could not be created.\n";
    std::cerr << " SDL_Error: " << SDL_GetError() << "\n";
  }

  // Create renderer
  sdl_renderer = SDL_CreateRenderer(sdl_window, -1, SDL_RENDERER_ACCELERATED|SDL_RENDERER_PRESENTVSYNC);
  if (nullptr == sdl_renderer) {
    std::cerr << "Renderer could not be created.\n";
    std::cerr << "SDL_Error: " << SDL_GetError() << "\n";
  }
}

/**
 Destructor for Renderer Class Which Destroys The Window and
 Clears SDL Layer As well 
 */
Renderer::~Renderer() {
  SDL_DestroyWindow(sdl_window);
  SDL_Quit();
}

void Renderer::Render(Snake const snake, SDL_Point const &food) {
  SDL_Rect block;
    
    // Clear screen
    SDL_SetRenderDrawColor(sdl_renderer,  0x1E, 0x1E, 0x1E, 0xFF);
    SDL_RenderClear(sdl_renderer);
    
    
    //Fill Screen With Color
    SDL_SetRenderDrawColor(sdl_renderer, Game::bcolor.r, Game::bcolor.g, Game::bcolor.b, Game::bcolor.a);
    block.w = screen_width ;
    block.h = screen_height ;
    block.x = 0;
    block.y = 0;
    SDL_RenderFillRect(sdl_renderer, &block);
    
  block.w = screen_width / grid_width;
  block.h = screen_height / grid_height;



    
  // Render food
  SDL_SetRenderDrawColor(sdl_renderer, 0xFF, 0xCC, 0x00, 0xFF);
  block.x = food.x * block.w;
  block.y = food.y * block.h;
  SDL_RenderFillRect(sdl_renderer, &block);

  // Render snake's body
  SDL_SetRenderDrawColor(sdl_renderer, 0xFF, 0xFF, 0xFF, 0xFF);
  for (SDL_Point const &point : snake.body) {
    block.x = point.x * block.w;
    block.y = point.y * block.h;
    SDL_RenderFillRect(sdl_renderer, &block);
  }

  // Render snake's head
  block.x = static_cast<int>(snake.head_x) * block.w;
  block.y = static_cast<int>(snake.head_y) * block.h;
  if (snake.alive) {
    SDL_SetRenderDrawColor(sdl_renderer, 0x00, 0x7A, 0xCC, 0xFF);
  } else {
    SDL_SetRenderDrawColor(sdl_renderer, 0xFF, 0x00, 0x00, 0xFF);
  }
  SDL_RenderFillRect(sdl_renderer, &block);


    
  // Update Screen
  SDL_RenderPresent(sdl_renderer);
}

void Renderer::UpdateWindowTitle(int score, int fps) {
  std::string title{"Snake Score: " + std::to_string(score) + " FPS: " + std::to_string(fps)};
  SDL_SetWindowTitle(sdl_window, title.c_str());
}


bool Renderer::Start()
{
  #if 0
    SDL_Window* stwindow = SDL_CreateWindow("SnakeGame Start", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 400, 250, SDL_WINDOW_SHOWN);
    SDL_Surface* stsurface = SDL_GetWindowSurface( stwindow );
    SDL_Surface* stsurf = IMG_Load("../start.png");
    
    if(stwindow == nullptr || stsurface == nullptr || stsurf == nullptr)
        std::cout << "Rendered Start: Error!!" << std::endl;
    
    
    SDL_BlitSurface( stsurf, NULL, stsurface, NULL );
    SDL_UpdateWindowSurface( stwindow );
    SDL_Delay(5000);
    
    SDL_FreeSurface(stsurf);
    SDL_FreeSurface(stsurface);
    SDL_DestroyWindow(stwindow);
    #endif
    return false;
}


void Renderer::End()
{
  #if 0
    SDL_Window* stwindow = SDL_CreateWindow("Snake Game END", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 400, 250, SDL_WINDOW_SHOWN);
    SDL_Surface* stsurface = SDL_GetWindowSurface( stwindow );
    SDL_Surface* stsurf = IMG_Load("../end.png");
    
    if(stwindow == nullptr || stsurface == nullptr || stsurf == nullptr)
        std::cout << "Rendered Start: Error!!" << std::endl;
    
    
    SDL_BlitSurface( stsurf, NULL, stsurface, NULL );
    SDL_UpdateWindowSurface( stwindow );
    SDL_Delay(5000);
    
    SDL_FreeSurface(stsurf);
    SDL_FreeSurface(stsurface);
    SDL_DestroyWindow(stwindow);
    #endif
}

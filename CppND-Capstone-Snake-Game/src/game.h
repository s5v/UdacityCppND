#ifndef GAME_H
#define GAME_H

#include <random>
#include "SDL.h"
#include "controller.h"
#include "renderer.h"
#include "snake.h"
#include <vector>
#include <thread>
#include <mutex>

#include <deque>
#include <condition_variable>

//Msg Queue For Communication Between
//Retrieving Update Food Location and BackGround Color to be used for Snake

const SDL_Color blue = {100,0,255,255};
const SDL_Color red  = {255, 0 , 0, 255};
const SDL_Color grn  = {0,255,0,255};
const SDL_Color blk  = {0x1E, 0x1E, 0x1E, 255};

template <class T>
class MessageQueue
{
public:
    T receive();
    void send(T &&msg);
    
private:
    std::mutex _mutex;
    std::condition_variable _cond;
    std::deque<T> _queue;
    
};

template <typename T>
T MessageQueue<T>::receive()
{
    // perform queue modification under the lock
    std::unique_lock<std::mutex> uLock(_mutex);
    _cond.wait(uLock, [this] { return !_queue.empty(); }); // pass unique lock to condition variable
    
    // remove last vector element from queue
    T msg = std::move(_queue.back());
    _queue.pop_back();
    
    return msg; // will not be copied due to return value optimization (RVO) in C++
    
}

template <typename T>
void MessageQueue<T>::send(T &&msg)
{
    // perform vector modification under the lock
    std::lock_guard<std::mutex> uLock(_mutex);
    
    _queue.push_back(std::move(msg));
    _cond.notify_one(); // notify client after pushing new Vehicle into vector
}

class Game {
 public:
    Game(const std::size_t screen_width,
         const std::size_t screen_height,
         std::size_t grid_width,
         std::size_t grid_height);
  ~Game();
    
  void Run();
  
  int GetScore() const;
  int GetSize() const;
    
  //Update BackGround Color
  void UpdateBckgrnd();
    
  void Initiate(std::size_t target_frame_duration);
  static SDL_Color bcolor ;
 private:
  Snake snake;
  SDL_Point food;
  Renderer renderer;
  Controller controller;

    
  std::random_device dev;
  std::mt19937 engine;
  std::uniform_int_distribution<int> random_w;
  std::uniform_int_distribution<int> random_h;

  int score{0};

  void PlaceFood();
  void Update();
    
  std::thread b_thread; // holds all threads that have been launched within this object
    
  std::size_t target_frame_duration;
    
  MessageQueue<int> _msgq;
    std::mutex gmutex;
};

#endif

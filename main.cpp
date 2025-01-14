#include"raylib/raylib.h"
#include<iostream>

#define SCREEN_WIDTH 1000
#define SCREEN_HEIGHT 1000


#include"include/grid.hpp"

int main(){
  //init stuff
  InitWindow(SCREEN_WIDTH,SCREEN_HEIGHT,"wheel disp");

  SetTargetFPS(120);

  //init grid
  grid g(SCREEN_WIDTH,SCREEN_HEIGHT);
  std::cout<<"Inititalize"<<std::endl;
  
  while(!WindowShouldClose()){
    //handle inputs
    g.HandleInputs();
    //update
    g.Update();
    //draw
    
    BeginDrawing();
    ClearBackground(WHITE);

    g.DrawGrid();
  
    EndDrawing();

  }
  CloseWindow();
  
  return 0;
}

#pragma once

#include"stdio.h"
#include"../raylib/raylib.h"

#include<vector>
#include<random>

#include<fstream>
#include<iostream>

class grid{
public:
  grid(int height,int width);

  void DrawGrid();
  void DrawCells();

  //sims
  void UpdateCells();
  int GetRandom();
  void FillRandomDroplets();

  void OpUpdateCells();
  void EvOpUpdateCells();
  void InitActiveCells();
  std::vector<std::pair<int,int>>activeCells;
  //update
  void Update();
  void HandleInputs();
  
private:
  //file handling
  std::ofstream file;

  
  int grid_cols;
  int grid_rows;
  int grid_size;
  int grid_height;
  int grid_width;

  std::vector<int> demo;
  std::vector<std::vector<int>> cell;
  //dummy cell
  std::vector<std::vector<int>> loadDummy;

};

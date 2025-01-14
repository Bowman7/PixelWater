#include"../include/grid.hpp"

//handle mouse inputs
void grid::HandleInputs(){
  int m_x,m_y;
  if(IsMouseButtonDown(MOUSE_BUTTON_LEFT)){
    m_x = GetMouseX();
    m_y = GetMouseY();

    int t_col = m_x%grid_size;
    int t_row = m_y%grid_size;

    int col = (m_x - t_col)/10;
    int row = (m_y - t_row)/10;

    //printf("pos x: %d y: %d\n",pos_x,pos_y);

    std::pair<int,int> temp;
    temp.first = row;
    temp.second = col;

    activeCells.emplace_back(temp);
  }else if(IsMouseButtonDown(MOUSE_BUTTON_RIGHT)){
    m_x = GetMouseX();
    m_y = GetMouseY();

    int t_col = m_x%grid_size;
    int t_row = m_y%grid_size;

    int col = (m_x - t_col)/10;
    int row = (m_y - t_row)/10;

    cell[row][col] = 2;//2 for wall
    
  }
}
//update
void grid::Update(){
  EvOpUpdateCells();
  
}//eval-optimized update cells
void grid::EvOpUpdateCells(){
  std::vector<std::vector<int>>dummy  = cell;
  //new active cells
  std::vector<std::pair<int,int>>dummyActive;
  std::pair<int,int> temp;
  int rows = grid_rows;
  int cols = grid_cols;
  //only cehck active cells
  for(std::pair<int,int>& c : activeCells){
    if(c.first<rows-1 && cell[c.first+1][c.second] == 0 &&
       dummy[c.first+1][c.second] == 0){
      
      dummy[c.first+1][c.second] = 1;
      dummy[c.first][c.second] = 0;

      dummyActive.emplace_back(c.first+1,c.second);
    }else{
      if(GetRandom()==1){
	//right move
	if(c.second<cols-1 && cell[c.first][c.second+1] == 0 &&
	   dummy[c.first][c.second+1] == 0){
	  dummy[c.first][c.second+1] = 1;
	  dummy[c.first][c.second] = 0;

	  dummyActive.emplace_back(c.first,c.second+1);
	}else if(c.second>=1 && cell[c.first][c.second-1] == 0 &&
		 dummy[c.first][c.second-1] == 0){
	  dummy[c.first][c.second-1] = 1;
	  dummy[c.first][c.second] = 0;

	  dummyActive.emplace_back(c.first,c.second-1);
	}else{
	  dummyActive.emplace_back(c);
	}
      }else{
	dummyActive.emplace_back(c);
      }
    }
  }
  activeCells = dummyActive;
  cell = dummy;
}

//update cells
void grid::UpdateCells(){
  std::vector<std::vector<int>>dummy  = cell;
  int rows = grid_rows;
  int cols = grid_cols;
  for(int r=0;r<rows;r++){
    for(int c=0;c<cols;c++){ 
      if(cell[r][c] == 1 && r<rows-1 && cell[r+1][c] == 0 && dummy[r+1][c] == 0){
	dummy[r+1][c] = 1;
	dummy[r][c] = 0;
      }else if(GetRandom() == 1){//right
	if(cell[r][c] == 1 && c<=cols-1 && cell[r][c+1] == 0 && dummy[r][c+1] == 0){
	  dummy[r][c+1] = 1;
	  dummy[r][c] = 0;
	}
      }else{//left
	if(cell[r][c] == 1 && c>=1 && cell[r][c-1] == 0 && dummy[r][c-1] == 0){
	  dummy[r][c-1] = 1;
	  dummy[r][c] = 0;
	}
      }
    }
  }
  cell = dummy;
}

//get random
int grid::GetRandom(){
  std::random_device dev;
  std::mt19937 rng(dev());
  std::uniform_int_distribution<std::mt19937::result_type>dist6(0,10);

  int val = dist6(rng);
  if(val%2==0){
    return 1;
  }
  return 0;
}
grid::grid(int height,int width){
    grid_cols=100;
    grid_rows = 100;
    grid_size = 10;
    grid_height = height;
    grid_width = width;
    //printf("yeya aKASDFKJBASDKFBKJDSF");

    //init cells
    cell = std::vector<std::vector<int>>(grid_rows,std::vector<int>(grid_cols,0));
    //inti random droplets 500
    FillRandomDroplets();
   
    
}
//fill random dropets
void grid::FillRandomDroplets(){
  std::pair<int,int> temp;
  
  int DropCount  = 0;
  for(int r =0;r<grid_rows;r++){
    for(int c = 0;c<grid_cols;c++){
      int val = GetRandom();
      if(DropCount<300){
	if(val == 1){
	  cell[r][c] = 1;
	  //place pair loc
	  temp.first = r;
	  temp.second = c;
	  activeCells.push_back(temp);
	  DropCount++;
	  //printf("Dropcount: %d\n",DropCount);
	}
      }
    }
  }
}
void grid::DrawGrid(){

  for(int i=0;i<grid_cols;i++){
    //cols
    //DrawLine(i*grid_size,0,i*grid_size,grid_height,BLACK);
    //rows
    //DrawLine(0,i*grid_size,grid_width,i*grid_size,BLUE);
  }
  DrawCells();
}


void grid::DrawCells(){
  
  int radius = grid_size/2;
  //draw drop lets
  for(int r=0;r<grid_rows;r++){
    for(int c=0;c<grid_cols;c++){
      if(cell[r][c] == 1){
	DrawRectangle(c*grid_size,r*grid_size,grid_size,grid_size,DARKBLUE);
	/* int x = (c*grid_size)+(grid_size/2); */
	/* int y = (r*grid_size)+(grid_size/2); */
	
	/* DrawCircle(x,y,radius,DARKBLUE); */
      }else if(cell[r][c] == 2){
	DrawRectangle(c*grid_size,r*grid_size,grid_size,grid_size,BLACK);
      }
    }
  }
}


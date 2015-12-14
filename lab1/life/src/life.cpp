//Game of Life
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include "../lib/StanfordCPPLib/grid.h"
#include "../lib/lifeutil.h"

using namespace std;

void welcomeMsg();
void createBoard(Grid<char> &board, int &rows, int &cols);
void initTempBoard(int &rows, int &cols, Grid<int> &tempBoard);
void printBoard(Grid<char> &board, int &rows, int &cols);
void gameLoop(Grid<char> &board, int &rows, int &cols, Grid<int> &tempBoard);
void increaseNeighbours(int &rows, int &cols, int cur_row, int cur_col, Grid<int> &tempBoard);
void overWriteBoard(int &rows, int &cols, Grid<int> &tempBoard, Grid<char> &board);
int dedgaem(Grid<char> &board, int &rows, int &cols);

void printTempBoard(Grid<int> &tempBoard, int &rows, int &cols); //debugger

int main(){
  
  char c;
  Grid <char> board;
  Grid <int> tempBoard;
  int rows;
  int cols;
  
  welcomeMsg(); //hello welcome to...
  createBoard(board, rows, cols); //reads infile
  initTempBoard(rows, cols, tempBoard); //remove bogus data if any
  printBoard(board, rows, cols);
  cout << "a)nimate, c)lear, t)ick, q)uit? ";
  cin >> c;
  while (c == 't' or c == 'c'){
    if (c == 'c'){
      clearConsole();
    }
    gameLoop(board, rows, cols, tempBoard);
    //printTempBoard(tempBoard, rows, cols); //debug function
    overWriteBoard(rows, cols, tempBoard, board); //also resets tempBoard
    printBoard(board, rows, cols);
    if (dedgaem(board, rows, cols)){ //only triggers if entire board is '-'
      cout << "You ded boi." << endl;
      break;
    }
    cout << "a)nimate, c)lear, t)ick, q)uit? ";
    cin >> c;
  }
  while (c == 'a'){
    gameLoop(board, rows, cols, tempBoard);
    overWriteBoard(rows, cols, tempBoard, board);
    clearConsole(); //for smooth animation, no spam
    printBoard(board, rows, cols);
    pause(250); //tick timer (ms)
    if (dedgaem(board, rows, cols)){ //only triggers if entire board is '-'
      cout << "You ded boi." << endl;
      break;
    } 
  }
  if (c == 'q'){
    cout << "Have a nice Life!" << endl;
  }
  return 0;
}

void welcomeMsg(){
  cout << "Welcome to the TDDD86 Game of Life," << endl;
  cout << "a simulation of the lifecycle of a bacteria colony." << endl;
  cout << "Cells (X) live and die by the following rules:" << endl;
  cout << " - A cell with 1 or fewer neighbours dies." << endl;
  cout << " - Locations with 2 neighbours remain stable." << endl;
  cout << " - Locations with 3 neighbours will create life." << endl;
  cout << " - A cell with 4 or more neighbours dies." << endl;
}

void createBoard(Grid<char> &board, int &rows, int &cols){
  //reads file input, puts resulting input into the board-grid and rows/cols variables.
  string filename;
  ifstream fileInput;
  string line;
  cout << "Grid input file name? ";
  cin >> filename;
  fileInput.open(filename.c_str());
  getline(fileInput, line); //rows
  istringstream (line) >> rows; //convert string to int
  getline(fileInput, line); //cols
  istringstream (line) >> cols; //convert string to int
  board.resize(rows, cols);
  int cur_row = 0;
  while (getline(fileInput, line)){
    for (int cur_col = 0; cur_col < line.length(); cur_col++){
      board[cur_row][cur_col] = line[cur_col]; //puts - or X for every char in grid
    }
    cur_row++;
    if (cur_row == rows){
      break; //skip all the irrelevant info text at the bottom
    }
  }
  fileInput.close();
}

void initTempBoard(int &rows, int &cols, Grid<int> &tempBoard){
  //initializes tempBoard to a grid with (rows, cols) dimensions full of zeroes.
  tempBoard.resize(rows, cols);
  for (int cur_row = 0; cur_row < rows; cur_row++){
    for (int cur_col = 0; cur_col < cols; cur_col++){
      tempBoard[cur_row][cur_col] = 0;
    }
  }
}

void printTempBoard(Grid<int> &tempBoard, int &rows, int &cols){
  //debugger, does exactly the same thing as printBoard, but for tempBoard.
  for (int cur_row = 0; cur_row < rows; cur_row++){
    for (int cur_col = 0; cur_col < cols; cur_col++){
      cout << tempBoard[cur_row][cur_col];
    }
    cout << endl;
  }
}

void printBoard(Grid<char> &board, int &rows, int &cols){
  //prints current status of board to screen
  for (int cur_row = 0; cur_row < rows; cur_row++){
    for (int cur_col = 0; cur_col < cols; cur_col++){
      cout << board[cur_row][cur_col];
    }
    cout << endl;
  }
}

void gameLoop(Grid<char> &board, int &rows, int &cols, Grid<int> &tempBoard){
  //find alive cells, if cell is alive, call for increaseNeighbours(args)
  for (int cur_row = 0; cur_row < rows; cur_row++){
    for (int cur_col = 0; cur_col < cols; cur_col++){
      if (board[cur_row][cur_col] == 'X'){
	increaseNeighbours(rows, cols, cur_row, cur_col, tempBoard);
      }
    }
  }
}

void increaseNeighbours(int &rows, int &cols, int cur_row, int cur_col, Grid<int> &tempBoard){
  //if alive cell is found, increment all valid neighbours with 1.
  int tempRow;
  int tempCol;
  for (tempRow = cur_row - 1; tempRow < cur_row + 2; tempRow++){
    for (tempCol = cur_col - 1; tempCol < cur_col + 2; tempCol++){ //loop 3x3
      if (not (tempRow < 0 or tempRow + 2 > rows + 1 or tempCol < 0 or tempCol + 2 > cols + 1)){ //edge checking, we can't index tempBoard out of range
	if ((tempBoard[tempRow][tempCol] < 4) and (tempRow != cur_row or tempCol != cur_col)){ //no need to increase past 4, don't increase ourselves
	  tempBoard[tempRow][tempCol]++;
	}
      }
    }
  }
}

void overWriteBoard(int &rows, int &cols, Grid<int> &tempBoard, Grid<char> &board){
  /*basically does the conversion of board = tempBoard using the switch-case as a
    dictionary; then resets tempBoard. */
  for (int cur_row = 0; cur_row < rows; cur_row++){
    for (int cur_col = 0; cur_col < cols; cur_col++){
      switch (tempBoard[cur_row][cur_col]){
      case 0:
	board[cur_row][cur_col] = '-';
	break;
      case 1:
	board[cur_row][cur_col] = '-';
	break;
      case 2:
	tempBoard[cur_row][cur_col] = tempBoard[cur_row][cur_col]; //redundant?
	break;
      case 3:
	board[cur_row][cur_col] = 'X';
	break;
      case 4:
	board[cur_row][cur_col] = '-';
	break;
      }	
      tempBoard[cur_row][cur_col] = 0;
    }
  }
}

int dedgaem(Grid<char> &board, int &rows, int &cols){
  //if no X are present stop animating
  for (int cur_row = 0; cur_row < rows; cur_row++){
    for (int cur_col = 0; cur_col < cols; cur_col++){
      if (board[cur_row][cur_col] == 'X'){
	return 0;
      }
    }
  }
  return 1;
}

//g++ -o out life.cpp ../lib/lifeutil.cpp -std=c++11 -g compiling for ubuntu deb

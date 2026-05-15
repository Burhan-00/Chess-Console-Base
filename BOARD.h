#pragma once
#include"PIECE.h"
#include<windows.h>
void setColor(int textColor, int backgroundColor);
void gotoxy(int positionX, int positionY);
using namespace std;
class Board
{
private:
	PIECE* board[8][8];
	int boardSize;
public:
	Board();
	void setupBoard();
	void displayBoard(COLOR currentTurn);
	void movepiece(int sourceRow, int sourceCol, int destRow, int destCol);
	bool is_Path_Clear(int sourceRow, int sourceCol, int destRow, int destCol);
	bool is_King_Alive();
	void find_King(COLOR kingColor, int& kingRow, int& kingCol);
	bool is_Check(COLOR kingColor);
	bool is_Check_Mate(COLOR kingColor);
	bool check_safety(int sourceRow, int sourceCol, int destRow, int destCol, COLOR kingColor);
	PIECE* get_piece(int pieceRow, int pieceCol);
	~Board();
};

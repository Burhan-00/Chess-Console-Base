#pragma once
#include"BOARD.h"
class GAME
{
	Board chessBoard;
	COLOR activeTurn = WHITE;
public:
	void showMenu();
	void showMessage(string displayMessage, int textColor);
	void Start_Game();
	void switch_Turn();
	void Input_convert(string playerInput, int& boardRow, int& boardCol);
	bool is_Valid_Input(string inputValue);
	bool is_Current_Player_Piece(int pieceRow, int pieceCol);
};

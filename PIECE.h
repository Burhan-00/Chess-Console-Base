#pragma once
#include<iostream> 
using namespace std;

enum COLOR
{
	BLACK, WHITE
};
class Board;
class PIECE
{
protected:
	COLOR pieceColor;
	char pieceSymbol;
public:
	PIECE(char pieceChar, COLOR pieceShade);
	char get_Symbol();
	COLOR get_color();
	virtual bool isValidMove(int startRow, int startCol, int destRow, int destCol, Board* chessBoard) = 0;
	virtual ~PIECE() = 0;
};
class PAWN :public PIECE
{
public:
	PAWN(char pawnChar, COLOR pawnColor);
	bool isValidMove(int startRow, int startCol, int destRow, int destCol, Board* chessBoard);
};
class ROOK :public PIECE
{
public:
	ROOK(char rookChar, COLOR rookColor);
	bool isValidMove(int startRow, int startCol, int destRow, int destCol, Board* chessBoard);
};
class KNIGHT :public PIECE
{
public:
	KNIGHT(char knightChar, COLOR knightColor);
	bool isValidMove(int startRow, int startCol, int destRow, int destCol, Board* chessBoard);
};
class BISHOP :public PIECE
{
public:
	BISHOP(char bishopChar, COLOR bishopColor);
	bool isValidMove(int startRow, int startCol, int destRow, int destCol, Board* chessBoard);
};
class QUEEN :public PIECE
{
public:
	QUEEN(char queenChar, COLOR queenColor);
	bool isValidMove(int startRow, int startCol, int destRow, int destCol, Board* chessBoard);
};
class KING :public PIECE
{
public:
	KING(char kingChar, COLOR kingColor);
	bool isValidMove(int startRow, int startCol, int destRow, int destCol, Board* chessBoard);
};

#include"PIECE.h"
#include "Board.h"
//PIECE-----------------------------
PIECE::PIECE(char pieceChar, COLOR pieceShade)
{
	pieceSymbol = pieceChar;
	pieceColor = pieceShade;
}
char PIECE::get_Symbol()
{
	return pieceSymbol;
}
COLOR PIECE::get_color()
{
	return pieceColor;
}

PIECE::~PIECE()
{

}
//PAWN-----------------
PAWN::PAWN(char pawnChar, COLOR pawnColor) :PIECE(pawnChar, pawnColor)
{

}
bool PAWN::isValidMove(int startRow, int startCol, int destRow, int destCol, Board* chessBoard)
{
	int moveDirection = ((pieceColor == WHITE) ? -1 : 1);
	if (startRow == destRow && startCol == destCol)//If same source and destination than invalid
	{
		return false;
	}
	if (startCol == destCol && destRow == startRow + moveDirection) //Logic for forward move
	{
		if (chessBoard->get_piece(destRow, destCol) == nullptr)
		{
			return true;
		}
	}
	if (startCol == destCol && destRow == startRow + 2 * moveDirection) //Logic for first time 2 step move
	{
		if ((pieceColor == WHITE && startRow == 6) || (pieceColor == BLACK && startRow == 1))//checking if pawn is at initial position
		{
			if (chessBoard->get_piece(startRow + moveDirection, startCol) == nullptr && chessBoard->get_piece(destRow, destCol) == nullptr)//Checking for empty space
			{
				return true;
			}
		}
	}
	int columnDifference = startCol - destCol;
	if ((columnDifference == 1 || columnDifference == -1) && destRow == startRow + moveDirection)//For diagonal attack
	{
		if (chessBoard->get_piece(destRow, destCol) != nullptr && chessBoard->get_piece(destRow, destCol)->get_color() != pieceColor)
		{
			return true;
		}
	}
	return false;
}
//BISHOP-------------------
BISHOP::BISHOP(char bishopChar, COLOR bishopColor) :PIECE(bishopChar, bishopColor)
{

}
bool BISHOP::isValidMove(int startRow, int startCol, int destRow, int destCol, Board* chessBoard)
{
	int rowDifference = destRow - startRow;
	int colDifference = destCol - startCol;
	if (rowDifference < 0)
	{
		rowDifference *= -1;
	}
	if (colDifference < 0)
	{
		colDifference *= -1;
	}
	if (rowDifference != colDifference || (startRow == destRow && startCol == destCol))//Invalid Move
	{
		return false;
	}
	if (!chessBoard->is_Path_Clear(startRow, startCol, destRow, destCol)) //Checking Path
	{
		return false;
	}
	if (chessBoard->get_piece(destRow, destCol) != nullptr && chessBoard->get_piece(destRow, destCol)->get_color() == pieceColor)//Checking same color piece
	{
		return false;
	}
	return true;
}
//KNIGHT--------------------
KNIGHT::KNIGHT(char knightChar, COLOR knightColor) :PIECE(knightChar, knightColor)
{

}
bool KNIGHT::isValidMove(int startRow, int startCol, int destRow, int destCol, Board* chessBoard)
{
	int rowDifference = destRow - startRow;
	int colDifference = destCol - startCol;
	if (rowDifference < 0)
	{
		rowDifference *= -1;
	}
	if (colDifference < 0)
	{
		colDifference *= -1;
	}
	if (!((rowDifference == 2 && colDifference == 1) || (rowDifference == 1 && colDifference == 2)))
	{
		return false;
	}
	if (chessBoard->get_piece(destRow, destCol) != nullptr && chessBoard->get_piece(destRow, destCol)->get_color() == pieceColor)
	{
		return false;
	}
	return true;
}
//QUEEN--------------------
QUEEN::QUEEN(char queenChar, COLOR queenColor) :PIECE(queenChar, queenColor)
{

}
bool QUEEN::isValidMove(int startRow, int startCol, int destRow, int destCol, Board* chessBoard)
{
	int rowDifference = destRow - startRow;
	int colDifference = destCol - startCol;
	if (rowDifference < 0)
	{
		rowDifference *= -1;
	}
	if (colDifference < 0)
	{
		colDifference *= -1;
	}
	if (startRow == destRow && startCol == destCol)
	{
		return false;
	}
	bool isDiagonalMove = (rowDifference == colDifference);
	bool isStraightMove = (startRow == destRow || startCol == destCol);
	if (!(isDiagonalMove || isStraightMove))
	{
		return false;
	}
	if (!chessBoard->is_Path_Clear(startRow, startCol, destRow, destCol))
	{
		return false;
	}
	if (chessBoard->get_piece(destRow, destCol) != nullptr && chessBoard->get_piece(destRow, destCol)->get_color() == pieceColor)
	{
		return false;
	}
	return true;
}
//KING------------------
KING::KING(char kingChar, COLOR kingColor) :PIECE(kingChar, kingColor)
{

}
bool KING::isValidMove(int startRow, int startCol, int destRow, int destCol, Board* chessBoard)
{
	int rowDifference = destRow - startRow;
	int colDifference = destCol - startCol;
	if (rowDifference < 0)
	{
		rowDifference *= -1;
	}
	if (colDifference < 0)
	{
		colDifference *= -1;
	}
	if (startRow == destRow && startCol == destCol)
	{
		return false;
	}
	if (rowDifference > 1 || colDifference > 1)
	{
		return false;
	}
	if (chessBoard->get_piece(destRow, destCol) != nullptr && chessBoard->get_piece(destRow, destCol)->get_color() == pieceColor)
	{
		return false;
	}
	return true;
}
//ROOK----------------
ROOK::ROOK(char rookChar, COLOR rookColor) :PIECE(rookChar, rookColor)
{

}

bool ROOK::isValidMove(int startRow, int startCol, int destRow, int destCol, Board* chessBoard)
{
	if (!(startRow == destRow || startCol == destCol))
	{
		return false;
	}
	if (startRow == destRow && startCol == destCol)
	{
		return false;
	}
	if (!chessBoard->is_Path_Clear(startRow, startCol, destRow, destCol))
	{
		return false;
	}
	if (chessBoard->get_piece(destRow, destCol) != nullptr && chessBoard->get_piece(destRow, destCol)->get_color() == pieceColor)
	{
		return false;
	}
	return true;
}

#include"PIECE.h"
#include "Board.h"
//----------------------PIECE-----------------------------
PIECE::PIECE(char s, COLOR c)
{
	symbol = s;
	color = c;
}
char PIECE::get_Symbol()
{
	return symbol;
}
COLOR PIECE::get_color()
{
	return color;
}

PIECE::~PIECE()
{

}
//------------PAWN-----------------
PAWN::PAWN(char s, COLOR c) :PIECE(s, c)
{

}
bool PAWN::isValidMove(int sr, int sc, int dr, int dc, Board* b)
{
	int direction = ((color == WHITE) ? -1 : 1);
	if (sr == dr && sc == dc)//If same source and destination than invalid
	{
		return false;
	}
	if (sc == dc && dr == sr + direction) //Logic for forward move
	{
		if (b->get_piece(dr, dc) == nullptr)
		{
			return true;
		}
	}
	if (sc == dc && dr == sr + 2 * direction) //Logic for first time 2 step move
	{
		if ((color == WHITE && sr == 6) || (color == BLACK && sr == 1))//checking if pawn is at initial position
		{
			if (b->get_piece(sr + direction, sc) == nullptr && b->get_piece(dr, dc) == nullptr)//Checking for empty space
			{
				return true;
			}
		}
	}
	int diff = sc - dc;
	if ((diff == 1 || diff == -1) && dr == sr + direction)//For diagonal attack
	{
		if (b->get_piece(dr, dc) != nullptr && b->get_piece(dr, dc)->get_color() != color)
		{
			return true;
		}
	}
	return false;
}
//---------------BISHOP-------------------
BISHOP::BISHOP(char s, COLOR c) :PIECE(s, c)
{

}
bool BISHOP::isValidMove(int sr, int sc, int dr, int dc, Board* b)
{
	int row_diff = dr - sr;
	int col_diff = dc - sc;
	if (row_diff < 0)
	{
		row_diff *= -1;
	}
	if (col_diff < 0)
	{
		col_diff *= -1;
	}
	if (row_diff != col_diff || (sr == dr && sc == dc))//Invalid Move
	{
		return false;
	}
	if (!b->is_Path_Clear(sr, sc, dr, dc)) //Checking Path
	{
		return false;
	}
	if (b->get_piece(dr, dc) != nullptr && b->get_piece(dr, dc)->get_color() == color)//Checking same color piece
	{
		return false;
	}
	return true;
}
//----------------KNIGHT--------------------
KNIGHT::KNIGHT(char s, COLOR c) :PIECE(s, c)
{

}
bool KNIGHT::isValidMove(int sr, int sc, int dr, int dc, Board* b)
{
	int row_diff = dr - sr;
	int col_diff = dc - sc;
	if (row_diff < 0)
	{
		row_diff *= -1;
	}
	if (col_diff < 0)
	{
		col_diff *= -1;
	}
	if (!((row_diff == 2 && col_diff == 1) || (row_diff == 1 && col_diff == 2)))
	{
		return false;
	}
	if (b->get_piece(dr, dc) != nullptr && b->get_piece(dr, dc)->get_color() == color)
	{
		return false;
	}
	return true;
}
//-----------------QUEEN--------------------
QUEEN::QUEEN(char s, COLOR c) :PIECE(s, c)
{

}
bool QUEEN::isValidMove(int sr, int sc, int dr, int dc, Board* b)
{
	int row_diff = dr - sr;
	int col_diff = dc - sc;
	if (row_diff < 0)
	{
		row_diff *= -1;
	}
	if (col_diff < 0)
	{
		col_diff *= -1;
	}
	if (sr == dr && sc == dc)
	{
		return false;
	}
	bool diagonal = (row_diff == col_diff);
	bool straight = (sr == dr || sc == dc);
	if (!(diagonal || straight))
	{
		return false;
	}
	if (!b->is_Path_Clear(sr, sc, dr, dc))
	{
		return false;
	}
	if (b->get_piece(dr, dc) != nullptr && b->get_piece(dr, dc)->get_color() == color)
	{
		return false;
	}
	return true;
}
//------------------KING------------------
KING::KING(char s, COLOR c) :PIECE(s, c)
{

}
bool KING::isValidMove(int sr, int sc, int dr, int dc, Board* b)
{
	int row_diff = dr - sr;
	int col_diff = dc - sc;
	if (row_diff < 0)
	{
		row_diff *= -1;
	}
	if (col_diff < 0)
	{
		col_diff *= -1;
	}
	if (sr == dr && sc == dc)
	{
		return false;
	}
	if (row_diff > 1 || col_diff > 1)
	{
		return false;
	}
	if (b->get_piece(dr, dc) != nullptr && b->get_piece(dr, dc)->get_color() == color)
	{
		return false;
	}
	return true;
}
//------------------ROOK----------------
ROOK::ROOK(char s, COLOR c) :PIECE(s, c)
{

}

bool ROOK::isValidMove(int sr, int sc, int dr, int dc, Board* b)
{
	if (!(sr == dr || sc == dc))
	{
		return false;
	}
	if (sr == dr && sc == dc)
	{
		return false;
	}
	if (!b->is_Path_Clear(sr, sc, dr, dc))
	{
		return false;
	}
	if (b->get_piece(dr, dc) != nullptr && b->get_piece(dr, dc)->get_color() == color)
	{
		return false;
	}
	return true;
}
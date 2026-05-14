#include"BOARD.h"
void setColor(int text, int bg)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (bg << 4) | text);
}
void gotoxy(int x, int y)
{
	COORD coord = { (SHORT)x, (SHORT)y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}
Board::Board()
{
	size = 8;
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			board[i][j] = nullptr;
		}
	}
}
void Board::setupBoard()
{
	board[0][0] = new ROOK('r', BLACK);
	board[0][1] = new KNIGHT('n', BLACK);
	board[0][2] = new BISHOP('b', BLACK);
	board[0][3] = new QUEEN('q', BLACK);
	board[0][4] = new KING('k', BLACK);
	board[0][5] = new BISHOP('b', BLACK);
	board[0][6] = new KNIGHT('n', BLACK);
	board[0][7] = new ROOK('r', BLACK);
	for (int i = 0; i < 8; i++)
	{
		board[1][i] = new PAWN('p', BLACK);
	}
	board[7][0] = new ROOK('R', WHITE);
	board[7][1] = new KNIGHT('N', WHITE);
	board[7][2] = new BISHOP('B', WHITE);
	board[7][3] = new QUEEN('Q', WHITE);
	board[7][4] = new KING('K', WHITE);
	board[7][5] = new BISHOP('B', WHITE);
	board[7][6] = new KNIGHT('N', WHITE);
	board[7][7] = new ROOK('R', WHITE);
	for (int i = 0; i < 8; i++)
	{

		board[6][i] = new PAWN('P', WHITE);
	}
}
void Board::displayBoard(COLOR turn)
{
	gotoxy(4, 1);
	setColor(14, 0);
	cout << "========  CHESS GAME  ========";
	gotoxy(4, 3);
	setColor(14, 0);
	cout << "   a  b  c  d  e  f  g  h";
	gotoxy(4, 4);
	cout << "  +--+--+--+--+--+--+--+--+";
	for (int i = 0; i < 8; i++)
	{
		gotoxy(4, 5 + i * 2);
		cout << 8 - i << " ";
		for (int j = 0; j < 8; j++)
		{
			bool isLight = (i + j) % 2 == 0;
			int bgColor = isLight ? 7 : 8; // 7=gray, 8=dark gray
			if (board[i][j] == nullptr)
			{
				setColor(0, bgColor);
				cout << "|  ";
			}
			else
			{
				char sym = board[i][j]->get_Symbol();
				setColor(0, bgColor);
				cout << "|" << sym << " ";
			}
		}
		setColor(14, 0);
		cout << "|";
		gotoxy(4, 6 + i * 2);
		cout << "  +--+--+--+--+--+--+--+--+";
	}
	// Right side info panel
	gotoxy(32, 4);
	setColor(11, 0); // Cyan
	cout << "+-----------------+";

	gotoxy(32, 4);
	if (turn == WHITE)
	{
		setColor(0, 7);
		cout << "|   WHITE'S TURN  |";
	}
	else
	{
		setColor(15, 8);
		cout << "|   BLACK'S TURN  |";
	}
	gotoxy(32, 5);
	setColor(11, 0);
	cout << "+-----------------+";
	gotoxy(32, 7);
	setColor(14, 0); // Yellow
	cout << "  PIECES INFO:";
	gotoxy(32, 8);
	setColor(7, 0); // Gray
	cout << "  R/r = Rook";
	gotoxy(32, 9);
	cout << "  N/n = Knight";
	gotoxy(32, 10);
	cout << "  B/b = Bishop";
	gotoxy(32, 11);
	cout << "  Q/q = Queen";
	gotoxy(32, 12);
	cout << "  K/k = King";
	gotoxy(32, 13);
	cout << "  P/p = Pawn";
	gotoxy(32, 15);
	setColor(11, 0);
	cout << "  UPPERCASE = White";
	gotoxy(32, 16);
	cout << "  lowercase = black";
	setColor(15, 0);
}
PIECE* Board::get_piece(int r, int c)
{
	return board[r][c];
}
void Board::movepiece(int sr, int sc, int dr, int dc)
{
	PIECE* p = board[sr][sc];
	if (p == nullptr)
	{
		return;
	}
	if (dr < 0 || dr >= 8 || dc < 0 || dc >= 8)
	{
		cout << "Out of bounds move!" << endl;
		return;
	}
	if (p->isValidMove(sr, sc, dr, dc, this))
	{
		if (board[dr][dc] != nullptr)
		{
			delete board[dr][dc];
		}
		board[dr][dc] = p;
		board[sr][sc] = nullptr;
	}
	else
	{
		cout << "Invalid Move!" << endl;
	}
}
bool Board::is_Path_Clear(int sr, int sc, int dr, int dc)
{
	int rowstep = 0;
	int colstep = 0;
	if (dr > sr)
	{
		rowstep = 1;
	}
	else if (dr < sr)
	{
		rowstep = -1;
	}
	if (dc > sc)
	{
		colstep = 1;
	}
	else if (dc < sc)
	{
		colstep = -1;
	}
	int r = sr + rowstep;
	int c = sc + colstep;
	while (r != dr || c != dc)
	{
		if (r < 0 || r >= 8 || c < 0 || c >= 8)
		{
			return false;
		}
		if (board[r][c] != nullptr)
		{
			return false;
		}
		r += rowstep;
		c += colstep;
	}
	return true;
}
bool Board::is_King_Alive()
{
	bool is_white_alive = false;
	bool is_black_alive = false;
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			if (board[i][j] != nullptr && board[i][j]->get_Symbol() == 'k' && board[i][j]->get_color() == BLACK)
			{
				is_black_alive = true;
			}
			if (board[i][j] != nullptr && board[i][j]->get_Symbol() == 'K' && board[i][j]->get_color() == WHITE)
			{
				is_white_alive = true;
			}
		}
	}
	return (is_white_alive && is_black_alive);
}
void Board::find_King(COLOR c, int& rows, int& col)
{
	char king_symbol;
	if (c == WHITE)
	{
		king_symbol = 'K';
	}
	else if (c == BLACK)
	{
		king_symbol = 'k';
	}
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			if (board[i][j] != nullptr && board[i][j]->get_Symbol() == king_symbol)
			{
				rows = i;
				col = j;
				return;
			}
		}
	}
}
bool Board::is_Check(COLOR c)
{
	int kr, kl;
	find_King(c, kr, kl);
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			if (board[i][j] != nullptr && board[i][j]->get_color() != c && board[i][j]->isValidMove(i, j, kr, kl, this))
			{
				return true;
			}
		}
	}
	return false;
}
bool Board::is_Check_Mate(COLOR c)
{
	if (!is_Check(c))
	{
		return false;
	}
	for (int sr = 0; sr < 8; sr++)
	{
		for (int sc = 0; sc < 8; sc++)
		{
			if (board[sr][sc] != nullptr && board[sr][sc]->get_color() == c)
			{
				for (int dr = 0; dr < 8; dr++)
				{
					for (int dc = 0; dc < 8; dc++)
					{
						if (board[sr][sc]->isValidMove(sr, sc, dr, dc, this))
						{
							if (check_safety(sr, sc, dr, dc, c))
							{
								return false;
							}
						}
					}
				}
			}
		}
	}
	return true;
}
bool Board::check_safety(int sr, int sc, int dr, int dc, COLOR c)
{
	PIECE* move = board[sr][sc];
	PIECE* capture = board[dr][dc];
	board[dr][dc] = move;
	board[sr][sc] = nullptr;
	bool check = is_Check(c);
	board[sr][sc] = move;
	board[dr][dc] = capture;
	return !check;
}
Board::~Board()
{
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			delete board[i][j];
		}
	}
}
#include"BOARD.h"

void setColor(int textColor, int backgroundColor)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (backgroundColor << 4) | textColor);
}
void gotoxy(int positionX, int positionY)
{
	COORD consoleCoord = { (SHORT)positionX, (SHORT)positionY };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), consoleCoord);
}
Board::Board()
{
	boardSize = 8;
	for (int rowIndex = 0; rowIndex < boardSize; rowIndex++)
	{
		for (int colIndex = 0; colIndex < boardSize; colIndex++)
		{
			board[rowIndex][colIndex] = nullptr;
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
	for (int pawnIndex = 0; pawnIndex < 8; pawnIndex++)
	{
		board[1][pawnIndex] = new PAWN('p', BLACK);
	}
	board[7][0] = new ROOK('R', WHITE);
	board[7][1] = new KNIGHT('N', WHITE);
	board[7][2] = new BISHOP('B', WHITE);
	board[7][3] = new QUEEN('Q', WHITE);
	board[7][4] = new KING('K', WHITE);
	board[7][5] = new BISHOP('B', WHITE);
	board[7][6] = new KNIGHT('N', WHITE);
	board[7][7] = new ROOK('R', WHITE);
	for (int pawnIndex = 0; pawnIndex < 8; pawnIndex++)
	{

		board[6][pawnIndex] = new PAWN('P', WHITE);
	}
}
void Board::displayBoard(COLOR currentTurn)
{
	gotoxy(4, 1);
	setColor(14, 0);
	cout << "========  CHESS GAME  ========";
	gotoxy(4, 3);
	setColor(14, 0);
	cout << "   a  b  c  d  e  f  g  h";
	gotoxy(4, 4);
	cout << "  +--+--+--+--+--+--+--+--+";
	for (int rowIndex = 0; rowIndex < 8; rowIndex++)
	{
		gotoxy(4, 5 + rowIndex * 2);
		cout << 8 - rowIndex << " ";
		for (int colIndex = 0; colIndex < 8; colIndex++)
		{
			bool isLightSquare = (rowIndex + colIndex) % 2 == 0;
			int backgroundShade = isLightSquare ? 7 : 8; // 7=gray, 8=dark gray
			if (board[rowIndex][colIndex] == nullptr)
			{
				setColor(0, backgroundShade);
				cout << "|  ";
			}
			else
			{
				char pieceCharacter = board[rowIndex][colIndex]->get_Symbol();
				setColor(0, backgroundShade);
				cout << "|" << pieceCharacter << " ";
			}
		}
		setColor(14, 0);
		cout << "|";
		gotoxy(4, 6 + rowIndex * 2);
		cout << "  +--+--+--+--+--+--+--+--+";
	}
	// Right side info panel
	gotoxy(32, 4);
	setColor(11, 0); // Cyan
	cout << "+-----------------+";

	gotoxy(32, 4);
	if (currentTurn == WHITE)
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
PIECE* Board::get_piece(int pieceRow, int pieceCol)
{
	return board[pieceRow][pieceCol];
}
void Board::movepiece(int sourceRow, int sourceCol, int destRow, int destCol)
{
	PIECE* selectedPiece = board[sourceRow][sourceCol];
	if (selectedPiece == nullptr)
	{
		return;
	}
	if (destRow < 0 || destRow >= 8 || destCol < 0 || destCol >= 8)
	{
		cout << "Out of bounds move!" << endl;
		return;
	}
	if (selectedPiece->isValidMove(sourceRow, sourceCol, destRow, destCol, this))
	{
		if (board[destRow][destCol] != nullptr)
		{
			delete board[destRow][destCol];
		}
		board[destRow][destCol] = selectedPiece;
		board[sourceRow][sourceCol] = nullptr;
	}
	else
	{
		cout << "Invalid Move!" << endl;
	}
}
bool Board::is_Path_Clear(int sourceRow, int sourceCol, int destRow, int destCol)
{
	int rowStepValue = 0;
	int colStepValue = 0;
	if (destRow > sourceRow)
	{
		rowStepValue = 1;
	}
	else if (destRow < sourceRow)
	{
		rowStepValue = -1;
	}
	if (destCol > sourceCol)
	{
		colStepValue = 1;
	}
	else if (destCol < sourceCol)
	{
		colStepValue = -1;
	}
	int currentRow = sourceRow + rowStepValue;
	int currentCol = sourceCol + colStepValue;
	while (currentRow != destRow || currentCol != destCol)
	{
		if (currentRow < 0 || currentRow >= 8 || currentCol < 0 || currentCol >= 8)
		{
			return false;
		}
		if (board[currentRow][currentCol] != nullptr)
		{
			return false;
		}
		currentRow += rowStepValue;
		currentCol += colStepValue;
	}
	return true;
}
bool Board::is_King_Alive()
{
	bool isWhiteKingAlive = false;
	bool isBlackKingAlive = false;
	for (int rowIndex = 0; rowIndex < 8; rowIndex++)
	{
		for (int colIndex = 0; colIndex < 8; colIndex++)
		{
			if (board[rowIndex][colIndex] != nullptr && board[rowIndex][colIndex]->get_Symbol() == 'k' && board[rowIndex][colIndex]->get_color() == BLACK)
			{
				isBlackKingAlive = true;
			}
			if (board[rowIndex][colIndex] != nullptr && board[rowIndex][colIndex]->get_Symbol() == 'K' && board[rowIndex][colIndex]->get_color() == WHITE)
			{
				isWhiteKingAlive = true;
			}
		}
	}
	return (isWhiteKingAlive && isBlackKingAlive);
}
void Board::find_King(COLOR kingColor, int& kingRow, int& kingCol)
{
	char kingSymbol;
	if (kingColor == WHITE)
	{
		kingSymbol = 'K';
	}
	else if (kingColor == BLACK)
	{
		kingSymbol = 'k';
	}
	for (int rowIndex = 0; rowIndex < boardSize; rowIndex++)
	{
		for (int colIndex = 0; colIndex < boardSize; colIndex++)
		{
			if (board[rowIndex][colIndex] != nullptr && board[rowIndex][colIndex]->get_Symbol() == kingSymbol)
			{
				kingRow = rowIndex;
				kingCol = colIndex;
				return;
			}
		}
	}
}
bool Board::is_Check(COLOR kingColor)
{
	int kingRow, kingCol;
	find_King(kingColor, kingRow, kingCol);
	for (int rowIndex = 0; rowIndex < 8; rowIndex++)
	{
		for (int colIndex = 0; colIndex < 8; colIndex++)
		{
			if (board[rowIndex][colIndex] != nullptr && board[rowIndex][colIndex]->get_color() != kingColor && board[rowIndex][colIndex]->isValidMove(rowIndex, colIndex, kingRow, kingCol, this))
			{
				return true;
			}
		}
	}
	return false;
}
bool Board::is_Check_Mate(COLOR kingColor)
{
	if (!is_Check(kingColor))
	{
		return false;
	}
	for (int sourceRow = 0; sourceRow < 8; sourceRow++)
	{
		for (int sourceCol = 0; sourceCol < 8; sourceCol++)
		{
			if (board[sourceRow][sourceCol] != nullptr && board[sourceRow][sourceCol]->get_color() == kingColor)
			{
				for (int destRow = 0; destRow < 8; destRow++)
				{
					for (int destCol = 0; destCol < 8; destCol++)
					{
						if (board[sourceRow][sourceCol]->isValidMove(sourceRow, sourceCol, destRow, destCol, this))
						{
							if (check_safety(sourceRow, sourceCol, destRow, destCol, kingColor))
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
bool Board::check_safety(int sourceRow, int sourceCol, int destRow, int destCol, COLOR kingColor)
{
	PIECE* movingPiece = board[sourceRow][sourceCol];
	PIECE* capturedPiece = board[destRow][destCol];
	board[destRow][destCol] = movingPiece;
	board[sourceRow][sourceCol] = nullptr;
	bool isKingInCheck = is_Check(kingColor);
	board[sourceRow][sourceCol] = movingPiece;
	board[destRow][destCol] = capturedPiece;
	return !isKingInCheck;
}
Board::~Board()
{
	for (int rowIndex = 0; rowIndex < 8; rowIndex++)
	{
		for (int colIndex = 0; colIndex < 8; colIndex++)
		{
			delete board[rowIndex][colIndex];
		}
	}
}

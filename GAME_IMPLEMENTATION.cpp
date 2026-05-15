#include"GAME.h"

void GAME::Input_convert(string inputValue, int& boardRow, int& boardCol)
{
	boardRow = 8 - (inputValue[1] - '0');
	boardCol = inputValue[0] - 'a';
}
void GAME::switch_Turn()
{
	if (activeTurn == WHITE)
	{
		activeTurn = BLACK;
	}
	else
	{
		activeTurn = WHITE;
	}
}
bool GAME::is_Valid_Input(string inputValue)
{
	if (inputValue.length() != 2)
	{
		return false;
	}
	if ((inputValue[0] >= 'a' && inputValue[0] <= 'h') && (inputValue[1] >= '1' && inputValue[1] <= '8'))
	{
		return true;
	}
	return false;
}
bool GAME::is_Current_Player_Piece(int pieceRow, int pieceCol)
{
	if (chessBoard.get_piece(pieceRow, pieceCol) == nullptr)
	{
		return false;
	}
	return chessBoard.get_piece(pieceRow, pieceCol)->get_color() == activeTurn;
}
void GAME::showMenu()
{
	system("cls");
	setColor(14, 0); // Yellow
	gotoxy(30, 5);
	cout << "===========================";
	gotoxy(30, 6);
	cout << "|                         |";
	gotoxy(30, 7);
	cout << "|       CHESS GAME        |";
	gotoxy(30, 8);
	cout << "|                         |";
	gotoxy(30, 9);
	cout << "===========================";
	gotoxy(30, 12);
	setColor(11, 0); // Cyan
	cout << "  1. Start New Game";
	gotoxy(30, 14);
	cout << "  2. Exit";
	gotoxy(30, 17);
	setColor(7, 0); // Gray
	cout << "Enter choice (1 or 2): ";
	setColor(15, 0);
}
void GAME::showMessage(string displayMessage, int textColor)
{
	system("cls");
	setColor(textColor, 0);
	gotoxy(28, 8);
	cout << "==========================================";
	gotoxy(28, 9);
	cout << "|                                        |";
	gotoxy(28, 10);
	cout << " " << displayMessage << "      ";
	gotoxy(28, 11);
	cout << "|                                        |";
	gotoxy(28, 12);
	cout << "==========================================";
	setColor(15, 0);
	Sleep(1500); //To pop up Conditional messages
	system("cls");
}
void GAME::Start_Game()
{
	string sourcePosition, destinationPosition;
	int sourceRow, sourceCol, destRow, destCol;
	COLOR enemyKingColor;
	chessBoard.setupBoard();
	while (chessBoard.is_King_Alive())
	{
		chessBoard.displayBoard(activeTurn);
		gotoxy(4, 24);
		setColor(11, 0);
		cout << "Source: ";
		setColor(15, 0);
		cin >> sourcePosition;
		if (!is_Valid_Input(sourcePosition))
		{
			showMessage("   INVALID INPUT! TRY AGAIN  ", 12);
			continue;
		}
		gotoxy(4, 25);
		setColor(11, 0);
		cout << "Destination: ";
		setColor(15, 0);
		cin >> destinationPosition;
		if (!is_Valid_Input(destinationPosition))
		{
			showMessage("   INVALID INPUT! TRY AGAIN  ", 12);
			continue;
		}
		Input_convert(sourcePosition, sourceRow, sourceCol);
		Input_convert(destinationPosition, destRow, destCol);
		if (!is_Current_Player_Piece(sourceRow, sourceCol))
		{
			showMessage("    NOT YOUR PIECE!          ", 12);
			continue;
		}
		PIECE* selectedPiece = chessBoard.get_piece(sourceRow, sourceCol);
		if (selectedPiece == nullptr)
		{
			showMessage("    EMPTY LOCATION!          ", 12);
			continue;
		}
		if (!selectedPiece->isValidMove(sourceRow, sourceCol, destRow, destCol, &chessBoard))
		{
			showMessage("    INVALID MOVE!            ", 12);
			continue;
		}
		if (!chessBoard.check_safety(sourceRow, sourceCol, destRow, destCol, activeTurn))
		{
			showMessage("  MOVE PUTS YOU IN CHECK!    ", 12);
			continue;
		}
		chessBoard.movepiece(sourceRow, sourceCol, destRow, destCol);
		if (chessBoard.is_King_Alive() == false)
		{

			if (activeTurn == WHITE)
			{
				showMessage("  GAME OVER! WHITE WINS    ", 12);
			}
			else
			{
				showMessage("  GAME OVER! BLACK WINS    ", 12);
			}
			break;
		}
		if (activeTurn == WHITE)
		{
			enemyKingColor = BLACK;
		}
		else
		{
			enemyKingColor = WHITE;
		}
		if (chessBoard.is_Check(enemyKingColor))
		{
			if (chessBoard.is_Check_Mate(enemyKingColor))
			{
				if (activeTurn == WHITE)
				{
					showMessage("  CHECKMATE! WHITE WINS!     ", 10);
					system("pause");
				}
				else
				{
					showMessage("  CHECKMATE! BLACK WINS!     ", 10);
					system("pause");
				}
				break;
			}
			else
			{
				showMessage("     CHECK     ", 10);
			}
		}
		switch_Turn();
		system("cls");
	}
}

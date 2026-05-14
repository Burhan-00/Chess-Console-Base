#include"GAME.h"
void GAME::Input_convert(string s, int& row, int& col)
{
	row = 8 - (s[1] - '0');
	col = s[0] - 'a';
}
void GAME::switch_Turn()
{
	if (current_turn == WHITE)
	{
		current_turn = BLACK;
	}
	else
	{
		current_turn = WHITE;
	}
}
bool GAME::is_Valid_Input(string s)
{
	if (s.length() != 2)
	{
		return false;
	}
	if ((s[0] >= 'a' && s[0] <= 'h') && (s[1] >= '1' && s[1] <= '8'))
	{
		return true;
	}
	return false;
}
bool GAME::is_Current_Player_Piece(int r, int c)
{
	if (b.get_piece(r, c) == nullptr)
	{
		return false;
	}
	return b.get_piece(r, c)->get_color() == current_turn;
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
void GAME::showMessage(string msg, int color)
{
	system("cls");
	setColor(color, 0);
	gotoxy(28, 8);
	cout << "==========================================";
	gotoxy(28, 9);
	cout << "|                                        |";
	gotoxy(28, 10);
	cout << " " << msg << "      ";
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
	string source, destination;
	int sr, sc, dr, dc;
	COLOR enemyking;
	b.setupBoard();
	while (b.is_King_Alive())
	{
		b.displayBoard(current_turn);
		gotoxy(4, 24);
		setColor(11, 0);
		cout << "Source: ";
		setColor(15, 0);
		cin >> source;
		if (!is_Valid_Input(source))
		{
			showMessage("   INVALID INPUT! TRY AGAIN  ", 12);
			continue;
		}
		gotoxy(4, 25);
		setColor(11, 0);
		cout << "Destination: ";
		setColor(15, 0);
		cin >> destination;
		if (!is_Valid_Input(destination))
		{
			showMessage("   INVALID INPUT! TRY AGAIN  ", 12);
			continue;
		}
		Input_convert(source, sr, sc);
		Input_convert(destination, dr, dc);
		if (!is_Current_Player_Piece(sr, sc))
		{
			showMessage("    NOT YOUR PIECE!          ", 12);
			continue;
		}
		PIECE* p = b.get_piece(sr, sc);
		if (p == nullptr)
		{
			showMessage("    EMPTY LOCATION!          ", 12);
			continue;
		}
		if (!p->isValidMove(sr, sc, dr, dc, &b))
		{
			showMessage("    INVALID MOVE!            ", 12);
			continue;
		}
		if (!b.check_safety(sr, sc, dr, dc, current_turn))
		{
			showMessage("  MOVE PUTS YOU IN CHECK!    ", 12);
			continue;
		}
		b.movepiece(sr, sc, dr, dc);
		if (b.is_King_Alive() == false)
		{

			if (current_turn == WHITE)
			{
				showMessage("  GAME OVER! WHITE WINS    ", 12);
			}
			else
			{
				showMessage("  GAME OVER! BLACK WINS    ", 12);
			}
			break;
		}
		if (current_turn == WHITE)
		{
			enemyking = BLACK;
		}
		else
		{
			enemyking = WHITE;
		}
		if (b.is_Check(enemyking))
		{
			if (b.is_Check_Mate(enemyking))
			{
				if (current_turn == WHITE)
				{
					showMessage("  CHECKMATE! WHITE WINS!     ", 10);
				}
				else
				{
					showMessage("  CHECKMATE! BLACK WINS!     ", 10);
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
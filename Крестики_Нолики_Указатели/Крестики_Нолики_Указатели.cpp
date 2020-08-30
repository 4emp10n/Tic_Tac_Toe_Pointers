//Dziuba Aleksandr Tic_tac_toe_PointerVersion
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>

using namespace std;

const char X = 'X';
const char O = 'O';
const char EMPTY = ' ';
const char TIE = 'T';
const char NO_ONE = 'N';

void Instructions();
char AskYesNo(string question);
int AskNumber(string question, int ihight, int low = 0);
char HumanPiece();
char Opponent(char piece);
void DisplayBoard(const vector<char>* const board);
char Winner(const vector<char>* const board);
bool IsLegal(int t, const vector <char>* const board);
int HumanMove(const vector<char>* const board, char human);
int ComputerMove(vector<char> board, char computer);
void AnnounceWinner(char winner, char computer, char human);



int main()
{
	int move;
	const int NUM_SQUERES = 9;
	vector <char> board(NUM_SQUERES, EMPTY);

	Instructions();

	char human = HumanPiece();
	char computer = Opponent(human);
	char turn = X;

	DisplayBoard(&board);

	while (Winner(&board) == NO_ONE)
	{
		if (turn == human)
		{
			move = HumanMove(&board, human);
			board[move] = human;
		}
		else
		{
			move = ComputerMove(board, computer);
			board[move] = computer;
		}

		DisplayBoard(&board);

		turn = Opponent(turn);
	}
	AnnounceWinner(Winner(&board), computer, human);
	return 0;
}

void Instructions()
{
	cout << "Welcome to the ultimate man-machine showdown: Tic-Tac-Toe.\n";
	cout << "--where human brain is pit against silicon processor\n\n";
	cout << "Make your move known by entering a number. 0-8. The number\n";
	cout << "corresponds to the desired board position, as illustrated:\n\n";
	cout << "0 | 1 | 2\n";
	cout << "3 | 4 | 5\n";
	cout << "6 | 7 | 8\n\n";
	cout << "Prepare yourself, human.The battle is about to begin\n\n";
}

char AskYesNo(string question)
{
	char response;

	do
	{
		cout << question << " (y/n): ";
		cin >> response;
	} while (response != 'y' && response != 'n');
	return response;
}


int AskNumber(string question, int high, int low)
{
	int number;
	do
	{
		cout << question << " (" << low << " - " << high << "): ";
		cin >> number;
	} while (number > high || number < low);
	return number;
}

char HumanPiece()
{
	char go_first = AskYesNo("Do you require the first move?");
	if (go_first == 'y')
	{
		cout << "\nThen take the first move. You will need it.\n";
		return X;
	}
	else
	{
		return O;
	}
}

char Opponent(char piece)
{
	if (piece == X)
	{
		return O;
	}
	else
	{
		return X;
	}
}

void DisplayBoard(const vector<char>* const board)
{
	cout << "\n\t" << (*board)[0] << " | " << (*board)[1] << " | " << (*board)[2];
	cout << "\n\t" << "--------";
	cout << "\n\t" << (*board)[3] << " | " << (*board)[4] << " | " << (*board)[5];
	cout << "\n\t" << "--------";
	cout << "\n\t" << (*board)[6] << " | " << (*board)[7] << " | " << (*board)[8];
	cout << "\n\n";
}

char Winner(const vector<char>* const board)
{
	const int WINNING_ROWS[8][3] =
	{ {0,1,2},
	{3,4,5},
	{6,7,8},
	{0,3,6},
	{1,4,7},
	{2,5,8},
	{0,4,8},
	{2,4,6} };

	const int TOTAL_ROWS = 8;

	for (int row = 0; row < TOTAL_ROWS; ++row)
	{
		if (( (*board)[WINNING_ROWS[row][0]] != EMPTY) &&
			( (*board)[WINNING_ROWS[row][0]] == (*board)[WINNING_ROWS[row][1]]) &&
			( (*board)[WINNING_ROWS[row][1]] == (*board)[WINNING_ROWS[row][2]]))
		{
			return (*board)[WINNING_ROWS[row][0]];
		}
	}
	if (count(board->begin(), board->end(), EMPTY) == 0)
	{
		return TIE;
	}

	return NO_ONE;
}

inline bool IsLegal(int move, const vector<char>* const board)
{
	return ( (*board)[move] == EMPTY);
}

int HumanMove(const vector<char>* const board, char human)
{
	int move = AskNumber("Where will you move?", (board->size() - 1));

	while (!IsLegal(move, board))
	{
		cout << "\nThat square is already occupeid< foolish human.\n";
		move = AskNumber("Where will you move?", board->size() - 1);
	}
	cout << "Fine...\n";
	return move;
}

int ComputerMove(vector<char> board, char computer)
{
	unsigned int move = 0;
	bool found = false;
	while (!found && move < board.size())
	{
		if (IsLegal(move, &board))
		{
			board[move] = computer;
			found = Winner(&board) == computer;
			board[move] = EMPTY;
		}
		if (!found)
		{
			++move;
		}
	}

	if (!found)
	{
		move = 0;
		char human = Opponent(computer);
		while (!found && move < board.size())
		{
			if (IsLegal(move, &board))
			{
				board[move] = human;
				found = Winner(&board) == human;
				board[move] = EMPTY;
			}
			if (!found)
			{
				++move;
			}
		}
	}

	if (!found)
	{
		move = 0;
		unsigned int i = 0;
		const int BEST_MOVES[] = { 4, 0, 2, 6, 8, 1, 3, 5, 7 };

		while (!found && i < board.size())
		{
			move = BEST_MOVES[i];
			if (IsLegal(move, &board))
			{
				found = true;
			}
			++i;
		}
	}
	cout << "I shall take square number " << move << endl;
	return move;
}

void AnnounceWinner(char winner, char computer, char human)
{
	if (winner == computer)
	{
		cout << winner << "'s won\n";
		cout << "As I predicted, human. I am triumphant once more -- proof\n";
		cout << "that computer's are superior to humans in all regards\n";
	}
	else if (winner == human)
	{
		cout << winner << "'s won\n";
		cout << "No, no! It cannot be! Somehow you triced me, human.\n";
		cout << "But never again! I, the computer so swear it!\n";
	}
	else
	{
		cout << "It's a tie!\n";
		cout << "You were most lucky human and somhow managed to tie me.\n";
		cout << "Celebrate... for this the best you will ever acheive.\n";
	}
}
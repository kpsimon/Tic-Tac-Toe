//Keoni Simon
//Tic Tac Toe
//Goals:
//	1. Display in console.
//	2. Multiplayer mode.
//	3. AI for singleplayer using different algorithms. (MINMAX)
// 2-24-20


//TODO:
/*
* 1. Keep track of visited and progress game.		x
* 2. Change gamemode based on initial user input.	X
* 3. Implement minmax AI for single player.			X
* 4. Value check inputs at all points.				X
*/

#include <iostream>
#include <sstream>
#include <limits>
#include <set>
#include <utility>
#include <math.h>
#include <unistd.h>

using namespace std;

class Board
{
		int board[9];
		int winner;

	public:
		Board()
		{
			for(int i = 0; i < 9; i++)
			{
				board[i] = i+3;
			}
			winner = -1;
		}

		Board(int _board[])
		{
			for(int i = 0; i < 9; i++)
			{
				board[i] = _board[i];
			}
		}

		int* get_board()
		{
			return board;
		}

		bool is_winner()
		{
			if(board[0] == board[1] && board[0] == board[2] && board[1] == board[2])
			{
				winner = board[0];
				return true;
			}
			else if(board[3] == board[4] && board[3] == board[5] && board[4] == board[5])
			{
				winner = board[3];
				return true;
			}
			else if(board[6] == board[7] && board[6] == board[8] && board[7] == board[8])
			{
				winner = board[6];
				return true;
			}
			else if(board[0] == board[3] && board[0] == board[6] && board[3] == board[6])
			{
				winner = board[0];
				return true;
			}
			else if(board[1] == board[4] && board[1] == board[7] && board[4] == board[7])
			{
				winner = board[1];
				return true;
			}
			else if(board[2] == board[5] && board[2] == board[8] && board[5] == board[8])
			{
				winner = board[2];
				return true;
			}
			else if(board[0] == board[4] && board[0] == board[8] && board[4] == board[8])
			{
				winner = board[0];
				return true;
			}
			else if(board[2] == board[4] && board[2] == board[6] && board[4] == board[6])
			{
				winner = board[2];
				return true;
			}
			else
			{
				return false;
			}
		}

		bool is_full()
		{
			int count = 0;
			for(int grid_val : board)
			{
				if(grid_val == 1 || grid_val == 2)
				{
					count++;
				}
			}

			if(count == 9)
			{
				return true;
			}
			else
			{
				return false;
			}
		}

		string convert_board_value(int val)
		{
			if(val == 1)
			{
				return "X";
			}
			else if (val == 2)
			{
				return "O";
			}
			else
			{
				return " ";
			}
		}

		void update_board(int player, int location)
		{
			board[location-1] = player;
		}

		void display_board()
		{
			cout << "\n       |       |              " << endl;
			cout << "   " << convert_board_value(board[0]) << "   |" <<"   " << convert_board_value(board[1]) << "   |" <<"   " << convert_board_value(board[2]) << "   " << endl;
			cout << "_______|_______|_______" << endl;
			cout << "       |       |              " << endl;
			cout << "   " << convert_board_value(board[3]) << "   |" <<"   " << convert_board_value(board[4]) << "   |" <<"   " << convert_board_value(board[5]) << "   " << endl;
			cout << "_______|_______|_______" << endl;
			cout << "       |       |              " << endl;
			cout << "   " << convert_board_value(board[6]) << "   |" <<"   " << convert_board_value(board[7]) << "   |" <<"   " << convert_board_value(board[8]) << "   " << endl;
			cout << "       |       |       " << endl;
			cout << endl;
		}

		int get_winner()
		{
			return winner;
		}

};

int game_intro();
void game_play(int game_mode);
void game_multiplayer();
void game_singleplayer();
bool set_contains_val(int val, set<int> visited);
int minmax(Board game_board, int depth, int current_player);

int main ()
{
	//introduce game settings, rules, and options
	//allow user to select from either single or multiplayer mode
	int mode = game_intro();

	game_play(mode);
}

int game_intro()
{
	cout << "Let's Play Tic-Tac-Toe" << endl;
	cout << "======================\n" << endl;


	int game_mode = -1;

	while(!(game_mode == 1 || game_mode == 2))
	{
		cout << "Enter 1 for singleplayer." << endl;
		cout << "Enter 2 for multiplayer." << endl;
		cout << "Mode: ";

		while(!(cin >> game_mode))
		{
			cout << "Invalid input, please try again:";
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
		}
		cout << endl;
	}

	if(game_mode == 1)
	{
		cout << "You have chosen singleplayer." << endl;
	}
	else
	{
		cout << "You have chosen multiplayer." << endl;
	}

	cout << "Player 1: X" << endl;
	cout << "Player 2: O" << endl;

	cout << "The format of the grid is:" << endl;
	cout << "       |        |        " << endl;
	cout << "   1   |    2   |    3   " << endl;
	cout << "_______|________|________" << endl;
	cout << "       |        |        " << endl;
	cout << "   4   |    5   |    6   " << endl;
	cout << "_______|________|________" << endl;
	cout << "       |        |        " << endl;
	cout << "   7   |    8   |    9   " << endl;
	cout << "       |        |        " << endl;


	return game_mode;
}

void game_play(int game_mode)
{
	if(game_mode == 1)
	{
		game_singleplayer();
	}
	else
	{
		game_multiplayer();
	}
}

void game_multiplayer()
{
	string continue_game = "Y";
	while (continue_game == "Y")
	{
		Board game_board;
		int player_move = -1;
		set<int> visited;

		int current_player = -1;
		while(!(current_player == 1 || current_player == 2))
		{
			cout << "Which player takes the first turn, 1 or 2?:";
			while(!(cin >> current_player))
			{
				cout << "Invalid input, please try again:";
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
			}
		}

		while(!game_board.is_winner() && !game_board.is_full())
		{
			//take player move
			while(!set_contains_val(player_move, visited))
			{
				cout << "Which location does player " << current_player << " wish to mark?:";
				while(!(cin >> player_move))
				{
					cout << "Invalid input, please try again:";
					cin.clear();
					cin.ignore(numeric_limits<streamsize>::max(), '\n');
				}

				if(set_contains_val(player_move, visited) || (player_move < 1 || player_move > 9))
				{
					cout << "\n### Spot already marked or invalid input. ###\n" << endl;
					player_move = -1;
				}
				else
				{
					visited.insert(player_move);
				}
			}

			//update and display board
			game_board.update_board(current_player, player_move);
			game_board.display_board();

			//switch current player
			if(current_player == 1)
			{
				current_player = 2;
			}
			else if (current_player == 2)
			{
				current_player = 1;
			}

			//reset player move
			player_move = -1;

		}

		if(game_board.is_winner())
		{
			cout << "Player " << game_board.get_winner() << " wins the game!" << endl;
		}
		else if (game_board.is_full())
		{
			cout << "Game board is full with no winners. Better luck next time!" << endl;
		}

		cout << "Continue playing, Y or N?:";
		cin >> continue_game;
	}

	cout << "\nThanks for playing!" << endl;
}

void game_singleplayer()
{
	string continue_game = "Y";
	while(continue_game == "Y")
	{
		Board game_board;
		int player_move = -1;
		set<int> visited;

		// WHILE LOOP: Control whole game and allow for multiple games played.
		int current_player = -1;
		while(!(current_player == 1 || current_player == 2))
		{
			cout << "Which player takes the first turn, 1(PLAYER) or 2(AI)?:";
			while(!(cin >> current_player))
			{
				cout << "Invalid input, please try again:";
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
			}
		}
		// WHILE LOOP: Allow player to make move and update board.
		//			   Alternate between players as game progresses.
		while(!game_board.is_winner() && !game_board.is_full())
		{
			// Player 1 (HUMAN) takes player move, updates board, and updates visited spots.
			if(current_player == 1)
			{
				//take player move
				while(!set_contains_val(player_move, visited))
				{
					cout << "Which location does player " << current_player << " wish to mark?:";
					while(!(cin >> player_move))
					{
						cout << "Invalid input, please try again:";
						cin.clear();
						cin.ignore(numeric_limits<streamsize>::max(), '\n');
					}

					if(set_contains_val(player_move, visited) || (player_move < 1 || player_move > 9))
					{
						cout << "\n### Spot already marked or invalid input. ###\n" << endl;
						player_move = -1;
					}
					else
					{
						visited.insert(player_move);
					}
				}

				game_board.update_board(current_player, player_move);
			}
			// Player 2 (AI) calculates best score of possible moves using minmax, updates board and visited spots.
			else
			{
				// ###	AI PLAYER MIN MAX  ###
				int high_score = -INFINITY;
				int best_move;
				for(int i = 0; i < 9; i++)
				{
					if(!set_contains_val(i+1,visited))
					{
						game_board.update_board(current_player, i+1);
						// int score = minmax(game_board.get_board(), visited, current_player);
						int score = minmax(game_board, 0, 1);

						game_board.update_board(i+3, i+1);

						if(score > high_score)
						{
							high_score = score;
							best_move = i+1;
						}
					}
				}

				usleep(1500000);

				cout << "Player 2 has chosen location " << best_move << "." << endl;
				game_board.update_board(current_player, best_move);
				visited.insert(best_move);
			}

			// BELOW: Display board, alternate player, and check for winner.

			game_board.display_board();

			//switch current player
			if(current_player == 1)
			{
				current_player = 2;
			}
			else if (current_player == 2)
			{
				current_player = 1;
			}

			//reset player move
			player_move = -1;

			//check for winner
			if(game_board.is_winner())
			{
				cout << "Player " << game_board.get_winner() << " wins the game!" << endl;
			}
			else if (game_board.is_full())
			{
				cout << "Game board is full with no winners. Better luck next time!" << endl;
			}
		}

		//OUTSIDE GAME LOOP: continue play or not
		cout << "Continue playing, Y or N?:";
		cin >> continue_game;
	}

	cout << "\nThanks for playing!" << endl;
}

int minmax(Board game_board, int depth, int current_player)
{
	if(game_board.is_winner() && game_board.get_winner() == 2)
	{
		return 10 - depth;
	}
	else if (game_board.is_winner() && game_board.get_winner() == 1)
	{
		return -20 + depth;
	}
	else if(!game_board.is_winner() && game_board.is_full())
	{
		return 0;
	}

	//MAXIMIZING
	if(current_player == 2)
	{
		int score = -10;
		for(int i = 0; i < 9; i++)
		{
			if(game_board.get_board()[i] == i+3)
			{
				//Add move to board.
				game_board.update_board(current_player,i+1);

				//Calculate score for updated board.
				int score_for_move = minmax(game_board.get_board(), depth + 1, 1);

				//Remove move from board.
				game_board.update_board(i+3,i+1);

				//Check if new high score.
				if(score_for_move > score)
				{
					score = score_for_move;
				}
			}
		}
		return score;
	}
	//MINIMIZING
	else
	{
		int score = 10;
		for(int i = 0; i < 9; i++)
		{
			if(game_board.get_board()[i] == i+3)
			{
				//Add move to board.
				game_board.update_board(current_player,i+1);

				//Calculate score for updated board.
				int score_for_move = minmax(game_board.get_board(), depth + 1, 2);

				//Remove move from board.
				game_board.update_board(i+3,i+1);

				//Check if new high score.
				if(score_for_move < score)
				{
					score = score_for_move;
				}
			}
		}
		return score;
	}
}

bool set_contains_val(int val, set<int> visited)
{
	for(auto element : visited)
	{
		if(element == val)
		{
			return true;
		}
	}
	return false;
}


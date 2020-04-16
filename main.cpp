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
* 3. Implement minmax AI for single player.
* 4. Value check inputs at all points.
*/

#include <iostream>
#include <sstream>
#include <limits>
#include <set>
#include <math.h>

using namespace std;

class Board 
{
		int board[9];
		int winner;

	public:
		Board()
		{
			for(int i = 0; i < 10; ++i)
			{
				board[i] = i+3;
			}
			winner = -1;
		}

		int[] get_board()
		{
			return & board;
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
int best_move(Board &game_board, int current_player);
int minimax(Board &game_board, int depth, bool maximizing, int current_player);

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
		int ai_move = -1;
		set<int> visited;

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

		while(!game_board.is_winner() && !game_board.is_full())
		{
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
			else
			{
				// ###	AI PLAYER MIN MAX  ###
				ai_move = best_move(&game_board.board, current_player);
				game_board.update_board(current_player, ai_move);

			}

		}

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
		ai_move = -1;
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

int best_move(Board &game_board, int current_player)
{
	int best_score = -INFINITY;
	int move;
	int temp;
	for(int i = 0; i < 9; i++)
	{
		if(game_board.board[i] != 0 && game_board.board[i] != 1)
		{
			temp = game_board.board[i];
			game_board.board[i] = current_player;
		}
		int score = minimax(&game_board, depth, false, current_player);
		game_board.board[i] = temp;
		if(score > best_score)
		{
			best_score = score;
			move = i;
		}
	}
	game_board.board[move] = current_player;
}

int minimax(Board &game_board, int depth, bool maximizing, int current_player)
{
	//Check if winner exists
	if(game_board.is_winner())
	{
		if(game_board.winner == current_player)
		{
			return 1;
		}
		else 
		{
			return 0;
		}
	}

	if(maximizing)
	{
		int best_score = -INFINITY;
		for(int i = 0; i < 9; i++)
		{
			if(game_board.board[i] != 0 && game_board.board[i] != 1)
			{
				temp = game_board.board[i];
				game_board.board[i] = current_player;
			}
			int score = minimax(&game_board, depth+1, false, current_player%2+1);
			game_board.board[i] = temp;
			if(score > best_score)
			{
				best_score = score;
				move = i;
			}
		}
	}
	else
	{
		int best_score = -INFINITY;
		for(int i = 0; i < 9; i++)
		{
			if(game_board.board[i] != 0 && game_board.board[i] != 1)
			{
				temp = game_board.board[i];
				game_board.board[i] = current_player;
			}
			int score = minimax(&game_board, depth+1, true, current_player%2+1);
			game_board.board[i] = temp;
			if(score < best_score)
			{
				best_score = score;
				move = i;
			}
		}
	}
	return best_score;
}

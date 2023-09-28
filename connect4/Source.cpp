# include <iostream>
# include <string>
using namespace std;

const int dimen_y = 6;
const int dimen_x = 7;

void draw_board(int board[dimen_y][dimen_x]) {
	string header = " ";
	for (int i = 0; i < dimen_x; ++i) {
		header += to_string(i);
		header += " ";
	};
	cout << header << endl;
	for (int y_point = dimen_y - 1; y_point >= 0; --y_point) {
		string line = "|";
		for (int x_point = 0; x_point < dimen_x; ++x_point) {
			if (board[y_point][x_point] == 2) {
				line += 'X';
			}
			else if (board[y_point][x_point] == 1) {
				line += 'O';
			}
			else {
				line += ' ';
			};
			line += '|';
		};
		cout << line << endl;
	};
};

int next_player(int player) {
	int new_player = (player % 2) + 1;
	cout << "It is Player " << new_player << "'s turn." << endl;
	return new_player;
};

int check_in(int board[dimen_y][dimen_x], int start_x, int start_y, int player, int move[2]) {
	int check_x = start_x;
	int check_y = start_y;
	int tot = 0;
	for (int tot = 0; tot < max(dimen_y, dimen_x) + 2; ++tot) {
		check_x += move[0];
		check_y += move[1];
		if (0 > check_y || check_y >= dimen_y) {
			return tot;
		};
		if (0 > check_x || check_x >= dimen_x) {
			return tot;
		};
		if (board[check_y][check_x] != player) {
			return tot;
		};
	};
	return tot;
};

bool won_game(int board[dimen_y][dimen_x], int start_x, int start_y, int player) {
	int accum[4] = { 0, 0, 0, 0 };
	int dir[8][2] = {
		{0, 1},
		{1, 1},
		{1, 0},
		{1, -1},
		{0, -1},
		{-1, -1},
		{-1, 0},
		{-1, 1}
	};
	for (int i = 0; i < 8; ++i) {
		accum[i % 4] += check_in(board, start_x, start_y, player, dir[i]);
		if (accum[i % 4] >= 3) {
			return true;
		};
	};
	return false;
};

int game() {
	int board[dimen_y][dimen_x];
	int placed[dimen_x];
	for (int i = 0; i < dimen_x; ++i) {
		placed[i] = 0;
	};
	char input;
	int player;
	int place;
	cout << "Should player 2 go first? (Y/N) ";
	cin >> input;
	switch (input) {
		case 'Y':
			cout << "Player 2 going first." << endl;
			player = 2;
			break;
		case 'N':
			cout << "Player 1 going first." << endl;
			player = 1;
			break;
		default:
			cout << "Invalid input.  Player 1 going first." << endl;
			player = 1;
			break;
	};
	draw_board(board);
	for (int i = 0; i < dimen_y * dimen_x; ++i) {
		cout << "Turn " << i << endl;
		while (true) {
			cout << "Player " << player << " move: ";
			cin >> place;
			if (0 <= place && place < dimen_x) {
				if (placed[place] < dimen_y) {
					break;
				} else {
					cout << "Column is full." << endl;
				};
			}
			else {
				cout << "Not in range." << endl;
			};
		};
		int place_y = placed[place];
		++placed[place];
		board[place_y][place] = player;
		draw_board(board);
		if (won_game(board, place, place_y, player)) {
			return (player - 1) * 2;
		};
		player = next_player(player);
	};
	return 1;
};

int main() {
	int wins[3] = { 0, 0, 0 }; //0 is player 1, 1 is ties, 2 is player 2
	char cont = 'Y';
	while (cont == 'Y') {
		++wins[game()];
		cout << "Player 1 has won " << wins[0] << " times.\n";
		cout << "Player 2 has won " << wins[2] << " times.\n";
		cout << "You have tied " << wins[1] << " times.\n";
		cout << "Continue? (Y/N) ";
		cin >> cont;
	};
	return -1;
};
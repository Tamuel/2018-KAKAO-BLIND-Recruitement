#include <iostream>
#include <vector>
#include <string>
#define _x first
#define _y second

using namespace std;

int main() {
	int m, n;
	vector<string> board;
	vector<pair<int, int>> offsets = { {0, 1}, {1, 0}, {1, 1} };

	cin >> m >> n;
	board.resize(m);
	for (int i = 0; i < m; i++)
		cin >> board[i];
	
	bool stop = false;
	int nBreaks = 0;
	while (!stop) {
		vector<vector<int>> checker(m, vector<int>(n));
		stop = true;
		// Break
		for (int i = 0; i < m - 1; i++) {
			for (int j = 0; j < n - 1; j++) {
				if (board[i][j] != ' ') {
					bool check = true;
					char current = board[i][j];
					for (auto o : offsets)
						if (current != board[i + o._y][j + o._x]) {
							check = false;
							break;
						}

					if (check) {
						stop = false;
						checker[i][j] = 1;
						for (auto o : offsets)
							checker[i + o._y][j + o._x] = 1;
					}
				}
			}
		}
		for (int i = 0; i < m; i++)
			for (int j = 0; j < n; j++)
				if (checker[i][j] == 1) {
					nBreaks++;
					board[i][j] = ' ';
				}

		// Down
		for (int i = m - 2; i >= 0; i--) {
			for (int j = 0; j < n; j++) {
				if (board[i][j] != ' ') {
					int k = i + 1;
					while (k < m && board[k][j] == ' ') k++;
					board[k - 1][j] = board[i][j];
					if (i != k - 1) board[i][j] = ' ';
				}
			}
		}
	}

	cout << nBreaks << endl;

	return 0;
}

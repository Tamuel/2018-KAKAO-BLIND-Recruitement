#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <deque>
#include <algorithm>
#include <functional>
#include <iomanip>

using namespace std;

// 2018 1st 5hour
// 6. «¡∑ª¡Ó4∫Ì∑œ
int friends4block() {
	int m = 6, n = 6;
	vector<string> board = {
		"TTTANT",
		"RRFACC",
		"RRRFCC",
		"TRRRAA",
		"TTMMMF",
		"TMMTTJ"
	};
	vector<vector<int>> neighbor = {
		{0, 1},
		{1, 0},
		{1, 1}
	};

	int count = 0;

	while (true) {
		cout << "===================" << endl;
		for (int i = 0; i < m; i++) {
			for (int j = 0; j < n; j++) {
				cout << board[i][j];
			}
			cout << endl;
		}

		// Check blocks
		vector<vector<int>> check(m, vector<int>(n, 0));
		for (int i = 0; i < m - 1; i++) {
			for (int j = 0; j < n - 1; j++) {
				int basis = board[i][j];
				if (basis == ' ')
					continue;
				bool broken = true;
				vector<vector<int>>::iterator n;
				for (n = neighbor.begin(); n != neighbor.end(); n++) {
					if (board[i + (*n)[0]][j + (*n)[1]] != basis) {
						broken = false;
						break;
					}
				}
				if (broken) {
					check[i][j] = 1;
					for (n = neighbor.begin(); n != neighbor.end(); n++)
						check[i + (*n)[0]][j + (*n)[1]] = 1;
				}
			}
		}

		int t_count = 0;
		// Calculate count
		for (int i = 0; i < m; i++)
			for (int j = 0; j < n; j++)
				if (check[i][j] == 1)
					t_count++;
		if (t_count == 0)
			break;
		else
			count += t_count;

		// Drop blocks
		for (int j = 0; j < n; j++) {
			for (int i = m - 1, k = m - 1; i >= 0;) {
				if (check[i][j] == 1) {
					k--;
					if (k < 0) {
						board[i][j] = ' ';
						i--;
					}
					else if (check[k][j] == 0) {
						board[i][j] = board[k][j];
						board[k][j] = ' ';
						check[k][j] = 1;
						i--;
					}
				}
				else {
					i--;
					k--;
				}
			}
		}
	}

	cout << count << endl;
	return count;
}


int main() {
	friends4block();

	return 0;
}
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
// 2. 다트게임
void dart_game() {
	string input = "1D2S3T*";
	vector<string> splits;

	string temp = "";
	for (int i = 0; i < input.size(); i++) {
		if (input[i] >= '0' && input[i] <= '9')
			temp += input[i];
		else {
			if (temp.size() != 0)
				splits.push_back(temp);
			splits.push_back(string(1, input[i]));
			temp = "";
		}
	}

	int score[3] = { 0, 0, 0 };
	int score_index = -1;
	for (int i = 0; i < splits.size(); i++) {
		if (splits[i][0] >= '0' && splits[i][0] <= '9')
			score[++score_index] = stoi(splits[i]);
		else {
			switch (splits[i][0]) {
			case '#':
				score[score_index] = -score[score_index];
				break;
			case '*':
				score[score_index] *= 2;
				if (score_index - 1 >= 0)
					score[score_index - 1] *= 2;
				break;
			case 'S':
				break;
			case 'D':
				score[score_index] = pow(score[score_index], 2);
				break;
			case 'T':
				score[score_index] = pow(score[score_index], 3);
				break;
			}
		}
	}

	for (int i = 0; i < 3; i++)
		cout << score[i] << endl;

	cout << score[0] + score[1] + score[2] << endl;
}

int main() {
	dart_game();
	return 0;
}
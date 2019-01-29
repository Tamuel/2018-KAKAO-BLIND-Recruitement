#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <deque>
#include <algorithm>
#include <functional>
#include <iomanip>

using namespace std;

// 3. 파일명 정렬
void filename_sorting() {
	/*vector<string> input = {
		"img12.png",
		"img2.JPG",
		"IMG01.GIF",
		"img10.png",
		"img02.png",
		"img1.png"
	};*/
	vector<string> input = {
		"F-5 Freedom Fighter",
		"B-50 Superfortress",
		"A-10 Thunderbolt II",
		"F-14 Tomcat"
	};
	typedef pair<string, int> str_int_pair;
	multimap<str_int_pair, string> augmented;

	for (int i = 0; i < input.size(); i++) {
		int number_start = 0;
		int number_end = 0;
		string head = "";
		for (int j = 0; j < input[i].size(); j++) {
			if (input[i][j] <= '9' && input[i][j] >= '0') {
				number_start = j;
				break;
			}
			else {
				if (input[i][j] >= 'a' && input[i][j] <= 'z')
					head += input[i][j];
				else if (input[i][j] >= 'A' && input[i][j] <= 'Z')
					head += char(input[i][j] - ('A' - 'a'));
				else
					head += input[i][j];
			}
		}
		for (int j = number_start + 1; j < input[i].size(); j++) {
			if (!(input[i][j] <= '9' && input[i][j] >= '0')) {
				number_end = j;
				break;
			}
		}

		int number = stoi(input[i].substr(number_start, number_end - number_start));

		augmented.insert(pair<str_int_pair, string>(str_int_pair(head, number), input[i]));
	}

	for (multimap<str_int_pair, string>::iterator i = augmented.begin(); i != augmented.end(); i++) {
		cout << i->first.first << "|" << i->first.second << ", " << i->second << endl;
	}
}

int main() {
	filename_sorting();

	return 0;
}
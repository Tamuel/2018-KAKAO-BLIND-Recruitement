#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <deque>
#include <algorithm>
#include <functional>
#include <iomanip>

using namespace std;

// 2. æ–√‡
void compress() {
	string input = "KAKAO";
	map<string, int> dict;
	vector<int> output;

	for (int i = 'A'; i <= 'Z'; i++) {
		string temp = "";
		dict.insert(pair<string, int>(temp + char(i), i - 'A' + 1));
	}

	for (int i = 0; i < input.size(); i++) {
		string temp = "";
		temp += input[i];
		for (int j = i + 1; j < input.size(); j++) {
			if (dict.find(temp + input[j]) != dict.end()) {
				temp += input[j];
				i++;
			} else {
				output.push_back(dict[temp]);
				cout << temp << ", " << dict[temp] << endl;
				cout << "DICT " << temp + input[j] << endl;
				dict.insert(pair<string, int>(temp + input[j], dict.size() + 1));
				temp = "";
				break;
			}
		}
		if (temp.compare("") != 0)
			output.push_back(dict[temp]);
	}

	for (int i = 0; i < output.size(); i++)
		cout << output[i] << endl;
}

int main() {
	compress();

	return 0;
}
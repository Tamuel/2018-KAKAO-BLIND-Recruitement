#include <iostream>
#include <map>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;


int main() {
	int size = 26;
	map<string, int> dict;
	for (int i = 0; i < size; i++) {
		string t = " "; t[0] = 'A' + i;
		dict.insert({ t, i + 1 });
	}

	string input;
	cin >> input;

	vector<int> results;
	for (int i = 0; i < input.length();) {
		int sub = 1;
		while (i + sub <= input.length() && dict.find(input.substr(i, sub)) != dict.end()) sub++;
		results.push_back(dict[input.substr(i, sub - 1)]);
		dict.insert({ input.substr(i, sub), size + 1 });
		size++;
		i += sub - 1;
	}
	for (int r : results)
		cout << r << endl;

	return 0;
}

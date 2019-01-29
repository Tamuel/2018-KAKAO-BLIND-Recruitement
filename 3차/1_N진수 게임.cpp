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
// 2018 3rd 4hour
// 1. NÁø¼ö °ÔÀÓ
string encode(int decimal, int factor) {
	if (decimal == 0)
		return "0";

	string output = "";

	int current = decimal, remain;
	while (true) {
		if (current == 0)
			break;
		int temp = current % factor;
		char t = temp + '0';
		if (temp >= 10)
			t = (temp - 10) + 'A';

		output += t;
		current = int(current / factor);
	}

	string result;
	for (int i = output.size() - 1; i >= 0; i--)
		result += output[i];

	return result;
}
void n_factor() {
	// n Áø¹ý, m »ç¶÷ ¼ö, t ¾Æ¿ôÇ² °¹¼ö, p Æ©ºê ÀÚ¸®
	int n = 16, t = 16, m = 2, p = 1;
	vector<char> output;

	int index = 0;
	int current = 0;
	while (true) {
		string str = encode(current, n);
		
		for (int i = 0; i < str.size(); i++) {
			if (index % m == p - 1) {
				output.push_back(str[i]);
				if (output.size() == t)
					break;
			}
			index++;
		}
		if (output.size() == t)
			break;

		current++;
	}

	for (int i = 0; i < output.size(); i++)
		cout << output[i];

	cout << endl;
}

int main() {
	n_factor();

	return 0;
}
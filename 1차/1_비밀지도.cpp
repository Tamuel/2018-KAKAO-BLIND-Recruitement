#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <deque>
#include <algorithm>
#include <functional>
#include <iomanip>

using namespace std;

// 2018 1st
// 1. 비밀지도
string decimal_to_binary(int n, int decimal) {
	string result;
	result.resize(n);

	int count = n - 1;
	int next = decimal;
	int reminder;
	for (int i = n - 1; i >= 0; i--) {
		reminder = next % 2;
		if (next != 0)
			result[i] = to_string(reminder)[0];
		else
			result[i] = '0';
		next = (int)(next / 2);
	}

	return result;
}
void secret_map() {
	int n = 5;
	int arr1[] = { 9, 20, 28, 18, 11 };
	int arr2[] = { 30, 1, 21, 17, 28 };

	for (int i = 0; i < n; i++) {
		int out = arr1[i] | arr2[i];
		string result = decimal_to_binary(n, out);
		string output = "";
		for (int j = 0; j < n; j++) {
			if (result[j] == '0')
				output += " ";
			else
				output += "#";
		}
		cout << output << endl;
	}
}

int main() {
	secret_map();
	return 0;
}
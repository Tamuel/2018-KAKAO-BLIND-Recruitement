#include <iostream>
#include <string>

using namespace std;

string changeNumber(int num, int k) {
	if (num == 0) return "0";
	string output = "";
	
	while (num >= 1) {
		if (num % k < 10) output += (num % k) + '0';
		else output += (num % k - 10) + 'A';
		num /= k;
	}
	string reverse;
	for (int i = output.size() - 1; i >= 0; i--)
		reverse += output[i];

	return reverse;
}

int main() {
	int n, t, m, p;

	cin >> n >> t >> m >> p;
	p--;
	int current = 0;
	int count = 0;
	string results = "";
	while (results.length() < t) {
		string toNum = changeNumber(current++, n);
		for (int i = 0; i < toNum.size(); i++)
			if ((i + count) % m == p && results.length() < t) results += toNum[i];
		count += toNum.size();
	}

	cout << results << endl;

	return 0;
}

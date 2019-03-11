#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
	int N;
	cin >> N;
	vector<string> dict(N);

	for (int i = 0; i < N; i++)
		cin >> dict[i];

	sort(dict.begin(), dict.end());
	vector<int> count(N, 1);
	
	for (int i = 0; i < dict.size() - 1; i++) {
		if (dict[i].substr(0, count[i]) == dict[i + 1].substr(0, count[i])) {
			while (dict[i].substr(0, count[i]) == dict[i + 1].substr(0, count[i]) && dict[i].size() >= count[i])
				count[i]++;
			count[i + 1] = count[i];
			if (count[i] >= dict[i].size())
				count[i] = dict[i].size();
		}
		else {
			count[i + 1] = count[i];
			while (dict[i].substr(0, count[i + 1]) != dict[i + 1].substr(0, count[i + 1]) && count[i + 1] >= 0)
				count[i + 1]--;
			count[i + 1]++;
		}
	}

	int sum = 0;
	for (int c : count)
		sum += c;

	cout << sum << endl;

	return 0;
}

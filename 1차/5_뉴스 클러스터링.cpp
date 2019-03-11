#include <iostream>
#include <map>
#include <string>
#include <algorithm>

using namespace std;

void tolower(string& str) {
	for (int i = 0; i < str.length(); i++)
		if (str[i] <= 'Z' && str[i] >= 'A') str[i] += 'a' - 'A';
}

void makeStrMap(string& str, map<string, int>& strMap) {
	for (int i = 0; i < str.size() - 1; i++) {
		if (str[i] >= 'a' && str[i] <= 'z' && str[i + 1] >= 'a' && str[i + 1] <= 'z')
			if (!strMap.insert({ str.substr(i, 2), 1 }).second)
				strMap[str.substr(i, 2)]++;
	}
}

int main() {
	string str1;
	string str2;

	getline(cin, str1);
	getline(cin, str2);

	tolower(str1);
	tolower(str2);

	map<string, int> strMap1, strMap2;

	makeStrMap(str1, strMap1);
	makeStrMap(str2, strMap2);

	if (strMap1.size() == 0 && strMap2.size() == 0) {
		cout << 65536 << endl;
		return 0;
	}
	
	float uni = 0, inter = 0;
	map<string, int>::iterator iter1 = strMap1.begin(), iter2 = strMap2.begin();

	while (iter1 != strMap1.end() && iter2 != strMap2.end()) {
		if (iter1->first == iter2->first) {
			uni += max(iter1->second, iter2->second);
			inter += min(iter1->second, iter2->second);
			iter1++; iter2++;
		}
		else if (iter1->first > iter2->first) {
			uni += iter2->second;
			iter2++;
		}
		else {
			uni += iter1->second;
			iter1++;
		}
	}
	if (iter1 != strMap1.end())
		while (iter1 != strMap1.end()) uni += (iter1++)->second;
	if (iter2 != strMap2.end())
		while (iter2 != strMap2.end()) uni += (iter2++)->second;

	cout << int((inter / uni) * 65536) << endl;

	return 0;
}

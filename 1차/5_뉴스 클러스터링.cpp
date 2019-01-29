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
// 5. 뉴스 클러스터링
map<string, int> divide_string(string str, int sub_size) {
	map<string, int> division;
	for (int i = 0; i < str.size() - 1; i++) {
		string substring = str.substr(i, sub_size);
		bool check_str = true;
		for (int j = 0; j < sub_size; j++) {
			bool check_upper = substring[j] >= 'A' && substring[j] <= 'Z';
			bool check_lower = substring[j] >= 'a' && substring[j] <= 'z';
			if (!(check_upper || check_lower)) {
				check_str = false;
				break;
			}
			if (check_upper)
				substring[j] -= int('A' - 'a');
		}
		if (check_str && !division.insert(pair<string, int>(substring, 1)).second)
			division[substring]++;
	}

	return division;
}
int news_clustering() {
	string str1 = "E=M*C^2";
	string str2 = "e=m*c^2";

	int sub_size = 2;

	map<string, int> merge1, merge2;

	merge1 = divide_string(str1, sub_size);
	merge2 = divide_string(str2, sub_size);

	if (merge1.size() == 0 && merge2.size() == 0)
		return 1;
	
	int inter = 0, uni = 0, comparison;
	map<string, int>::iterator i = merge1.begin(), j = merge2.begin();
	while (true) {
		if (i == merge1.end() && j == merge2.end())
			break;

		if (i == merge1.end()) {
			uni += j->second;
			j++;
		}
		else if (j == merge2.end()) {
			uni += i->second;
			i++;
		}
		else {
			comparison = i->first.compare(j->first);
			if (comparison == 0) {
				inter += i->second < j->second ? i->second : j->second;
				uni += i->second > j->second ? i->second : j->second;
				i++;
				j++;
			}
			else if (comparison < 0) {
				uni += i->second;
				i++;
			}
			else if (comparison > 0) {
				uni += j->second;
				j++;
			}
		}
	}
	

	int result = int(65536 * inter / uni);
	cout << result << endl;
	return result;
}


int main() {
	news_clustering();

	return 0;
}
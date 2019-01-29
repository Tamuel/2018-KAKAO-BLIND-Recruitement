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
// 4. ¼ÅÆ²¹ö½º
void shuttle_bus() {
	int n = 10, t = 60, m = 45;
	vector<string> timetable = {
		"23:59", "23:59", "23:59", "23:59", "23:59", "23:59", "23:59", "23:59", "23:59", "23:59", "23:59", "23:59", "23:59", "23:59"
	};
	map<int, int> timetable_map; // [value, number of value]

	for (int i = 0; i < timetable.size(); i++) {
		int time = stoi(timetable[i].substr(0, 2)) * 60 + stoi(timetable[i].substr(3, 2));
		if (!timetable_map.insert(pair<int, int>(time, 1)).second)
			timetable_map[time]++;
	}

	int last = 0;
	map<int, int>::iterator j = timetable_map.begin();
	for (int i = 0; i < n; i++) {
		int end = 540 + i * t;
		int c_m = m;
		while (j != timetable_map.end()) {
			if (j->first <= end) {
				if (j->second > c_m) {
					j->second -= c_m;
					c_m = 0;
					last = j->first - 1;
					break;
				}
				else {
					c_m -= j->second;
					if (c_m > 0)
						last = j->first;
					else
						last = j->first - 1;
					j = timetable_map.erase(j);
				}
			}
			else break;
		}
		if (c_m > 0)
			last = end;

		cout << setw(2) << setfill('0') << (int)(last / 60) << ":" << setw(2) << setfill('0') << last % 60 << endl;
	}
}


int main() {
	shuttle_bus();

	return 0;
}
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
	int N;
	int n, t, m;
	map<int, int> timetable;

	cin >> N >> n >> t >> m;
	for (int i = 0; i < N; i++) {
		string temp;
		cin >> temp;
		
		int hour = stoi(temp.substr(0, 2));
		int minute = stoi(temp.substr(3, 2));

		if (!timetable.insert({ hour * 60 + minute, 1 }).second)
			timetable[hour * 60 + minute]++;
	}

	map<int, int>::iterator iter;
	int last = 0;
	for (int i = 0; i < n; i++) {
		int current = 9 * 60 + i * t;
		int cM = m;
		iter = timetable.begin();
		for (; iter != timetable.end() && cM > 0 && iter->first <= current;) {
			if (iter->second < cM) {
				last = iter->first;
				cM -= iter->second;
				iter = timetable.erase(iter);
			}
			else {
				last = iter->first - 1;
				cM -= iter->second;
				if (cM == 0) iter = timetable.erase(iter);
			}
		}
		if (cM > 0) last = current;
	}
	
	int hour = last / 60;
	int minute = last % 60;
	cout << (hour >= 10 ? to_string(hour) : "0" + to_string(hour)) << ":"
		<< (minute >= 10 ? to_string(minute) : "0" + to_string(minute)) << endl;
}


int main() {
	shuttle_bus();

	return 0;
}

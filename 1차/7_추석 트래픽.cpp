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
// 7. 추석 트래픽
void chuseok_traffic() {
	// 정렬 기준은 마지막 시간, 시작 순
	// 시작이 기준 + 1초 이하인 애들을 걸러내면 해당 범위에서 최대

	int time_out = 3 * 1000;
	vector<string> str = {
		"2016-09-15 20:59:57.421 0.351s",
		"2016-09-15 20:59:58.233 1.181s",
		"2016-09-15 20:59:58.299 0.8s",
		"2016-09-15 20:59:58.688 1.041s",
		"2016-09-15 20:59:59.591 1.412s",
		"2016-09-15 21:00:00.464 1.466s",
		"2016-09-15 21:00:00.741 1.581s",
		"2016-09-15 21:00:00.748 2.31s",
		"2016-09-15 21:00:00.966 0.381s",
		"2016-09-15 21:00:02.066 2.62s"
	};

	vector<long long> time_sort(str.size());

	for (int i = 0; i < str.size(); i++) {
		string end_time = str[i].substr(str[i].find(' ') + 1);
		string time = end_time.substr(end_time.find(' ') + 1);

		time = time.substr(0, time.size() - 1);
		end_time = end_time.substr(0, 12);
		
		int i_time = time_out - int(stof(time) * 1000);
		long long i_end = (stoi(end_time.substr(0,2)) * 3600 + stoi(end_time.substr(3,2)) * 60 + stof(end_time.substr(6, 6))) * 1000;

		time_sort[i] = i_end * 10000 + i_time;
	}

	sort(time_sort.begin(), time_sort.end());

	int max = 0;
	for (int i = 0; i < time_sort.size(); i++) {
		int count = 1;
		long long end_time_i = time_sort[i] / 10000;
		for (int j = i + 1; j < time_sort.size(); j++) {
			long long end_time_j = time_sort[j] / 10000;
			long long time_j = 3000 - (time_sort[j] - end_time_j * 10000);
			if (end_time_j - time_j <= end_time_i + 1000)
				count++;
			else
				break;
		}
		if (max < count)
			max = count;
	}

	cout << max << endl;
}

int main() {
	chuseok_traffic();

	return 0;
}
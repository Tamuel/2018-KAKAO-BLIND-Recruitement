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

// 2. 다트게임
void dart_game() {
	string input = "1D2S3T*";
	vector<string> splits;

	string temp = "";
	for (int i = 0; i < input.size(); i++) {
		if (input[i] >= '0' && input[i] <= '9')
			temp += input[i];
		else {
			if (temp.size() != 0)
				splits.push_back(temp);
			splits.push_back(string(1, input[i]));
			temp = "";
		}
	}

	int score[3] = { 0, 0, 0 };
	int score_index = -1;
	for (int i = 0; i < splits.size(); i++) {
		if (splits[i][0] >= '0' && splits[i][0] <= '9')
			score[++score_index] = stoi(splits[i]);
		else {
			switch (splits[i][0]) {
			case '#':
				score[score_index] = -score[score_index];
				break;
			case '*':
				score[score_index] *= 2;
				if (score_index - 1 >= 0)
					score[score_index - 1] *= 2;
				break;
			case 'S':
				break;
			case 'D':
				score[score_index] = pow(score[score_index], 2);
				break;
			case 'T':
				score[score_index] = pow(score[score_index], 3);
				break;
			}
		}
	}

	for (int i = 0; i < 3; i++)
		cout << score[i] << endl;

	cout << score[0] + score[1] + score[2] << endl;
}

// 3. 캐시
void cache() {
	int cacheSize = 0;
	vector<string> cities = {
		"Jeju",
		"Pangyo",
		"Seoul",
		"NewYork",
		"LA",
		"SanFrancisco",
		"Seoul",
		"Rome",
		"Paris",
		"Jeju",
		"NewYork",
		"Rome"
	};

	int cost = 0;
	deque<string> cache;
	for (int i = 0; i < cities.size(); i++) {
		cost += 5;
		for (deque<string>::iterator iter = cache.begin(); iter != cache.end(); iter++) {
			if (iter->compare(cities[i]) == 0) {
				cost -= 4;
				break;
			}
		}
		cache.push_back(cities[i]);
		if (cache.size() > cacheSize)
			cache.pop_front();
	}

	cout << cost << endl;
}

// 4. 셔틀버스
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

// 6. 프렌즈4블록
int friends4block() {
	int m = 6, n = 6;
	vector<string> board = {
		"TTTANT",
		"RRFACC",
		"RRRFCC",
		"TRRRAA",
		"TTMMMF",
		"TMMTTJ"
	};
	vector<vector<int>> neighbor = {
		{0, 1},
		{1, 0},
		{1, 1}
	};

	int count = 0;

	while (true) {
		cout << "===================" << endl;
		for (int i = 0; i < m; i++) {
			for (int j = 0; j < n; j++) {
				cout << board[i][j];
			}
			cout << endl;
		}

		// Check blocks
		vector<vector<int>> check(m, vector<int>(n, 0));
		for (int i = 0; i < m - 1; i++) {
			for (int j = 0; j < n - 1; j++) {
				int basis = board[i][j];
				if (basis == ' ')
					continue;
				bool broken = true;
				vector<vector<int>>::iterator n;
				for (n = neighbor.begin(); n != neighbor.end(); n++) {
					if (board[i + (*n)[0]][j + (*n)[1]] != basis) {
						broken = false;
						break;
					}
				}
				if (broken) {
					check[i][j] = 1;
					for (n = neighbor.begin(); n != neighbor.end(); n++)
						check[i + (*n)[0]][j + (*n)[1]] = 1;
				}
			}
		}

		int t_count = 0;
		// Calculate count
		for (int i = 0; i < m; i++)
			for (int j = 0; j < n; j++)
				if (check[i][j] == 1)
					t_count++;
		if (t_count == 0)
			break;
		else
			count += t_count;

		// Drop blocks
		for (int j = 0; j < n; j++) {
			for (int i = m - 1, k = m - 1; i >= 0;) {
				if (check[i][j] == 1) {
					k--;
					if (k < 0) {
						board[i][j] = ' ';
						i--;
					}
					else if (check[k][j] == 0) {
						board[i][j] = board[k][j];
						board[k][j] = ' ';
						check[k][j] = 1;
						i--;
					}
				}
				else {
					i--;
					k--;
				}
			}
		}
	}

	cout << count << endl;
	return count;
}

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


// 2018 3rd 4hour
// 1. N진수 게임
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
	// n 진법, m 사람 수, t 아웃풋 갯수, p 튜브 자리
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


// 2. 압축
void compress() {
	string input = "KAKAO";
	map<string, int> dict;
	vector<int> output;

	for (int i = 'A'; i <= 'Z'; i++) {
		string temp = "";
		dict.insert(pair<string, int>(temp + char(i), i - 'A' + 1));
	}

	//for (map<string, int>::iterator i = dict.begin(); i != dict.end(); i++)
	//	cout << i->first << ", " << i->second << endl;

	for (int i = 0; i < input.size(); i++) {
		string temp = "";
		temp += input[i];
		for (int j = i + 1; j < input.size(); j++) {
			if (dict.find(temp + input[j]) != dict.end()) {
				temp += input[j];
				i++;
			} else {
				output.push_back(dict[temp]);
				cout << temp << ", " << dict[temp] << endl;
				cout << "DICT " << temp + input[j] << endl;
				dict.insert(pair<string, int>(temp + input[j], dict.size() + 1));
				temp = "";
				break;
			}
		}
		if (temp.compare("") != 0)
			output.push_back(dict[temp]);
	}

	for (int i = 0; i < output.size(); i++)
		cout << output[i] << endl;
}


// 3. 파일명 정렬
void filename_sorting() {
	/*vector<string> input = {
		"img12.png",
		"img2.JPG",
		"IMG01.GIF",
		"img10.png",
		"img02.png",
		"img1.png"
	};*/
	vector<string> input = {
		"F-5 Freedom Fighter",
		"B-50 Superfortress",
		"A-10 Thunderbolt II",
		"F-14 Tomcat"
	};
	typedef pair<string, int> str_int_pair;
	multimap<str_int_pair, string> augmented;

	for (int i = 0; i < input.size(); i++) {
		int number_start = 0;
		int number_end = 0;
		string head = "";
		for (int j = 0; j < input[i].size(); j++) {
			if (input[i][j] <= '9' && input[i][j] >= '0') {
				number_start = j;
				break;
			}
			else {
				if (input[i][j] >= 'a' && input[i][j] <= 'z')
					head += input[i][j];
				else if (input[i][j] >= 'A' && input[i][j] <= 'Z')
					head += char(input[i][j] - ('A' - 'a'));
				else
					head += input[i][j];
			}
		}
		for (int j = number_start + 1; j < input[i].size(); j++) {
			if (!(input[i][j] <= '9' && input[i][j] >= '0')) {
				number_end = j;
				break;
			}
		}

		int number = stoi(input[i].substr(number_start, number_end - number_start));

		augmented.insert(pair<str_int_pair, string>(str_int_pair(head, number), input[i]));
	}

	for (multimap<str_int_pair, string>::iterator i = augmented.begin(); i != augmented.end(); i++) {
		cout << i->first.first << "|" << i->first.second << ", " << i->second << endl;
	}
}


// 4. 방금그곡
string recent_music() {
	string m = "ABC";
	vector<string> musicinfos = {
		"12:00,12:14,HELLO,C#DEFGAB",
		"13:00,13:05,WORLD,ABCDEF"
	};

	vector<pair<int, vector<string>>> dataset(musicinfos.size());
	vector<string> melody_vector;
	for (int i = 0; i < m.size(); i++) {
		if (i + 1 < m.size() && m[i + 1] == '#') {
			melody_vector.push_back(m.substr(i, 2));
			i++;
		}
		else {
			string t = "";
			melody_vector.push_back(t + m[i]);
		}
	}

	for (int i = 0; i < musicinfos.size(); i++) {
		int playtime;
		vector<string> repeat_melody;
		
		string begin = musicinfos[i].substr(0, 5);
		string end = musicinfos[i].substr(6, 5);
		string temp = musicinfos[i].substr(12);
		string name = temp.substr(0, temp.find(','));
		string melody = temp.substr(temp.find(',') + 1);

		int begin_hh, begin_mm, end_hh, end_mm;
		begin_hh = stoi(begin.substr(0, 2)) * 60;
		begin_mm = stoi(begin.substr(3, 2));;
		end_hh = stoi(end.substr(0, 2)) * 60;
		end_mm = stoi(end.substr(3, 2));

		playtime = (end_hh + end_mm) - (begin_hh + begin_mm);
		for (int i = 0; i < playtime; i++) {
			if (melody[(i + 1) % melody.size()] == '#') {
				repeat_melody.push_back(melody.substr(i % melody.size(), 2));
				i++;
			}
			else {
				string t = "";
				repeat_melody.push_back(t + melody[i % melody.size()]);
			}
		}
		repeat_melody.push_back(name);

		dataset[i] = pair<int, vector<string>>(playtime, repeat_melody);
	}

	sort(dataset.begin(), dataset.end(), greater<pair<int, vector<string>>>());

	for (int i = 0; i < dataset.size(); i++) {
		string temp;
		vector<string> current_melody = dataset[i].second;
		for (int j = 0; j < current_melody.size() - 1; j++) {
			if (current_melody[j].compare(melody_vector[0]) == 0) {
				temp += m[0];
				for (int k = j + 1; k < current_melody.size() - 1 && k - j < m.size(); k++) {
					if (current_melody[k].compare(melody_vector[k - j]) == 0)
						temp += m[k - j];
					else
						break;
				}
				if (temp.compare(m) == 0) {
					cout << dataset[i].second[dataset[i].second.size() - 1] << endl;
					return dataset[i].second[dataset[i].second.size() - 1];
				}
				else
					temp = "";
			}
		}
	}
}


// 5. 자동완성
class node {
private:
	bool root;
	char head;
	int n_childs;
	map<char, node> data;

public:
	node(char _head) {
		head = _head;
		root = false;
		n_childs = 0;
	}
	
	node() {
		root = true;
		n_childs = 0;
	}

	bool insert(string str) {
		n_childs++;
		if (str.size() == 0) {
			node new_node('/');
			data.insert(pair<char, node>('/', new_node));
			return false;
		}

		char new_head = str[0];

		if (data.find(new_head) != data.end()) { // Head 가 있을 경우
			data[new_head].insert(str.substr(1));
		}
		else { // Head 가 없을 경우
			node new_node(new_head);
			data.insert(pair<char, node>(new_head, new_node));
			data[new_head].insert(str.substr(1));
		}
		return true;
	}

	int size() {
		return data.size();
	}

	map<char, node> childs() {
		return data;
	}
	
	int num_childs() {
		return n_childs;
	}
};
int autocorrection() {
	vector<string> input = {
		"word",
		"war",
		"warrior",
		"world"
	};

	node root;

	// Make tree
	for (int i = 0; i < input.size(); i++)
		root.insert(input[i]);

	// Count
	int count_sum = 0;
	for (int i = 0; i < input.size(); i++) {
		string current = input[i] + '/';
		string in = "";
		in += input[i][0];
		int count = 1;
		node temp = root.childs()[current[0]];
		for (int j = 1; j < current.size(); j++) {
			if (current[j] == '/' && temp.childs().begin()->first == '/') {
				cout << count << endl;
				break;
			}
			else if (temp.num_childs() == 1){
				cout << count << endl;
				break;
			}
			else {
				temp = temp.childs()[current[j]];
				in += current[j];
				count++;
			}
		}
		cout << in << endl;
		count_sum += count;
	}
	
	cout << count_sum << endl;

	return count_sum;
}


int main() {
	//secret_map();
	//dart_game();
	//cache();
	//shuttle_bus();
	//news_clustering();
	//friends4block();
	//chuseok_traffic();
	//n_factor();
	//compress();
	//filename_sorting();
	//recent_music();
	//autocorrection();

	cout << "EOF" << endl;
	int i;
	cin >> i;

	return 0;
}
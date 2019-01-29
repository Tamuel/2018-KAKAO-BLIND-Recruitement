#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <deque>
#include <algorithm>
#include <functional>
#include <iomanip>

using namespace std;

// 4. ¹æ±Ý±×°î
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

int main() {
	recent_music();

	return 0;
}
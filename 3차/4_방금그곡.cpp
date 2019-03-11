#include <iostream>
#include <string>
#include <vector>

using namespace std;

typedef struct muinfo {
	int start;
	int end;
	string title = "";
	string melody = "";
} muinfo;


void convert(string& str) {
	string temp = "";
	for (int i = 0; i < str.length() - 1; i++) {
		if (str[i] == 'C' || str[i] == 'D' || str[i] == 'F' || str[i] == 'G' || str[i] == 'A') {
			if (str[i + 1] == '#')
				temp += char(str[i++] + 8);
			else temp += str[i];
		}
		else temp += str[i];
	}
	temp += str[str.length() - 1];
	str = temp;
}

int main() {
	int n;
	cin >> n;
	string m, temp;
	vector<muinfo> musicinfos;
	cin >> m;
	convert(m);
	musicinfos.resize(n);
	for (int i = 0; i < n; i++) {
		cin >> temp;
		musicinfos[i].start = stoi(temp.substr(0, 2)) * 60 + stoi(temp.substr(3, 2));
		musicinfos[i].end = stoi(temp.substr(6, 2)) * 60 + stoi(temp.substr(9, 2));
		int t = 12;
		while (temp[t] != ',') musicinfos[i].title += temp[t++];
		t++;
		while (temp[t] != '\0') musicinfos[i].melody += temp[t++];
		convert(musicinfos[i].melody);
	}

	int select = -1;
	for (int idx = 0; idx < musicinfos.size(); idx++) {
		muinfo& minfo = musicinfos[idx];
		bool check = true;
		int mLength = minfo.melody.length();
		for (int c = 0; c < minfo.end - minfo.start; c++) {
			check = true;
			for (int i = 0; i < m.length(); i++) {
				if (minfo.melody[(c + i) % mLength] != m[i]) {
					check = false;
					break;
				}
			}
			if (check) break;
		}

		if (check && (select == -1 || musicinfos[idx].end - musicinfos[idx].start > musicinfos[select].end - musicinfos[select].start))
			select = idx;
	}

	if (select == -1) cout << "(None)" << endl;
	else cout << musicinfos[select].title << endl;

	return 0;
}

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

typedef struct filename {
	string ori;
	string head;
	int number;
	bool operator<(struct filename& f) {
		if (head != f.head)
			return head < f.head;
		else
			return number < f.number;
	}
} filename;

int main() {
	vector<filename> files;
	int n;
	cin >> n;
	files.resize(n);

	for (int i = 0; i < n; i++) {
		cin >> files[i].ori;
		string num = "";
		for (int h = 0; h < files[i].ori.length(); h++) {
			if (files[i].ori[h] >= '0' && files[i].ori[h] <= '9')
				num += files[i].ori[h];
			else if (num == "")
				files[i].head += tolower(files[i].ori[h]);
			else break;
		}
		files[i].number = stoi(num);
	}

	sort(files.begin(), files.end());

	for (filename f : files)
		cout << f.ori << endl;
	
	return 0;
}

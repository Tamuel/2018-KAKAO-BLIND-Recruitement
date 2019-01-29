#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <deque>
#include <algorithm>
#include <functional>
#include <iomanip>

using namespace std;

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
		n_childs++; // Child의 갯수 저장
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

	// Make tree (Insert만 하면 자동으로 트리가 만들어지게 설계)
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
	autocorrection();

	return 0;
}
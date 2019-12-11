#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
using namespace std;

string solve(string::iterator& it);
int main() {
	freopen("Text.txt", "r", stdin);
	int C, test_case;

	cin >> C;
	
	for (test_case = 0; test_case < C; ++test_case) {
		string tree;
		cin >> tree;
		string::iterator it = tree.begin();
		string result = solve(it);
		cout << result << endl;
	}

	return 0;
}
string solve(string::iterator& it) {
	char head = *it;
	++it;
	if (head == 'b' || head == 'w')
		return string(1, head);

	string a0 = solve(it);
	string a1 = solve(it);
	string a2 = solve(it);
	string a3 = solve(it);

	return string("x") + a2 + a3 + a0 + a1;
}
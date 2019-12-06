
//�Է��� ù �ٿ��� �׽�Ʈ ���̽��� �� C(1 <= C <= 10) �� �־�����.
//�� �׽�Ʈ ���̽��� ù �ٿ��� ���ϵ�ī�� ���ڿ� W �� �־�����, �� ���� �ٿ��� ���ϸ��� �� N(1 <= N <= 50) �� �־�����.
//�� �� N �ٿ� �ϳ��� �� ���ϸ��� �־�����.���ϸ��� ���� ���� ���ĺ� ��ҹ��ڿ� ���ڸ����� �̷���� ������, 
//���ϵ�ī��� �� �ܿ� * �� ? �� ���� �� �ִ�.��� ���ڿ��� ���̴� 1 �̻� 100 �����̴�.
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

class MyString {
	char str[101];
	int size;
public:
	MyString() {
		for (int i = 0; i < 101; ++i)
			str[i] = '\0';
	}
	void reset() {
		for (int i = 0; i < 101; ++i)
			str[i] = '\0';
		size = 0;
	}
	char get(int index) {
		return this->str[index];
	}
	int get_size() {
		return size;
	}
	char* get_str() {
		return str;
	}
	char operator[](int index) {
		return str[index];
	}
	friend istream& operator>>(istream& in, MyString& obj);
};

istream& operator>>(istream& in, MyString& obj) {
	in >> obj.str;
	int size = 0;
	for (int i = 0; i < 101; ++i) {
		if (obj.str[i] == '\0') {
			obj.size = i;
			break;
		}
	}
	return in;
}
MyString pattern;
MyString str;
vector<string> result;

int cache[101][101];
int solve(int p, int s);
int solve2(int p, int s);

int main() {
	freopen("Text.txt", "r", stdin);
	int T, test_case;
	cin >> T;
	int N;
	for (test_case = 0; test_case < T; ++test_case) {
		pattern.reset();
		cin >> pattern;
		cin >> N;
		result.clear();
		for (int n = 0; n < N; ++n) {
			str.reset();
			for (int i = 0; i < 101; ++i)
				for (int j = 0; j < 101; ++j)
					cache[i][j] = -1;
				

			cin >> str;
			int ret = solve2(0,0);
			if (ret == 1) {
				result.push_back(str.get_str());
			}
			
		}
		sort(result.begin(), result.end());
		for (int i = 0; i < result.size(); ++i)
			cout << result[i] << endl;

	}

	return 0;
}
int solve(int start_p, int start_s) {
	int& ret = cache[start_p][start_s];
	if (ret != -1) return ret;

	int p = start_p;
	int s = start_s;

	ret = 0;
	while (p < pattern.get_size() && s < str.get_size()) {
		if (pattern.get(p) == str.get(s) || pattern.get(p) == '?') {
			++p;
			++s;
		}
		else if (pattern.get(p) == '*') {
			if ( p == pattern.get_size() - 1)
				return ret = 1;
			else 
				ret = ret || solve(p + 1, s++);

			if (ret == 1) return ret;
		}
		else
			return ret = 0;
			
	}

	if (pattern.get(p) == '*' && p == pattern.get_size() - 1)
		ret = ret || 1;
	else if (p == pattern.get_size() && s == str.get_size())
		ret = ret || 1;
	else
		ret = ret || 0;

	return ret;
}
int solve2(int p, int s) {
	int& ret = cache[p][s];
	if (ret != -1) return ret;

	if (p < pattern.get_size() && s < str.get_size() && (pattern.get(p) == str.get(s) || pattern.get(p) == '?')) {
		return ret = solve2(p + 1, s + 1);
	}
	if (pattern.get(p) == '*') {
		if (solve2(p + 1, s) || (s < str.get_size() && solve2(p, s + 1)))
			return ret = 1;
	}
	if (p == pattern.get_size() && s == str.get_size()) return 1;
	else  return 0;
}
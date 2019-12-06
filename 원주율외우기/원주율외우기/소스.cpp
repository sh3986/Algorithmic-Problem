#include <iostream>
#include <string>
using namespace std;

int INF = 5000000;
int cache[10000];
int pi[10000];

int min(int x, int y) {
	return x > y ? y : x;
}
int solve(int start, int end);
int level(int start, int end);
int main() {
	//freopen("Text.txt", "r", stdin);
	int T, test_case;
	cin >> T;
	

	for (test_case = 0; test_case < T; ++test_case) {
		string str;
		cin >> str;
		
		for (int i = 0; i < str.size(); ++i) {
			pi[i] = str[i] - 48;
			cache[i] = -1;
		}
		cout << solve(0, str.size()) << endl;
	}
	return 0;
}
int solve(int start, int end) {
	if (start == end) return 0;
	
	int& ret = cache[start];
	if (ret != -1) return ret;

	ret = INF;
	for (int i = 3; i <= 5; ++i) {
		if (start + i <= end) {
			int grade = level(start, start + i);
			int temp = solve(start + i, end);
			ret = min(ret, grade + temp);
		}
	}
	return ret;
}
int level(int start, int end) {
	int i = 0;
	for (i = start + 1; i < end; ++i)
		if (pi[i] != pi[i - 1])
			break;
	if (i == end)
		return 1;
	//pi[1] - pi[0]; 진짜 소름돋는 오류
	int add = pi[start+1] - pi[start];
	for (i = start + 1; i < end; ++i)
		if (pi[i] - pi[i - 1] != add)
			break;
	if (i == end) {
		if (add == 1 || add == -1)
			return 2;
		else
			return 5;
	}
	for (i = start + 2; i < end; ++i)
		if (pi[i] != pi[i - 2])
			break;
	if (i == end)
		return 4;

	return 10;
}

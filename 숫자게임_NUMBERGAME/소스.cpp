#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
using namespace std;

int MIN(int x, int y) { return x < y ? x : y; }
int MAX(int x, int y) { return x > y ? x : y; }

int board[50];
int cache[50][50];
int N;
int EMPTY = -5000000;

int play(int left, int right);
int main() {
	freopen("Text.txt", "r", stdin);
	
	int C, test_case;
	cin >> C;
	for (test_case = 0; test_case < C; ++test_case) {
		cin >> N;
		for (int i = 0; i < 50; ++i) {
			for (int j = 0; j < 50; ++j) {
				cache[i][j] = EMPTY;
			}
		}
		for (int n = 0; n < N; ++n) {
			cin >> board[n];
		}
		int result = play(0, N - 1);
		cout << result << endl;
		
	}

	return 0; 
}
int play(int left, int right) {
	if (left > right) return 0;

	int& ret = cache[left][right];
	if (ret != EMPTY) return ret;

	ret = MAX(ret, board[left] - play(left + 1, right));
	ret = MAX(ret, board[right] - play(left, right-1));

	if (right - left + 1 >= 2) {
		ret = MAX(ret, -play(left + 2, right));
		ret = MAX(ret, -play(left, right-2));
	}
	return ret;
}
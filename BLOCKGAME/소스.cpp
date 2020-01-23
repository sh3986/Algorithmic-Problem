#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
using namespace std;

int MIN(int x, int y) { return x < y ? x : y; }
int MAX(int x, int y) { return x > y ? x : y; }

int cache[1 << 25];
int block[6] = {3, 33, 67, 35, 49, 97};
int FULL_BOARD = (1 << 25) - 1;

int play(int board);

int main() {
	freopen("Text.txt", "r", stdin);

	int C, test_case;
	cin >> C;

	for (test_case = 0; test_case < C; ++test_case) {
		for (int i = 0; i < 1 << 25; ++i) {
			cache[i] = -2;
		}

		int board = 0;
		string input;
		for (int i = 0; i < 5; ++i) {
			cin >> input;
			for (int j = 0; j < 5; ++j) {
				board *= 2;
				if (input[j] == '#')
					++board;
			}
		}
		int result = play(board);
		string str = result == 1 ? "WINNING" : "LOSING";
		cout << str << endl;
	}
	

	return 0;
}
int play(int board) {
	if (board == FULL_BOARD)
		return -1;

	int& ret = cache[board];
	if (ret != -2) return ret;

	for (int start = 0; start < 25; ++start) {
		for (int i = 0; i < 6; ++i) {
			if ((block[i] << start) <= FULL_BOARD && ((block[i] << start) & board) == 0) {
				int cand = play(board | (block[i] << start));
				cand = cand == -2 ? cand : -cand;
				ret = MAX(ret, cand);
			}
		}
	}
	return ret;
}
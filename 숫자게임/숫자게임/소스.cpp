#include <iostream>
using namespace std;

int MAX(int x, int y) {
	return x > y ? x : y;
}
int MIN(int x, int y) {
	return x > y ? y : x;
}

int board[100];
int cache[51][51];
int minMaxCache[51][51][2];
int N;
int minValue = -60000;
int maxValue = 60000;
int solve(int l, int r);
int minMax(int l, int r, int player);
int main() {
	freopen("Text.txt", "r", stdin);

	int C, test_case;
	cin >> C;
	for (test_case = 0; test_case < C; ++test_case) {
		cin >> N;
		for (int n = 0; n < N; ++n) {
			cin >> board[n];
		}
		for (int l = 0; l < 51; ++l) {
			for (int r = 0; r < 51; ++r) {
				cache[l][r] = maxValue;
				minMaxCache[l][r][0] = minMaxCache[l][r][1] = maxValue;
			}
		}
		int result = solve(0, N-1);
		int result2 = minMax(0, N - 1, 0);
		cout << result << endl;
		cout << result2 << endl;
	}

	return 0;
}
int minMax(int l, int r, int player) {
	if (l > r) return 0;
	int& ret = minMaxCache[l][r][player];
	if (ret != maxValue) return ret;

	//서하차례일 때 MIN으로 Return 하면 최선을 다한 것이 아닌데?

	int result1 = board[l] - minMax(l + 1, r, (player-1)*-1);
	int result2 = board[r] - minMax(l, r - 1, (player-1)*-1);
	
	ret = player == 0 ? MAX(result1, result2) : MIN(result1, result2);

	if (r - l + 1 >= 2) {
		int result3 = -minMax(l + 2, r, (player - 1)*-1);
		int result4 = -minMax(l, r - 2, (player - 1)*-1);

		ret = player == 0 ? MAX(ret, result3) : MIN(ret, result3);
		ret = player == 0 ? MAX(ret, result4) : MIN(ret, result4);
	}
	return ret;

}
int solve(int l, int r) {
	if (l > r) return 0;

	int& ret = cache[l][r];
	if (ret != maxValue) return ret;

	ret = minValue;
	
	int result1 = board[l] - solve(l + 1, r);
	int result2 = board[r] - solve(l, r - 1);
	ret = MAX(result1, result2);
	if (r - l + 1 >= 2) {
		ret = MAX(ret, -solve(l + 2, r));
		ret = MAX(ret, -solve(l, r-2));
	}
	return ret;
}
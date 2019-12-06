#define _CRT_SECURE_NO_WARNINGS

#include <iostream>

using namespace std;

int H, W;
int map[22][22];
int solve();
void getStartPos(int& y, int& x) {
	int h = 1, w = 1;
	int flag = 0;
	for (int h = 1; h <= H; ++h) {
		for (int w = 1; w <= W; ++w) {
			if (map[h][w] == 0) {
				y = h;
				x = w;
				return;
			}
		}
	}
	y = -1;
	x = -1;
}

int dir[4][2][2] = {
	{{1,0},{1,-1}},
	{{1,0},{1,1}},
	{{0,1},{1,0}},
	{{0,1},{1,1}}
};
int main() {
	freopen("Text.txt", "r", stdin);

	int C, test_case;
	cin >> C;
	char ch;
	for (test_case = 0; test_case < C; ++test_case) {
		cin >> H >> W;
		for (int h = 0; h < 22; ++h) {
			for (int w = 0; w < 22; ++w) {
				map[h][w] = 1;
			}
		}
		for (int h = 1; h <= H; ++h) {
			for (int w = 1; w <= W; ++w) {
				cin >> ch;
				if (ch == '#')
					map[h][w] = 1;
				else
					map[h][w] = 0;
			}
		}
		cout << solve() << endl;
	}


	return 0;
}

int solve() {
	int y1 = -1, x1 = -1;
	getStartPos(y1, x1);

	if (y1 == -1 && x1 == -1)
		return 1;

	int ret = 0;

	int y2, x2, y3, x3;
	for (int d = 0; d < 4; ++d) {
		y2 = y1 + dir[d][0][0];
		x2 = x1 + dir[d][0][1];

		y3 = y1 + dir[d][1][0];
		x3 = x1 + dir[d][1][1];

		if (map[y2][x2] == 0 && map[y3][x3] == 0) {
			map[y1][x1] = map[y2][x2] = map[y3][x3] = 1;
			ret += solve();
			map[y1][x1] = map[y2][x2] = map[y3][x3] = 0;
		}
	}

	return ret;
}
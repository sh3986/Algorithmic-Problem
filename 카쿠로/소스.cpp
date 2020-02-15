#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
using namespace std;

int min(int x, int y) { return x < y ? x : y; }
int max(int x, int y) { return x > y ? x : y; }

int MAP[22][22][3];
int* HINT[22][22][2];
int N, Q;

void solve();
bool search();
bool set(int y, int x, int value, int offset);
int main() {
	freopen("Text.txt", "r", stdin);
	int Test, test_case;
	cin >> Test;
	for (test_case = 0; test_case < Test; ++test_case) {
		for (int i = 0; i < 22; ++i) {
			for (int j = 0; j < 22; ++j) {
				MAP[i][j][0] = MAP[i][j][1] = MAP[i][j][2] = 0;
				HINT[i][j][0] = HINT[i][j][1] = NULL;
			}
		}
		cin >> N;
		for (int i = 1; i <= N; ++i) {
			for (int j = 1; j <= N; ++j) {
				int input;
				cin >> input;
				MAP[i][j][2] = -input;
			}
		}
		cin >> Q;
		for (int q = 0; q < Q; ++q) {
			int y, x, d, sum;
			cin >> y >> x >> d >> sum;
			MAP[y][x][d] = sum;
		}
		solve();
	}

	return 0;
}
void solve() {
	for (int y = 1; y <= N; ++y) {
		for (int x = 1; x <= N; ++x) {
			if (MAP[y][x][2] != -1)
				continue;
			int l_y = y, l_x = x - 1;
			int u_y = y - 1, u_x = x;
			
			if (MAP[l_y][l_x][2] == 0) {
				HINT[y][x][0] = &MAP[l_y][l_x][0];
			}
			else {
				HINT[y][x][0] = HINT[l_y][l_x][0];
			}

			if (MAP[u_y][u_x][2] == 0) {
				HINT[y][x][1] = &MAP[u_y][u_x][1];
			}
			else {
				HINT[y][x][1] = HINT[u_y][u_x][1];
			}

		}
	}

	if (search()) {
		for (int y = 1; y <= N; ++y) {
			for (int x = 1; x <= N; ++x) {
				cout << MAP[y][x][2] << " ";
			}
			cout << endl;
		}
	}
}
bool set(int y, int x, int value, int offset) {
	if (offset == 1) {
		bool isZeroLast = false, isOneLast = false;
		if (MAP[y][x + 1][2] == 0) {
			isZeroLast = true;
		}
		if (MAP[y + 1][x][2] == 0) {
			isOneLast = true;
		}
		if ((isZeroLast && *HINT[y][x][0] != value) || (isOneLast && *HINT[y][x][1] != value))
			return false;

		if (*HINT[y][x][0] < value || *HINT[y][x][1] < value)
			return false;
	}
	

	MAP[y][x][2] = offset == 1 ? value : -1;
	*HINT[y][x][0] -= (value * offset);
	*HINT[y][x][1] -= (value * offset);
	return true;
}
bool search() {
	int y = -1, x = -1;
	for (int i = 1; i <= N; ++i) {
		for (int j = 1; j <= N; ++j) {
			if (MAP[i][j][2] == -1) {
				y = i;
				x = j;
				break;
			}
		}
		if (y != -1)
			break;
	}
	if (y == -1)
		return true;

	bool isZeroLast = false, isOneLast = false;

	if (MAP[y][x + 1][2] == 0) {
		isZeroLast = true;
	}
	if (MAP[y + 1][x][2] == 0) {
		isOneLast = true;
	}

	if ((isZeroLast && *HINT[y][x][0] > 9) || (isOneLast && *HINT[y][x][1] > 9))
		return false;
	
	for (int value = 9; value >= 1; --value) {
		if (set(y, x, value, 1)) {
			if (search()) {
				return true;
			}
			set(y, x, value, -1);
		}
	}
	return false;
}
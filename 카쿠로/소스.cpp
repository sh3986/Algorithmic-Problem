#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <vector>
using namespace std;

int min(int x, int y) { return x < y ? x : y; }
int max(int x, int y) { return x > y ? x : y; }

int MAP[22][22][3];
struct HINT {
	int y;
	int x;
	int d;
	int value;
	int useNum;
	vector<pair<int, int>> elementList;
	HINT(int y, int x, int d, int value) : y(y),x(x), d(d), value(value), useNum(0), elementList(vector<pair<int, int>>()) {}
};
HINT* HINT_PTR[22][22][2];
vector<HINT> HINT_LIST;

int N, Q;
void solve();
bool search();
bool set(int y, int x, int value, int offset);

int main() {
	freopen("Text.txt", "r", stdin);
	int Test, test_case;
	cin >> Test;
	for (test_case = 0; test_case < Test; ++test_case) {
		HINT_LIST.clear();
		for (int i = 0; i < 22; ++i) {
			for (int j = 0; j < 22; ++j) {
				MAP[i][j][0] = MAP[i][j][1] = MAP[i][j][2] = 0;
				HINT_PTR[i][j][0] = HINT_PTR[i][j][1] = NULL;
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
			HINT_LIST.push_back(HINT(y, x, d, sum));
		}
		for (int q = 0; q < Q; ++q) {
			int y = HINT_LIST[q].y;
			int x = HINT_LIST[q].x;
			int d = HINT_LIST[q].d;
			HINT_PTR[y][x][d] = &(HINT_LIST[q]);
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

			HINT_PTR[y][x][0] = HINT_PTR[l_y][l_x][0];
			HINT_PTR[y][x][0]->elementList.push_back(make_pair(y, x));

			HINT_PTR[y][x][1] = HINT_PTR[u_y][u_x][1];
			HINT_PTR[y][x][1]->elementList.push_back(make_pair(y, x));
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
		if ((isZeroLast && HINT_PTR[y][x][0]->value != value) || (isOneLast && HINT_PTR[y][x][1]->value != value))
			return false;

		if (HINT_PTR[y][x][0]->value < value || HINT_PTR[y][x][1]->value < value)
			return false;
	}

	MAP[y][x][2] = offset == 1 ? value : -1;
	HINT_PTR[y][x][0]->value -= (value * offset);
	HINT_PTR[y][x][1]->value -= (value * offset);
	return true;
}
bool search() {
	int h = -1;
	for (int i = 0; i < Q; ++i) {
		if (HINT_LIST[i].value != 0) {
			h = i;
			break;
		}
	}
	if (h == -1)
		return true;
	HINT& hint = HINT_LIST[h];
	for (int i = 0; i < hint.elementList.size(); ++i) {
		int y = hint.elementList[i].first, x = hint.elementList[i].second;
		int d = hint.d;
		int& visited = hint.useNum;
		if (MAP[y][x][2] != -1)
			continue;
		if (i == hint.elementList.size() - 1) {
			if (hint.value > 9 || (visited & (1<<hint.value)))
				return false;
			if (set(y, x, hint.value, 1)) {
				if (search()) {
					return true;
				}
				set(y, x, hint.value, -1);
			}
		}
		else {
			for (int value = 1; value <= 9; ++value) {
				if (visited & (1 << value))
					continue;
 				if (set(y, x, value, 1)) {
					int prev = visited;
					visited |= (1 << value);
					if (search()) {
						return true;
					}
					set(y, x, value, -1);
					visited = prev;
				}
			}
		}
		return false;
	}
}
/*int y = -1, x = -1;
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
		if (setValue(y, x, value, 1)) {
			if (search()) {
				return true;
			}
			setValue(y, x, value, -1);
		}
	}*/
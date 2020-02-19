//#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <vector>
using namespace std;

int min(int x, int y) { return x < y ? x : y; }
int max(int x, int y) { return x > y ? x : y; }

const int MAXN = 21;
int N;
int color[MAXN][MAXN], value[MAXN][MAXN], hint[MAXN][MAXN][2];


int Q;
// sum과 length는 고정
int sum[MAXN * MAXN], length[MAXN * MAXN], known[MAXN * MAXN];

int candidates[10][46][1024];
int getSize(int set) {
	int len = 0;
	for (int next = 1; next <= 9; ++next) {
		if (set & (1 << next))
			++len;
	}
	return len;
}
int getSum(int set) {
	int sum = 0;
	for (int next = 1; next <= 9; ++next) {
		if (set & (1 << next))
			sum+=next;
	}
	return sum;
}
void generateCandidates();

int getHint(int hint) {
	return candidates[length[hint]][sum[hint]][known[hint]];
}
int getCandidates(int y, int x) {
	return getHint(hint[y][x][0]) & getHint(hint[y][x][1]);
}
void put(int y, int x, int val) {
	for (int d = 0; d < 2; ++d) 
		known[hint[y][x][d]] += (1 << val);
	
	value[y][x] = val;
}
void remove(int y, int x, int val) {
	for (int d = 0; d < 2; ++d)
		known[hint[y][x][d]] -= (1 << val);

	value[y][x] = 0;
}
void printMatrix() {
	for (int i = 1; i <= N; ++i) {
		for (int j = 1; j <= N; ++j) {
			cout << value[i][j] << " ";
		}
		cout << endl;
	}
}
bool search();
int main() {
	//freopen("Text.txt", "r", stdin);
	int Test, test_case;
	cin >> Test;
	for (test_case = 0; test_case < Test; ++test_case) {
		for (int i = 0; i < MAXN; ++i) {
			for (int j = 0; j < MAXN; ++j) {
				color[i][j] = value[i][j] = 0;
				hint[i][j][0] = hint[i][j][1] = 0;
			}
		}
		for (int i = 0; i < MAXN * MAXN; ++i) {
			sum[i] = length[i] = known[i] = 0;
		}
		cin >> N;
		for (int i = 1; i <= N; ++i) {
			for (int j = 1; j <= N; ++j) {
				cin >> color[i][j];
			}
			
		}
		cin >> Q;
		for (int q = 0; q < Q; ++q) {
			int y, x, d, s;
			cin >> y >> x >> d >> s;
			sum[q] = s;
			known[q] = 0;
			int addY = d == 0 ? 0 : 1;
			int addX = d == 0 ? 1 : 0;
			y += addY;
			x += addX;
			
			while (color[y][x] == 1) {
				++length[q];
				hint[y][x][d] = q;
				y += addY;
				x += addX;
			}
		}
		generateCandidates();
		search();
	}
	
	return 0;
}

void generateCandidates() {
	for (int i = 0; i < 10; ++i) {
		for (int j = 0; j < 46; ++j) {
			for (int k = 0; k < 1024; ++k) {
				candidates[i][j][k] = 0;
			}
		}
	}
	for (int set = 0; set < 1024; ++set) {
		int l = getSize(set);
		int s = getSum(set);
		int subSet = set;
		while (true) {
			candidates[l][s][subSet] |= (set & ~subSet);
			if (subSet == 0) break;
			subSet = (subSet - 1) & set;
		}
	}
}

bool search() {
	int y = -1, x = -1, minCand = 1023;
	for (int i = 1; i <= N; ++i) {
		for (int j = 1; j <= N; ++j) {
			if (color[i][j] == 1 && value[i][j] == 0) {
				int cand = getCandidates(i, j);
				if (getSize(minCand) > getSize(cand)) {
					minCand = cand;
					y = i;
					x = j;
				}
			}
		}
	}
	if (minCand == 0) return false;

	if (y == -1) {
		printMatrix();
		return true;
	}

	for (int val = 1; val <= 9; ++val) {
		if (minCand & (1 << val)) {
			put(y, x, val);
			if (search())
				return true;
			remove(y, x, val);
		}
	}
	return false;
}
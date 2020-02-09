#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int min(int x, int y) { return x < y ? x : y; }
int max(int x, int y) { return x > y ? x : y; }

int H, W, R, C;

int best;
int blockCnt;
void boardCover(vector<vector<int>>& board, int currentCnt);

bool set(int y, int x, vector<vector<int>>& board, const vector<pair<int, int>>& block, int delta) {
	bool ok = true;
	for (int i = 0; i < block.size(); ++i) {
		const int next_y = y + block[i].first;
		const int next_x = x + block[i].second;
		if (next_y < 0 || next_y >= H || next_x < 0 || next_x >= W)
			ok = false;
		else if ((board[next_y][next_x] += delta) > 1)
			ok = false;
	}
	return ok;
}
vector<vector<int>> rotate(const vector<vector<int>> & source) {
	int rowSize = source.size();
	int colSize = source[0].size();
	vector<vector<int>> dest = vector<vector<int>>(colSize, vector<int>(rowSize));
	for (int r = 0; r < rowSize; ++r) {
		for (int c = 0; c < colSize; ++c) {
			dest[c][rowSize - 1 - r] = source[r][c];
		}
	}
	return dest;
}
vector<pair<int, int>> getBlock(const vector<vector<int>> & source) {
	vector<pair<int, int>> ret;

	int originY = -1;
	int originX = -1;
	for (int i = 0; i < source.size(); ++i) {
		for (int j = 0; j < source[0].size(); ++j) {
			if (source[i][j] == 1) {
				originY = i;
				originX = j;
				break;
			}
		}
		if (originY != -1)
			break;
	}
	for (int i = 0; i < source.size(); ++i) {
		for (int j = 0; j < source[0].size(); ++j) {
			if (source[i][j] == 1) {
				ret.push_back(make_pair(i - originY, j - originX));
			}
		}
	}
	return ret;
}
vector<vector<pair<int, int>>> blockList;

int pruning(vector<vector<int>> & board, int currentCnt) {
	int cnt = 0;
	for (int i = 0; i < board.size(); ++i) {
		for (int j = 0; j < board[i].size(); ++j) {
			cnt += (board[i][j] == 0 ? 1 : 0);
		}
	}
	return ((cnt / blockCnt) + currentCnt) <= best;
}

int main() {
	freopen("Text.txt", "r", stdin);
	int T, test_case;
	cin >> T;
	for (test_case = 0; test_case < T; ++test_case) {
		best = 0;
		blockCnt = 0;
		cin >> H >> W >> R >> C;
		vector<vector<int>> board = vector<vector<int>>(H, vector<int>(W));
		vector<vector<int>> block = vector<vector<int>>(R, vector<int>(C));


		for (int h = 0; h < H; ++h) {
			for (int w = 0; w < W; ++w) {
				char ch;
				cin >> ch;
				board[h][w] = ch == '#' ? 1 : 0;
			}
		}
		for (int r = 0; r < R; ++r) {
			for (int c = 0; c < C; ++c) {
				char ch;
				cin >> ch;
				block[r][c] = ch == '#' ? 1 : 0;
				if (ch == '#') ++blockCnt;
			}
		}
		blockList.clear();
		for (int i = 0; i < 4; ++i) {
			blockList.push_back(getBlock(block));
			vector<vector<int>> temp = rotate(block);
			block = temp;
		}
		sort(blockList.begin(), blockList.end());
		blockList.erase(unique(blockList.begin(), blockList.end()), blockList.end());
		boardCover(board, 0);
		cout << best << endl;
	}

	return 0;
}
void boardCover(vector<vector<int>> & board, int currentCnt) {
	// Simple Heuristic ( <=이  <보다 훨씬 많이 가지치기 하기 때문에 더 빠르다.)
	if (pruning(board, currentCnt))
		return;

	int y = -1, x = -1;
	for (int i = 0; i < H; ++i) {
		for (int j = 0; j < W; ++j) {
			if (board[i][j] != 1) {
				y = i;
				x = j;
				break;
			}
		}
		if (y != -1) break;
	}
	if (y == -1) {
		best = max(best, currentCnt);
		return;
	}

	for (int d = 0; d < blockList.size(); ++d) {
		if (set(y, x, board, blockList[d], 1)) {
			boardCover(board, currentCnt + 1);
		}
		set(y, x, board, blockList[d], -1);
	}

	board[y][x] = 1;
	boardCover(board, currentCnt);
	board[y][x] = 0;
}
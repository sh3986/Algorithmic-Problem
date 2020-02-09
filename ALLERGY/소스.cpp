#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <vector>
#include <algorithm>
#include <time.h>
using namespace std;

int min(int x, int y) { return x < y ? x : y; }
int max(int x, int y) { return x > y ? x : y; }

int N, M;
vector<string> friends;
vector<int> canEat;
vector<pair<int, int>> order;
int MAP[50][50];
int accumulateMap[50][50];
int INF = 987654321;
int best;

int solve();
void search(int start, int currentCnt);
bool check() {
	for (int i = 0; i < N; ++i) {
		if (canEat[i] == 0)
			return false;
	}
	return true;
}
bool heuristic(int start, int currentCnt);
int main() {
	freopen("Text.txt", "r", stdin);
	int Test, test_case;
	cin >> Test;
	for (test_case = 0; test_case < Test; ++test_case) {
		cin >> N >> M;
		friends.clear();
		canEat = vector<int>(N, 0);
		string input;
		for (int n = 0; n < N; ++n) {
			cin >> input;
			friends.push_back(input);
		}
		for (int i = 0; i < 50; ++i) {
			for (int j = 0; j < 50; ++j) {
				MAP[i][j] = 0;
				accumulateMap[i][j] = 0;
			}
		}
		for (int m = 0; m < M; ++m) {
			int num = 0;
			cin >> num;
			for (int n = 0; n < num; ++n) {
				cin >> input;
				for (int i = 0; i < friends.size(); ++i) {
					if (friends[i] == input) {
						MAP[i][m] = 1;
						break;
					}
				}
			}
		}
		clock_t start, end;
		start = clock();
		int result = solve();
		cout << result << endl;
		end = clock();
		double executeTime = (double)(end - start);
		cout.precision(3);
		cout << "execute : " << executeTime << "ms" << endl;
	}
	return 0;
}
bool heuristic(int start, int currentCnt){
	//틀린 로직
	bool ok = true;
	for (int i = 0; i < N; ++i) {
		if (canEat[i] + accumulateMap[i][start] == 0)
			ok = false;
	}
		

	return ok && (currentCnt + (M - start + 1) >= best);
}
void search(int start, int currentCnt) {
	if (currentCnt >= best)
		return;

	/*if (heuristic(start, currentCnt)) {
		cout << endl;
	}*/

	if(start >= M){	
		if (check()) {
			int cand = currentCnt == 0 ? INF : currentCnt;
			best = min(best, cand);
		}
		return;	
	}

	int food = order[start].second;
	search(start + 1, currentCnt);
	for (int i = 0; i < N; ++i) 
		canEat[i] += MAP[i][food];
	search(start + 1, currentCnt + 1);
	for (int i = 0; i < N; ++i)
		canEat[i] -= MAP[i][food];
}
int solve() {
	best = INF;
	order.clear();

	for (int i = 0; i < N; ++i) {
		accumulateMap[i][M - 1] = MAP[i][M - 1];
	}
	for (int i = 0; i < N; ++i) {
		for (int j = M - 2; j >= 0; --j) {
			accumulateMap[i][j] = MAP[i][j] + accumulateMap[i][j + 1];
		}
	}

	for (int i = 0; i < M; ++i) {
		int cnt = 0;
		// 일단 없이 돌리기
		cnt = i;
		/*for (int j = 0; j < N; ++j) {
			if (MAP[j][i] == 1)
				++cnt;
		}*/
		order.push_back(make_pair(cnt, i));
	}
	sort(order.begin(), order.end());
	search(0, 0);
	return best;
}

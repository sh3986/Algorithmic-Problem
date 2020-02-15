//#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <vector>
#include <algorithm>
#include <time.h>
using namespace std;

int min(int x, int y) { return x < y ? x : y; }
int max(int x, int y) { return x > y ? x : y; }

int N, M;
vector<string> friends;
long long canEat;
vector<long long> mapBit;
vector<pair<int, int>> foodList;
vector<pair<int, int>> canEatFoodList[50];

int MAP[50][50];
int INF = 987654321;
int best;

int solve();
void search(int currentCnt);

int main() {
	//freopen("Text.txt", "r", stdin);
	int Test, test_case;
	cin >> Test;
	for (test_case = 0; test_case < Test; ++test_case) {
		cin >> N >> M;
		friends.clear();

		string input;
		for (int n = 0; n < N; ++n) {
			cin >> input;
			friends.push_back(input);
		}
		for (int i = 0; i < 50; ++i) {
			for (int j = 0; j < 50; ++j) {
				MAP[i][j] = 0;
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
		int result = solve();
		cout << result << endl;
	}
	return 0;
}

void search(int currentCnt) {
	if (currentCnt >= best)
		return;

	int n = 0;
	for (n = 0; n < N; ++n) {
		if (!(canEat & ((long long)1 << n)))
			break;
	}
	if (n == N)
		best = currentCnt;
	for (int i = 0; i < canEatFoodList[n].size(); ++i) {
		int m = canEatFoodList[n][i].second;
		long long prev = canEat;
		canEat |= mapBit[m];
		search(currentCnt + 1);
		canEat = prev;
	}	
}
int solve() {
	best = INF;
	canEat = 0;
	foodList.clear();
	mapBit.clear();

	for (int m = 0; m < M; ++m) {
		int cnt = 0;
		for (int n = 0; n < N; ++n) {
			if (MAP[n][m] == 1)
				++cnt;
		}
		foodList.push_back(make_pair(-cnt, m));
	}

	for (int n = 0; n < N; ++n) {
		canEatFoodList[n].clear();
		for (int m = 0; m < M; ++m) {
			if (MAP[n][m] == 1)
				canEatFoodList[n].push_back(foodList[m]);
		}
		sort(canEatFoodList[n].begin(), canEatFoodList[n].end());
	}

	for (int i = 0; i < foodList.size(); ++i) {
		long long bit = 0;
		int m = foodList[i].second;
		for (int n = 0; n < N; ++n) {
			if (MAP[n][m] == 1)
				bit |= ((long long)1 << n);
		}
		mapBit.push_back(bit);
	}
	search(0);
	return best;
}

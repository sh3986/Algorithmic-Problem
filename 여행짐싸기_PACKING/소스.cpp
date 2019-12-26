#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <vector>
#include <string>
using namespace std;

int MIN(int x, int y) { return x < y ? x : y; }
int MAX(int x, int y) { return x > y ? x : y; }

int N, W;
vector<string> A;
vector<int> W_ARRAY;
vector<int> N_ARRAY;

int NEGINF = -10000000;
int cache[101][1001];
int solve(int start, int weight);
void reconstruct(int start, int weight, vector<string>& seq);
int main() {
	freopen("Text.txt", "r", stdin);

	int C, test_case;
	cin >> C;
	for (test_case = 0; test_case < C; ++test_case) {
		for (int i = 0; i < 101; ++i) {
			for (int j = 0; j < 1001; ++j) {
				cache[i][j] = NEGINF;
			}
		}
			
		cin >> N >> W;
		A = vector<string>(N);
		W_ARRAY = vector<int>(N);
		N_ARRAY = vector<int>(N);

		for (int n = 0; n < N; ++n) {
			cin >> A[n];
			cin >> W_ARRAY[n] >> N_ARRAY[n];
		}

		int result = solve(0,W);
		vector<string> resultList;
		reconstruct(0, W, resultList);
		cout << result << ' ' << resultList.size() << endl;
		for (int i = 0; i < resultList.size(); ++i)
			cout << resultList[i] << endl;
	}
	return 0;
}
int solve(int start, int weight) {
	if (weight < 0) return NEGINF;
	if (start == N) return 0;

	int& ret = cache[start][weight];
	if (ret != NEGINF) return ret;

	ret = 0;
	if (weight - W_ARRAY[start] >= 0)
		ret = solve(start + 1, weight - W_ARRAY[start]) + N_ARRAY[start];
	ret = MAX(ret, solve(start + 1, weight));

	return ret;
}
void reconstruct(int start, int weight, vector<string>& seq) {
	if (start == N) return;
	int cand = NEGINF;
	if (weight - W_ARRAY[start] >= 0)
		cand = cache[start + 1][weight - W_ARRAY[start]] + N_ARRAY[start];

	int cand2 = cache[start + 1][weight];

	int nextWeight = 0;
	if (cand > cand2) {
		nextWeight = weight - W_ARRAY[start];
		seq.push_back(A[start]);
	}
	else
		nextWeight = weight;

	return reconstruct(start + 1, nextWeight, seq);
}
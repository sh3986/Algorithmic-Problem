#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <vector>
using namespace std;



int MIN(int x, int y) { return x < y ? x : y; }
int MAX(int x, int y) { return x > y ? x : y; }

int check(int first, int second);
int restore(int start, int taken);

int INF = 30000;
int K;
int duplicateIndex[16][16];
int cache[16][1 << 15];
int choices[16][1 << 15];
vector<string> A;
int main() {
	freopen("Text.txt", "r", stdin);

	int C, test_case;
	cin >> C;
	for (test_case = 0; test_case < C; ++test_case) {
		cin >> K;
		for (int i = 0; i < 16; ++i) {
			for (int j = 0; j < 16; ++j) {
				duplicateIndex[i][j] = -1;
			}
			for (int j = 0; j < 1 << 15; ++j) {
				cache[i][j] = -1;
				choices[i][j] = -1;
			}
		}
		A = vector<string>(K);
		for (int k = 0; k < K; ++k)
			cin >> A[k];

		for (int i = 0; i < K; ++i) {
			for (int j = 0; j < K; ++j) {
				if (i == j)
					continue;
				duplicateIndex[i][j] = check(i, j);
			}
		}
		int result = restore(-1, 0);
		cout << result << endl;
	}

	return 0;
}

int check(int first, int second) {
	string w1 = A[first];
	string w2 = A[second];
	for (int i = 0; i < w1.size(); ++i) {
		if (w1[i] != w2[0])
			continue;

		int size = w1.size() - i;
		if (w1.substr(i, size).compare(w2.substr(0, size)) == 0)
			return i;
		if (w1.substr(i, w2.size()).compare(w2) == 0)
			return i;
	}
	return -1;
}
int restore(int start, int taken) {
	if (taken == (1 << K) - 1) 
		return A[start].size();

	int& ret = cache[start+1][taken];
	int& choose = choices[start + 1][taken];
	if (ret != -1) return ret;

	ret = INF;
	for (int next = 0; next < K; ++next) {
		if ((taken & (1 << next)) != 0)
			continue;

		int nextWord = next;
		int currentLen = 0;

		if (start != -1) {
			int index = duplicateIndex[start][next];
			
			if (index != -1) {
				if (A[start].size() - index > A[next].size()) {
					nextWord = start;
				}
				else {
					currentLen = index;
				}
			}
			else {
				currentLen = A[start].size();
			}
		}
		int cand = currentLen + restore(nextWord, taken + (1 << next));
		if (cand < ret) {
			ret = cand;
			choose = next;
		}
	}
	return ret;
}
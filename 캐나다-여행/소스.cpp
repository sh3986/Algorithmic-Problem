#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
using namespace std;

int min(int x, int y) { return x < y ? x : y; }
int max(int x, int y) { return x > y ? x : y; }

int N, K;
int L[5000];
int M[5000];
int G[5000];
int C[5000];

int maxEnd = 0;
int decision(int s,int e);
int optimize();

int main() {
	freopen("Text.txt", "r", stdin);
	int Test, test_case;
	cin >> Test;
	for (test_case = 0; test_case < Test; ++test_case) {
		for (int i = 0; i < 5000; ++i) {
			L[i] = M[i] = G[i] = C[i] = 0;
		}	
		scanf("%d", &N);
		scanf("%d", &K);
		
		maxEnd = 0;
		for (int i = 0; i < N; ++i) {
			scanf("%d %d %d", &L[i], &M[i], &G[i]);
			maxEnd = max(maxEnd, L[i]);
		}
		int result = optimize();
		cout << result << endl;
	}

	return 0;
}
int decision(int s, int e) {
	int start = 0, end = 0;
	int ret = 0;
	for (int i = 0; i < N; ++i) {
		int init = L[i] - M[i];
		int count = 0;

		int prevCount = 0;
		if (s - 1 >= init)
			prevCount = (s - 1 - init) / G[i] + 1;

		int start = init + G[i] * prevCount;
		int end = min(L[i], e);
		if (end < start) 
			continue;
		count = (end - start) / G[i] + 1;
		ret += count;
	}
	return ret;
}
int optimize() {
	int lo = 0, hi = maxEnd + 1;
	
	while (lo < hi - 1) {
		int mid = (lo + hi) / 2;
		int count = decision(lo, mid-1);
		
		if (count >= K) {
			hi = mid;
		}
		else {
			lo = mid;
			K -= count;
		}
	}
	return lo;
}
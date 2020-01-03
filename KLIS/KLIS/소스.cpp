#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int MAX(int x, int y) { return x > y ? x : y; }
template<typename T>
T MIN(T x, T y) { return x < y ? x : y; }

int N, K;
int A[500];
int cacheLis[501], cacheKlis[501];

int MAX_VALUE = 2000000000 + 1;

int lis(int pos);
int klis(int start);
void reconstruct(int skip, int len, vector<int>& result);
int main() {
	freopen("Text.txt", "r", stdin);
	int C, test_case;

	cin >> C;
	for (test_case = 0; test_case < C; ++test_case) {
		for (int i = 0; i < 501; ++i) {
			cacheKlis[i] = -1;
			cacheLis[i] = -1;
		}


		cin >> N >> K;
		for (int n = 0; n < N; ++n) {
			cin >> A[n];
		}

		int lisLen = lis(-1) - 1;
		klis(-1);

		cout << lisLen << endl;
		vector<int> result;
		reconstruct(K, lisLen, result);

		for (int i = 0; i < result.size(); ++i)
			cout << result[i] << " ";
		cout << endl;
	}

	return 0;
}


int lis(int pos) {
	int& ret = cacheLis[pos + 1];
	if (ret != -1) return ret;
	ret = 1;
	for (int next = pos + 1; next < N; ++next) {
		if (pos == -1 || A[pos] < A[next]) {
			ret = MAX(ret, 1 + lis(next));
		}
	}
	return ret;
}
int klis(int start) {
	if (lis(start) == 1) return 1;

	int& ret = cacheKlis[start + 1];
	if (ret != -1) return ret;

	ret = 0;
	for (int next = start + 1; next < N; ++next) {
		if (start == -1 || (A[next] > A[start] && lis(next) + 1 == lis(start))) {
			ret = MIN<long long>((long long)MAX_VALUE, (long long)ret + klis(next));
		}
	}
	return ret;
}

void reconstruct(int skip, int len, vector<int>& result) {
	if (len == 0) 
		return;
	
	vector<pair<int, int>> search;

	for (int i = 0; i < N; ++i) {
		if ((result.empty() || A[i] > result.back()) && lis(i) == len)
			search.push_back(make_pair(A[i], i));
	}
	sort(search.begin(), search.end());
	
	for (int i = 0; i < search.size(); ++i) {
		if (klis(search[i].second) >= skip) {
			result.push_back(search[i].first);
			return reconstruct(skip, len - 1, result);
		}
		else {
			skip -= klis(search[i].second);
		}
	}
}
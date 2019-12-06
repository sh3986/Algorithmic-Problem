#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
using namespace std;

int MAX(int x, int y) {
	return x > y ? x : y;
}
int MIN(unsigned long long  x, unsigned long long  y) {
	return x > y ? y : x;
}

unsigned long long M = 200000000000 + 1;
int cacheLen[501];
unsigned long long cacheCnt[501];
vector<int> A = vector<int>(501);
int N;
unsigned long long K;
int lis(int pos);
unsigned long long lisCnt(int pos);
void reconstruct(int len, unsigned long long k, vector<int>& result);
int main() {
	freopen("Text.txt", "r", stdin);
	
	int T, test_case;
	cin >> T;
	for (test_case = 0; test_case < T; ++test_case) {
		cin >> N >> K;
		//
		N = 500;
		for (int i = 0; i < 501; ++i) {
			cacheLen[i] = -1;
			cacheCnt[i] = -1;
		}
		//
		/*for (int n = 0; n < N; ++n)
			cin >> A[n];*/
		int index = 0;
		for (int i = 1; i < 500; i += 2, index+=2) {
			A[index] = i + 1;
			A[index+1] = i;
		}
		int length = lis(-1) - 1;
		lisCnt(-1);
		vector<int> result;
		reconstruct(length, K, result);
		cout << length << endl;
		for (int i = 0; i < result.size(); ++i)
			cout << result[i] << " ";
		cout << endl;
	}
	return 0;
}
int lis(int pos) {
	int& ret = cacheLen[pos + 1];
	if (ret != -1) return ret;
	ret = 1;
	for (int next = pos + 1; next < N; ++next) {
		if (pos == -1 || A[pos] < A[next]) {
			ret = MAX(ret, 1 + lis(next));
		}
	}
	return ret;
}
unsigned long long lisCnt(int pos) {
	if (lis(pos) == 1) return 1;
	unsigned long long& ret = cacheCnt[pos + 1];
	if (ret != -1) return ret;
	ret = 0;
	for (int next = pos + 1; next < N; ++next) {
		if ((pos == -1 || A[pos] < A[next]) && lis(pos) == 1 + lis(next)) {
			ret = MIN(M, (unsigned long long)ret + lisCnt(next));
		}
	}
	return ret;
}
void reconstruct(int len, unsigned long long k, vector<int>& result) {
	if (len == 0) 
		return;
	
	vector<pair<int, unsigned long long>> search;
	for (int i = 0; i < N; ++i) {
		if ((result.empty() || A[i] > result.back()) && lis(i) == len)
			search.push_back(make_pair(A[i], lisCnt(i)));
	}
	sort(search.begin(), search.end());
	
	for (int i = 0; i < search.size(); ++i) {
		if (search[i].second >= k) {
			result.push_back(search[i].first);
			return reconstruct(len - 1, k, result);
		}
		else {
			k -= search[i].second;
		}
	}


}
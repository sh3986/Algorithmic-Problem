#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

vector<int> A;
int N, S;
int solve(int start, int n);

int MIN(int x, int y) { return x < y ? x : y; }
int MAX(int x, int y) { return x > y ? x : y; }
int INF = 2100000000;

int getMean(const vector<int>& A) {
	int sum = 0;
	for (int i = 0; i < A.size(); ++i)
		sum += A[i];
	return ((float)sum / A.size()+0.5);
}
int getDiffSquare(const vector<int>& A) {
	int mean = getMean(A);
	int sum = 0;
	for (int i = 0; i < A.size(); ++i) {
		sum += (A[i] - mean)*(A[i] - mean);
	}
	return sum;
}
int cache[100][11];
int main() {
	freopen("Text.txt", "r", stdin);

	int C, test_case;
	cin >> C;
	for (test_case = 0; test_case < C; ++test_case) {
		for (int i = 0; i < 100; ++i) {
			for (int j = 0; j < 11; ++j) {
				cache[i][j] = -1;
			}
		}
		cin >> N >> S;
		A = vector<int>(N);
		for (int n = 0; n < N; ++n)
			cin >> A[n];
		
		sort(A.begin(), A.end());
		
		int ret = solve(0, S);

		cout << ret << endl;
	}

	return 0;
}

int solve(int start, int n) {
	if (start == N)
		return 0;
	if (n == 0)
		return INF;
	int& ret = cache[start][n];
	if (ret != -1)return ret;

	ret = INF;
	for (int end = start+1; end <= N; ++end) {
		vector<int> subset = vector<int>(A.begin() + start, A.begin() + end);
		int residual = getDiffSquare(subset);
		ret = MIN(ret, residual + solve(end, n - 1));
	}
	return ret;
}
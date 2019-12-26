#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <vector>
#include <limits>
using namespace std;

const long long NEGINF = numeric_limits<long long>::min();

vector<long long> A;
vector<long long> B;
int N, M;
int cache[101][101];
long long MIN(long long x, long long y) { return x < y ? x : y; }
long long MAX(long long x, long long y) { return x > y ? x : y; }

int solve(int a, int b);
int main() {
	freopen("Text.txt", "r", stdin);
	int C, test_case;

	cin >> C;

	for (test_case = 0; test_case < C; ++test_case) {
		for (int i = 0; i < 101; ++i)
			for (int j = 0; j < 101; ++j)
				cache[i][j] = -1;

		cin >> N >> M;
		A = vector<long long>(N + 1, NEGINF);
		B = vector<long long>(M + 1, NEGINF);

		for (int n = 1; n <= N; ++n)
			cin >> A[n];
		for (int m = 1; m <= M; ++m)
			cin >> B[m];
		cout << solve(0, 0) << endl;
	}
	return 0;
}

int solve(int a, int b) {
	if (a == A.size() - 1 && b == B.size() - 1)
		return 0;
	int& ret = cache[a][b];
	if (ret != -1)
		return ret;

	long long lastValue = MAX(A[a], B[b]);

	ret = 0;
	for (int next = a + 1; next <= A.size() - 1; ++next) {
		if (A[next] > lastValue)
			ret = MAX(ret, solve(next, b) + 1);
	}
	for (int next = b + 1; next <= B.size() - 1; ++next) {
		if (B[next] > lastValue)
			ret = MAX(ret, solve(a, next) + 1);
	}
	return ret;
}
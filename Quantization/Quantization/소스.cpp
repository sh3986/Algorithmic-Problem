#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int N, S;
int INF = 1000000000;
vector<int> A;
int cache[101][11];
int quantization(int start, int s);
int calc(int start, int end);
int min(int x, int y) {
	return x > y ? y : x;
}

int used[21];
int fullSearch(int start, int s);
int main() {
	//freopen("Text.txt", "r", stdin);
	int T, test_case;
	//cin >> T;
	T = 1;
	N = 20;
	S = 3;
	for (test_case = 0; test_case < T; ++test_case) {
		//cin >> N >> S;
		A = vector<int>(N);
		for (int n = 0; n < N; ++n) {
			//cin >> A[n];
			A[n] = rand() % 20 + 1;
		}
		for (int n = 0; n < 21; ++n)
			used[n] = 0;

		for (int n = 0; n < 101; ++n) {
			for (int s = 0; s < 11; ++s) {
				cache[n][s] = -1;
			}
		}
		sort(A.begin(), A.end());
		//cout << fullSearch(0, S) << endl;
		cout << quantization(0, S) << endl;
	}


	return 0;
}
int fullSearch(int start, int s) {
	if (start == N) return 0;
	int ret = INF;
	for (int i = 1; i <= 20; ++i) {
		if (used[i] == 0) {
			used[i] = 1;
			int sub= A[start] - i;
			ret = min(ret, sub*sub + fullSearch(start + 1, s));
			used[i] = 0;
		}
			
	}
	return ret;
}
int quantization(int start, int s) {
	if (start == N) return INF;
	int& ret = cache[start][s];

	if (ret != -1) return ret;
	if (s == 1)
		return ret = calc(start, N - 1);
	ret = INF;
	for (int end = start; end < N; ++end) {
		int temp = calc(start, end);
		int quant = quantization(end + 1, s - 1);
		ret = min(ret, temp + quant);
	}
	return ret;
}
int calc(int start, int end) {
	int sum = 0;
	for (int i = start; i <= end; ++i)
		sum += A[i];
	int avg = int(0.5 + (double)sum / (end - start + 1));
	int ret = 0;
	for (int i = start; i <= end; ++i) {
		ret += ((avg - A[i])*(avg - A[i]));
	}
	return ret;
}
//입력의 첫 줄에는 테스트 케이스의 수 C(1 <= C <= 50) 가 주어집니다.
//그 후 각 줄에 사각형의 너비 n(1 <= n <= 100) 이 주어집니다.
#include <iostream>
using namespace std;

int cache[101];
unsigned int MOD = 1000000007;
int N;
int tiling(int width);
int asymmetric(int width);
int main() {
	//freopen("Text.txt", "r", stdin);
	int T, test_case;
	cin >> T;
	for (test_case = 0; test_case < T; ++test_case) {
		cin >> N;
		for (int i = 0; i < 101; ++i)
			cache[i] = -1;
		int result = 0;
		
		int duplicate = 0;
		if (N % 2 == 0) {
			result = tiling(N);
			result = (result - tiling(N / 2) + MOD) % MOD;
			result = (result - tiling((N - 2) / 2) + MOD) % MOD;
		}
		else {
			result = (tiling(N) - tiling(N / 2) + MOD) % MOD;
		}
		cout << result << endl;
	}

	return 0;
}
int tiling(int width) {
	if (width <= 1) return cache[width] = 1;
	int& ret = cache[width];
	if (ret != -1) return ret;
	return ret = (tiling(width - 1) + tiling(width - 2)) % MOD;
}
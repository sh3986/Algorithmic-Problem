#include <iostream>
#include <string>
using namespace std;


int cache[201][201];
void solve(int n, int m, int k);
int M = 1000000000 + 1000;
void calcBino();
string result;
int MIN(int x, int y) {
	return x > y ? y : x;
}
int main() {
	freopen("Text.txt", "r", stdin);
	int T, test_case;
	cin >> T;
	calcBino();
	for (test_case = 0; test_case < T; ++test_case) {
		int n, m, k;
		cin >> n >> m >> k;
		result = "";
		solve(n, m, k);
		cout << result << endl;
	}

}
void calcBino() {
	for (int i = 0; i < 201; ++i) {
		cache[i][0] = cache[i][i] = 1;
		for (int j = 1; j < i; ++j)
			cache[i][j] = MIN(M, cache[i - 1][j] + cache[i - 1][j - 1]);
	}
}
void solve(int n, int m, int k) {
	if (n == 0) {
		for (int i = 0; i < m; ++i)
			result.append("o");
		return;
	}
	int ret = cache[n - 1 + m][n-1];
	if (ret > k) {
		result.append("-");
		return solve(n - 1, m, k);
	}
	else {
		result.append("o");
		return solve(n, m-1, k-ret);
	}
	
}
#include <iostream>
#include <algorithm>
#include <string>
using namespace std;

string e, digits;
int n, m;
int MOD = 1000000007;
int cache[1 << 15][20][2];
int price(int index, int taken, int mod, int less);
int main() {
	freopen("Text.txt", "r", stdin);
	int C, test_case;
	cin >> C;
	for (test_case = 0; test_case < C; ++test_case) {
		cin >> e >> m;
		n = e.size();
		digits = e;
		sort(digits.begin(), digits.end());
		for (int i = 0; i < 1 << 15; ++i)
			for (int j = 0; j < 20; ++j)
				for (int k = 0; k < 2; ++k)
					cache[i][j][k] = -1;
		int result = price(0,0,0,0);
		cout << result << endl;
	}
	return 0;
}
int price(int index, int taken, int mod, int less) {
	if (index == n) 
		return less && mod == 0 ? 1 : 0;
	
	int& ret = cache[taken][mod][less];
	if (ret != -1) return ret;
	ret = 0;

	for (int next = 0; next < n; ++next) {
		if ((taken & 1 << next) != 0)
			continue;
		if (!less && e[index] < digits[next])
			continue;
		if (next > 0 && digits[next - 1] == digits[next] && (taken & 1 << (next - 1)) == 0)
			continue;
		int nextLess = less || e[index] > digits[next];
		int nextMod = (mod * 10 + digits[next]-'0') % m;
		int nextTaken = taken | (1 << next);
		ret += price(index + 1, nextTaken, nextMod, nextLess);
		ret %= MOD;
	}
	return ret;
}

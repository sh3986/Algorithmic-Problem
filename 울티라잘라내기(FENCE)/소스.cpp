#define _CRT_SECURE_NO_WARNINGS
#include <iostream>

template<typename T1, typename T2>
constexpr auto MIN(T1 x, T2 y) { return x < y ? x : y; }

template<typename T1, typename T2>
constexpr auto MAX(T1 x, T2 y) { return x > y ? x : y; }

using namespace std;

int FENCE[20000];
int N;

int solve(int start, int end);
int main() {
	freopen("Text.txt", "r", stdin);

	int C, test_case;
	cin >> C;
	for (test_case = 0; test_case < C; ++test_case) {

		for (int i = 0; i < 20000; ++i)
			FENCE[i] = 0;
		cin >> N;
		for (int n = 0; n < N; ++n) {
			cin >> FENCE[n];
		}

		cout << solve(0,N-1) << endl;
	}

	return 0;
}

int solve(int start, int end) {
	if (start == end)
		return FENCE[start];

	int ret = 0;
	int mid = (start + end) / 2;
	
	int leftSquare = solve(start, mid);
	int rightSquare = solve(mid + 1, end);
	ret = MAX(leftSquare, ret);
	ret = MAX(rightSquare, ret);

	int l = mid, r = mid + 1;
	int height = MIN(FENCE[l], FENCE[r]);
	ret = MAX(ret, height * (r - l + 1));

	while (start < l && r < end) {
		if (FENCE[l-1] >= FENCE[r+1]) {
			--l;
			height = MIN(height, FENCE[l]);
		}
		else {
			++r;
			height = MIN(height, FENCE[r]);
		}
		ret = MAX(ret, height * (r - l + 1));
	}

	if (r == end) {
		--l;
		for (; l >= start; --l) {
			height = MIN(height, FENCE[l]);
			ret = MAX(ret, height * (r - l + 1));
		}
	}
	else {
		++r;
		for (; r <= end; ++r) {
			height = MIN(height, FENCE[r]);
			ret = MAX(ret, height * (r - l + 1));
		}
	}

	return ret;
}

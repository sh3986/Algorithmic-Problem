#include <iostream>
using namespace std;

int MIN(int x, int y) {
	return x > y ? y : x;
}
int MAX(int x, int y) {
	return x > y ? x : y;
}
int fence[20000];
//int fence[10];
int N;
int solve(int start, int end);
int main() {
	freopen("Text.txt", "r", stdin);
	int T, test_case;
	cin >> T;
	for (test_case = 0; test_case < T; ++test_case) {
		cin >> N;

		for (int n = 0; n < N; ++n) {
			cin >> *(fence + n);
		}
		cout << solve(0, N-1) << endl;
	}


	return 0;
}
int solve(int start, int end) {
	if (start == end) 
		return fence[start];
	int mid = (start + end) / 2;
	int ret = -1;
	int left_square = solve(start, mid);
	int right_square = solve(mid + 1, end);
	ret = MAX(ret, left_square);
	ret = MAX(ret, right_square);

	int i = mid, j = mid + 1;
	int height = MIN(fence[i], fence[j]);
	int square = height * (j - i + 1);

	while (start < i && j < end) {
		if (fence[i - 1] <= fence[j + 1]) 
			height = MIN(height, fence[++j]);
		else
			height = MIN(height, fence[--i]);
		square = MAX(square, height*(j - i + 1));
	}

	for (; start < i;) {
		height = MIN(height, fence[--i]);
		square = MAX(square, height*(j - i + 1));
	}
	for (; j < end;) {
		height = MIN(height, fence[++j]);
		square = MAX(square, height*(j - i + 1));
	}
	return MAX(square, ret);
}
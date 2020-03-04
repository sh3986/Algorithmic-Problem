#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
using namespace std;

int min(int x, int y) { return x < y ? x : y; }
int max(int x, int y) { return x > y ? x : y; }

int N, M;

bool decision(int n, int m, long long mid);
int optimize(int n, int m);
int main() {
	freopen("Text.txt", "r", stdin);
	int Test, test_case;
	cin >> Test;
	for (test_case = 0; test_case < Test; ++test_case) {
		cin >> N >> M;
		
		int result = optimize(N,M);
		cout << result << endl;
	}

	return 0;
}

bool decision(int n, int m, long long mid) {
	long long first = (long long)m * 100 / n ;
	long long second = (long long)(m + mid) * 100 / (n + mid);
	return second - first < 1;
}
int optimize(int n, int m) {
	long long lo = 0, hi = 2e+9 + 1;
	while(lo+1<hi){
		long long mid = (lo + hi) / 2;
		if (decision(n,m, mid)) {
			lo = mid;
		}
		else {
			hi = mid;
		}
	}
	return hi == 2e+9 + 1 ? -1 : hi;
}

//소수점 자리 출력
//cout.setf(ios::fixed);
//cout.precision(2);
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
using namespace std;


int MIN(int x, int y) { return x < y ? x : y; }
int MAX(int x, int y) { return x > y ? x : y; }

int N, K, M;
int L[50];
double T[50][50];
int Q[10];

vector<double> genius();
int main() {
	freopen("Text.txt", "r", stdin);
	int C, test_case;

	cin >> C;
	for (test_case = 0; test_case < C; ++test_case) {
		cin >> N >> K >> M;
		for (int n = 0; n < N; ++n) 
			cin >> L[n];
		
		for (int i = 0; i < N; ++i) {
			for (int j = 0; j < N; ++j) {
				cin >> T[i][j];
			}
		}
		for (int m = 0; m < M; ++m)
			cin >> Q[m];

		vector<double> result = genius();
		cout << 1 << endl;
		
	}

	return 0;
}

vector<double> genius() {
	double c[5][50];
	for (int i = 0; i < 5; ++i) {
		for (int j = 0; j < 50; ++j) {
			c[i][j] = 0;
		}
	}
	c[0][0] = 1;
	for (int k = 1; k <= K; ++k) {
		for (int s = 0; s < N; ++s) {
			double& cache = c[k % 5][s];
			cache = 0;
			for (int i = 0; i < N; ++i) {
				if (k >= L[i])
					cache += c[(k - L[i] + 5) % 5][i] * T[i][s];
			}
 		}
	}
	vector<double> ret(N);

	for (int song = 0; song < N; ++song) {
		double& cand = ret[song];
		cand = 0;
		for (int time = K - L[song] + 1; time <= K; ++time) {
			cand += c[time % 5][song];
		}
	}

	return ret;
}
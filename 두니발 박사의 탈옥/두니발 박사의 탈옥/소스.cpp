#include <iostream>
#include <iomanip>
using namespace std;

int A[51][51];
//int A[5][5];
double cache[51][101];
int edges[51];
double solve(int pos, int d);
int N, D, P;
int main() {
	freopen("Text.txt", "r", stdin);
	int T, test_case;
	cin >> T;
	int cnt, p;
	for (test_case = 0; test_case < T; ++test_case) {
		cin >> N >> D >> P;
		for (int i = 0; i < N; ++i) {
			edges[i] = 0;
			for (int j = 0; j < N; ++j) {
				cin >> A[i][j];
				edges[i] += A[i][j];
			}
		}
			
		for (int i = 0; i < 51; ++i) 
			for (int d = 0; d < 101; ++d) 
				cache[i][d] = -1;
		cin >> cnt;
		for (int i = 0; i < cnt; ++i) {
			cin >> p;
			cout << solve(p, D) << " ";
			//cout << fixed << setprecision(8) << solve(p, D) << " ";
		}
		cout << endl;
		
	}
	return 0;
}
double solve(int pos, int d) {
	if (d == 0) {
		if (pos == P) return 1;
		else return 0;
	}
	double& ret = cache[pos][d];
	if (ret != -1) return ret;

	ret = 0;
	for (int next = 0; next < N; ++next) {
		if (A[pos][next] == 1) {
			double propablity = 1.0 / edges[next];
			double result = solve(next, d - 1);
			ret += (propablity * result);
		}
			
	}
	return ret;
}
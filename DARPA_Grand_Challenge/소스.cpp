#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <vector>
using namespace std;
double max(double x, double y) { return x > y ? x : y; }
double min(double x, double y) { return x < y ? x : y; }

double cache[200][100];
double NINF = -987654321;
double INF = 987654321;
int N, M;
vector<double> locations;
bool decisions(const vector<double>& locations, int cameras, double gap);
double optimize(const vector<double>& locations, int cameras);
double solve(int start, int cameras);
int main() {
	freopen("Text.txt", "r", stdin);
	int Test, test_case;
	cin >> Test;
	for (test_case = 0; test_case < Test; ++test_case) {
		cin >> N >> M;
		locations.clear();
		for (int i = 0; i < 200; ++i) {
			for (int j = 0; j < 100; ++j) {
				cache[i][j] = -1;
			}
		}
		for (int m = 0; m < M; ++m) {
			double input;
			cin >> input;
			locations.push_back(input);
		}
		double result = optimize(locations, N);

		cout.setf(ios::fixed);
		cout.precision(2);
		cout << result << endl;

		result = NINF;
		for (int i = 0; i < M; ++i) {
			double cand = solve(i, N - 1);
			if(cand != INF)
				result = max(result, cand);
		}
		cout << result << endl;
		cout << endl;
		
	}

	return 0;
}
bool decisions(const vector<double>& locations, int cameras, double gap) {
	double limit = -1;
	int installed = 0;
	for (int i = 0; i < locations.size(); ++i) {
		if (limit <= locations[i]) {
			++installed;
			limit = locations[i] + gap;
		}
	}
	return cameras <= installed;
}
double optimize(const vector<double>& locations, int cameras) {
	double lo = 0, hi = 241;

	for (int i = 0; i < 100; ++i) {
		double mid = (lo + hi) / 2;
		if (decisions(locations, cameras, mid)) {
			lo = mid;
		}
		else
			hi = mid;
	}
	return lo;
}

double solve(int start, int cameras) {
	if (cameras == 0)
		return 0;

	if (start == M-1)
		return INF;

	double& ret = cache[start][cameras];
	if (ret != -1) return ret;

	double minValue = INF;
	for (int next = start+1; next < M; ++next) {
		if (cameras >= 1) {
			double gap = locations[next] - locations[start];
			double cand = solve(next, cameras - 1);
			cand = cand == 0 ? gap : cand;
			//이게 문제
			minValue = min(minValue, cand);
		}
		if (minValue != INF)
			ret = max(ret, minValue);
	}
	return ret;
}
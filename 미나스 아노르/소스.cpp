#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <algorithm>
#include <cmath>

using namespace std;


int MIN(int x, int y) { return x < y ? x : y; }
double MAX(double x, double y) { return x > y ? x : y; }
int N;

double y[100], x[100], r[100];
pair<double, double> ranges[100];
const double pi = 2 * acos(0);
const int INF = 987654321;

void converRange();
int solveCircular();
int solveLinear(double start, double end);
int main() {
	freopen("Text.txt", "r", stdin);
	int C, test_case;
	cin >> C;

	for (test_case = 0; test_case < C; ++test_case) {
		cin >> N;
		for (int n = 0; n < N; ++n) {
			cin >> y[n] >> x[n] >> r[n];
		}
		converRange();
		int result = solveCircular();
		if (result == INF)
			cout << "IMPOSSIBLE" << endl;
		else
			cout << result << endl;
	}

	return 0;
}
void converRange() {
	for (int i = 0; i < N; ++i) {
		double loc = fmod(2*pi + atan2(y[i], x[i]), 2*pi);
		double range = 2.0 * asin(r[i] / 2 / 8);
		ranges[i] = make_pair(loc - range, loc + range);
	}
	sort(y, y + N);
}
int solveCircular() {
	int ret = INF;
	sort(ranges, ranges + N);

	for (int i = 0; i < N; ++i) {
		if (ranges[i].first <= 0 || ranges[i].second >= 2 * pi) {
			double begin = fmod(ranges[i].second, 2 * pi);
			double end = fmod(2 * pi + ranges[i].first, 2 * pi);
			
			ret = MIN(ret, 1 + solveLinear(begin, end));
		}
	}
	return ret;
}

int solveLinear(double begin, double end) {
	int used = 0;
	
	while (begin < end) {
		double maxCover = -1;
		for (int i = 0; i < N; ++i) {
			//왜 여기서 값을 정규화 시키지 않고 바로 연산하지?
			double first = ranges[i].first;
			if (first <= begin) {
				double second = ranges[i].second;
				maxCover = MAX(maxCover, second);
			}
			
		}
		if (maxCover <= begin) return INF;
		begin = maxCover;
		++used;
	}
	return used;
}
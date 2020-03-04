#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <vector>
#include <queue>
#include <math.h>
using namespace std;

double min(double x, double y) { return x < y ? x : y; }
double max(double x, double y) { return x > y ? x : y; }

int N;
//(x,y)
vector<pair<double, double>> locations;
double dist[100][100];
bool decision(const vector<pair<double, double>>& locations, int bases, double d);
double optimize(const vector<pair<double, double>>& locations, int bases);
int main() {
	freopen("Text.txt", "r", stdin);
	int Test, test_case;
	cin >> Test;
	for (test_case = 0; test_case < Test; ++test_case) {
		cin >> N;
		locations.clear();
		for (int i = 0; i < 100; ++i) {
			for (int j = 0; j < 100; ++j) {
				dist[i][j] = 0.0;
			}
		}
		for (int n = 0; n < N; ++n) {
			double x,y;
			cin >> x >> y;
			locations.push_back(make_pair(x, y));
		}
		for (int i = 0; i < N; ++i) {
			for (int j = i + 1; j < N; ++j) {
				double xDiff = locations[i].first - locations[j].first;
				double yDiff = locations[i].second - locations[j].second;
				dist[i][j] = dist[j][i] = sqrt(xDiff * xDiff + yDiff * yDiff);
			}
		}
	
		double result = optimize(locations, N);
		cout.setf(ios::fixed);
		cout.precision(2);
		cout << result << endl;
	}
	return 0;
}

bool decision(const vector<pair<double, double>>& locations, int bases, double d) {
	int seen = 1;
	vector<bool> visited(bases, false);
	visited[0] = true;
	queue<int> q;
	q.push(0);
	while (!q.empty()) {
		int here = q.front();
		q.pop();
		for (int next = 0; next < N; ++next) {
			if (visited[next] != true && d >= dist[here][next]) {
				visited[next] = true;
				q.push(next);
				++seen;
			}
		}
	}
	return seen == bases;
}
double optimize(const vector<pair<double, double>>& locations, int bases) {
	double lo = 0, hi = 1415;

	for (int i = 0; i < 100; ++i) {
		double mid = (lo + hi) / 2;

		if (decision(locations, bases, mid))
			hi = mid;
		else
			lo = mid;
	}
	return lo;
}

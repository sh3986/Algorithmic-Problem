#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <vector>
#include <time.h>
#include <algorithm>
#include <map>
#include <intrin.h>

using namespace std;

double min(double x, double y) { return x < y ? x : y; }
double max(double x, double y) { return x > y ? x : y; }

int N;
const int MAX = 15;
const int CACHE_DEPTH = 5;
double dist[MAX][MAX];
double minEdge[MAX];
vector<int> nearest[MAX];
map<int, double> cache[MAX][CACHE_DEPTH+1];

const double INF = 1e200;
double best = INF;
double shortestPath(vector<int>& path, vector<bool>& visited, double currentLength);
double simpleHeuristic(const vector<bool>& visited);
bool pathSwapPruning(const vector<int>& path);
bool pathReversePruning(const vector<int>& path);
double dp(int here, int visited);
void search(vector<int>& path, vector<bool>& visited, double currentLength);
double solve();
int main() {
	freopen("Text.txt", "r", stdin);
	int C, test_case;
	cin >> C;

	for (test_case = 0; test_case < C; ++test_case) {
		cin >> N;
		for (int i = 0; i < N; ++i) {
			for (int j = 0; j < N; ++j) {
				cin >> dist[i][j];
			}
		}
		
		clock_t start, end;
		start = clock();
		double result = solve();
		cout.precision(10);
		cout << result << endl;
		end = clock();
		double executeTime = (double)(end - start);
		cout.precision(3);
		cout << "test case : " << N << " time : " << executeTime << "ms" << endl;

		/*double result = solve();
		cout.precision(10);
		cout << result << endl;*/
	}

	return 0;
}
double shortestPath(vector<int>& path, vector<bool>& visited, double currentLength) {
	int here = path.back();
	if (path.size() == N) {
		//return currentLength + dist[here][0];
		return currentLength;
	}
	double ret = INF;
	for (int next = 0; next < N; ++next) {
		if (!visited[next]) {
			path.push_back(next);
			visited[next] = 1;
			double cand = shortestPath(path, visited, currentLength + dist[here][next]);
			ret = min(ret, cand);
			path.pop_back();
			visited[next] = 0;
		}
	}
	return ret;
}
double simpleHeuristic(const vector<bool>& visited) {
	double ret = 0;
	for (int next = 0; next < N; ++next) {
		if (!visited[next])
			ret += minEdge[next];
	}
	return ret;
}
bool pathSwapPruning(const vector<int>& path) {
	if (path.size() < 4) return false;

	int p = path[path.size() - 4];
	int a = path[path.size() - 3];
	int b = path[path.size() - 2];
	int q = path[path.size() - 1];

	return dist[p][a] + dist[b][q] > dist[p][b] + dist[a][q];
}
bool pathReversePruning(const vector<int>& path) {
	if (path.size() < 4) return false;
	int b = path[path.size() - 2];
	int q = path[path.size() - 1];
	for (int i = 0; i + 3 < path.size(); ++i) {
		int p = path[i];
		int a = path[i + 1];
		if (dist[p][a] + dist[b][q] > dist[p][b] + dist[a][q])
			return true;
	}
	return false;
}

double dp(int here, int visited) {
	if (visited == ((1 << N) - 1))
		return 0;
	int remaining = N - __popcnt(visited);
	double& ret = cache[here][remaining][visited];

	if (ret != 0) return ret;
	ret = INF;

	for (int i = 0; i < nearest[here].size(); ++i) {
		int next = nearest[here][i];
		if (visited & (1 << next)) continue;
		ret = min(ret, dp(next, visited | (1 << next)) + dist[here][next]);
	}
	return ret;
}
void search(vector<int>& path, vector<bool>& visited, double currentLength) {
	if (path.size() + CACHE_DEPTH >= N) {
		int visitedInt = 0;
		for (int i = 0; i < path.size();++i) 
			visitedInt += (1 << path[i]);

		best = min(best, currentLength + dp(path.back(), visitedInt));
		return;
	}
	if (best <= currentLength + simpleHeuristic(visited)) return;
	if (pathReversePruning(path))  return;

	int here = path.back();
	if (path.size() == N) {
		//return currentLength + dist[here][0];
		best = min(best, currentLength);
	}
	for (int i = 0; i < nearest[here].size(); ++i) {
		int next = nearest[here][i];
		if (!visited[next]) {
			path.push_back(next);
			visited[next] = 1;
			search(path, visited, currentLength + dist[here][next]);
			path.pop_back();
			visited[next] = 0;
		}
	}
}
double solve() {
	best = INF;
	// 가지치기 heuristic 준비
	for (int i = 0; i < N; ++i) {
		double& ret = minEdge[i];
		ret = INF;
		for (int j = 0; j < N; ++j) {
			if (i != j)
				ret = min(ret, dist[i][j]);
		}
	}
	// 탐색순서 바꾸기 준비
	for (int i = 0; i < N; ++i) {
		vector<pair<double, int>> order;
		for (int j = 0; j < N; ++j) {
			if (i != j) 
				order.push_back(make_pair(dist[i][j], j));
		}
		sort(order.begin(), order.end());
		nearest[i].clear();
		for (int j = 0; j < order.size(); ++j) {
			nearest[i].push_back(order[j].second);
		}
	}
	for (int i = 0; i < N; ++i) {
		for (int j = 0; j <= CACHE_DEPTH; ++j) {
			cache[i][j].clear();
		}
	}

	for (int start = 0; start < N; ++start) {
		vector<int> path(1, start);
		vector<bool> visited(N, 0);
		visited[start] = 1;
		search(path, visited, 0);
	}
	return best;
}


/*double result = INF;
for (int start = 0; start < N; ++start) {
	vector<int> path(1, start);
	vector<bool> visited(N, 0);
	visited[start] = 1;
	double cand = shortestPath(path, visited, 0);
	result = min(result, cand);
}*/
#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int MIN(int x, int y) { return x < y ? x : y; }
int MAX(int x, int y) { return x > y ? x : y; }

int N;
class Lunch {
public:
	int m;
	int e;
	Lunch(int m, int e) :m(m), e(e) {};
};
bool compare(Lunch o1, Lunch o2) {
	if (o1.e == o2.e) {
		return o1.m < o2.m;
	}
	else {
		return o1.e > o2.e;
	}
}

int lunchBox(const vector<int>& M, const vector<int>& E);
int main() {
	freopen("Text.txt", "r", stdin);
	int C, test_case;
	cin >> C;

	for (test_case = 0; test_case < C; ++test_case) {
		cin >> N;
		vector<int> M(N);
		vector<int> E(N);
		for (int n = 0; n < N; ++n) {
			cin >> M[n];
		}
		for (int n = 0; n < N; ++n) {
			cin >> E[n];
		}

		int result = lunchBox(M, E);
		cout << result << endl;
	}
	
	return 0;
}
int lunchBox(const vector<int>& M, const vector<int>& E) {
	vector<Lunch> lunches;
	for (int n = 0; n < N; ++n) {
		lunches.push_back(Lunch(M[n], E[n]));
	}

	sort(lunches.begin(), lunches.end(), compare);
	
	int a = 0, b = 0;
	for (int i = 0; i < N; ++i) {
		a += lunches[i].m;
		b = MAX(b, a + lunches[i].e);
	}
	return b;
}
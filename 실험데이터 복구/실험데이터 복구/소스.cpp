#include <iostream>
#include <string>
#include <vector>
using namespace std;
int MAX(int x, int y) {
	return x > y ? x : y;
}

string words[15];

int isSkip[15];
string inputWords[15];

int K;
int cache[15][1 << 15];
int overlap[15][15];

int overlapCheck(string o1, string o2);
int getOverLapCount(string o1, string o2, int i, int j);
int restore(int last, int used);

void restruct(vector<int>& result, int used);
int main() {
	freopen("Text.txt", "r", stdin);
	int T, test_case;
	cin >> T;
	for (test_case = 0; test_case < T; ++test_case) {
		int N = 0;
		cin >> N;
		for (int k = 0; k < N; ++k) {
			isSkip[k] = 0;
			cin >> inputWords[k];
			for (int i = 0; i < (1 << 15); ++i)
				cache[k][i] = -1;
		}
		for (int i = 0; i < N; ++i) {
			for (int j = 0; j < N; ++j) {
				if (i == j) continue;
				int count = overlapCheck(inputWords[i], inputWords[j]);
				if (inputWords[j].size() == count)
					isSkip[j] = 1;
			}
		}
		int idx = 0;
		for (int i = 0; i < N; ++i) {
			if (isSkip[i]) continue;
			words[idx++] = inputWords[i];
		}
		K = idx;
		for (int i = 0; i < K; ++i) {
			for (int j = 0; j < K; ++j) {
				if (i == j) continue;
				overlap[i][j] = overlapCheck(words[i], words[j]);
			}
		}
		for (int k = 0; k < K; ++k) {
			restore(k, 1<<k);
		}
		vector<int> result;
		restruct(result, 0);
	}
	return 0;
}
void restruct(vector<int>& result,  int used) {
	if (result.size() == K) {
		string ret = words[result[0]];
		for (int i = 1; i < K; ++i)
			ret += words[result[i]].substr(overlap[result[i - 1]][result[i]]);
		cout << ret << endl;
		return;
	}
	int maxValue = -1;
	int idx = -1;
	for (int next = 0; next < K; ++next) {
		if ((used & (1 << next)) != 0) continue;
		if (maxValue < cache[next][used | 1 << next]) {
			idx = next;
			maxValue = cache[next][used | 1 << next];
		}
	}
	result.push_back(idx);
	restruct(result, used | 1 << idx);
}
int restore(int last, int used) {
	if (used == (1 << K) - 1) return cache[last][used] = 0;
	int& ret = cache[last][used];
	if (ret != -1) return ret;

	ret = 0;
	for (int next = 0; next < K; ++next) {
		if ((used & (1 << next)) == 0) {
			int overLength =  overlap[last][next];
			ret = MAX(overLength + restore(next, used | 1 << next), ret);
		}
	}
	return ret;
}
int getOverLapCount(string o1, string o2, int i, int j) {
	int count = 0;
	while (i < o1.size() && j < o2.size()) {
		if (o1[i] != o2[j]) {
			return 0;
		}
		++i;
		++j;
		++count;
	}
	return count;
}
int overlapCheck(string o1, string o2) {
	int result = 0;

	vector<int> starts;
	for (int i = 0; i < o1.size(); ++i) {
		if (o1[i] == o2[0]) {
			starts.push_back(i);
		}
	}
	if (starts.size() == 0) return 0;
	else {
		int maxCount = 0;
		for (int i = 0; i < starts.size(); ++i) {
			int start = starts[i];
			int count = getOverLapCount(o1, o2, start, 0);
			maxCount = MAX(maxCount, count);
		}
		
		return maxCount;
	}
}
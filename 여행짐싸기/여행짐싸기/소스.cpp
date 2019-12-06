#include <iostream>
#include <string>
#include <vector>
using namespace std;

int MAX(int x, int y) {
	return x > y ? x : y;
}

vector<string> selectedItems;
int N, W;
vector<string> items;
int weights[101];
int needs[101];
int cache[101][1001];
int pack(int idx, int w);
void reconstruct(int idx, int w);
int main() {
	freopen("Text.txt", "r", stdin);
	int T, test_case;
	cin >> T;
	for (test_case = 0; test_case < T; ++test_case) {
		cin >> N >> W;
		items = vector<string>(N);
		selectedItems = vector<string>();
		for (int n = 0; n < N; ++n) {
			cin >> items[n] >> weights[n] >> needs[n];
		}
		for (int i = 0; i < 101; ++i)
			for (int j = 0; j < 1001; ++j)
				cache[i][j] = -1;

		int result = pack(0, W);
		reconstruct(0, W);
		cout << result << " " << selectedItems.size() << endl;
		for (int i = 0; i < selectedItems.size(); ++i)
			cout << selectedItems[i] << endl;
		
	}
	return 0;
}
int pack(int idx, int w) {
	if (idx >= N) return cache[idx][w]=0;
	int& ret = cache[idx][w];

	if (ret != -1) return ret;
	ret = 0;
	ret = MAX(ret, pack(idx + 1, w));
	if (w >= weights[idx])
		ret = MAX(ret, needs[idx] + pack(idx + 1, w - weights[idx]));
	
	return ret;
}
void reconstruct(int idx, int w) {
	if (idx == N) return;
	if (cache[idx][w] == cache[idx + 1][w]) {
		return reconstruct(idx + 1, w);
	}
	else {
		selectedItems.push_back(items[idx]);
		return reconstruct(idx + 1, w-weights[idx]);
	}
}
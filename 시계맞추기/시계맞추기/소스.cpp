#include <iostream>
using namespace std;
#define MIN(X,Y) X>Y?Y:X

int INF = 1000000;
int clocks[16];
int switchs[10][5] = {
	{0,1,2,-1,-1},
	{3,7,9,11,-1},
	{4,10,14,15,-1},
	{0,4,5,6,7},
	{6,7,8,10,12},
	{0,2,14,15,-1},
	{3,14,15,-1,-1},
	{4,5,7,14,15},
	{1,2,3,4,5},
	{3,4,5,9,13}
};
int click[10];
int solve(int pos);
int main() {
	//freopen("Text.txt", "r", stdin);

	int T, test_case;
	cin >> T;
	for (test_case = 0; test_case < T; ++test_case) {
		for (int i = 0; i < 10; ++i) 
			click[i] = 0;
		for (int i = 0; i < 16; ++i) 
			cin >> clocks[i];
		int result = solve(0);
		result = result == INF ? -1 : result;
		cout << result << endl;
	}

	return 0;
}
void setClocks(int index) {
	for (int i = 0; i < 5; ++i) {
		if (switchs[index][i] == -1) return;
		int time = clocks[switchs[index][i]];
		time += 3;
		time = time == 15 ? 3 : time;
		clocks[switchs[index][i]] = time;
	}

}
int solve(int pos) {
	if (pos == 10) {
		bool isAll12 = true;
		for (int i = 0; i < 16; ++i) {
			if (clocks[i] != 12) {
				isAll12 = false;
				break;
			}
		}
		if (isAll12 == true) {
			int ret = 0;
			for (int i = 0; i < 10; ++i)
				ret += click[i];
			return ret;
		}
		else return INF;
	}
	int ret = INF;

	for (int i = 0; i <= 3; ++i) {
		int temp;
		if (i == 0) {
			temp  = solve(pos + 1);
			ret = MIN(ret, temp);
		}
		else {
			setClocks(pos);
			click[pos]++;
			temp = solve(pos + 1);
			ret = MIN(ret, temp);
		}
	}
	setClocks(pos);
	click[pos] = 0;
	return ret;
}
#include <iostream>
#include <vector>
using namespace std;


bool areFriends[10][10];
bool hasFriend[10];
int solve(bool hasFriend[10]);
int N,M;

int main() {
	//freopen("Text.txt", "r", stdin);
	int T, test_case;
	
	cin >> T;
	for (test_case = 0; test_case < T; ++test_case) {
		for (int i = 0; i < 10; ++i) {
			for(int j=0;j < 10; ++j){
				areFriends[i][j] = false;
			}
			hasFriend[i] = false;
		}
		cin >> N >> M;
		for (int m = 0; m < M; ++m) {
			int i, j;
			cin >> i >> j;
			areFriends[i][j] = areFriends[j][i] = true;
		}

		
		cout << solve(hasFriend) << endl;
	}
		
	

	return 0;
}

int solve(bool hasFriend[10]) {
	int current = -1;
	for (int i = 0; i < N; ++i) {
		if (hasFriend[i] == false) {
			current = i;
			break; 
		}
	}
	if (current == -1) return 1;
	int ret = 0;
	hasFriend[current] = true;
	for (int next = current + 1; next < N; ++next) {
		if (areFriends[next][current] == true && hasFriend[next] == false) {
			hasFriend[next] = true;
			ret += solve(hasFriend);
			hasFriend[next] = false;
		}
	}
	hasFriend[current] = false;
	return ret;
}
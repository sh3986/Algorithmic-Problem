#include <iostream>
using namespace std;

int map[22][22];
int H, W;
int setBlock();

const int dir[4][3][2] = {
	{{0,0}, {1,0},{1,-1}},
	{{0,0}, {0,1},{1,1}},
	{{0,0}, {1,0},{1,1}},
	{{0,0}, {1,0},{0,1}}
};

int main() {
	//freopen("Text.txt", "r", stdin);
	int T, test_case;

	cin >> T;
	
	char str[20];
	for (test_case = 0; test_case < T; ++test_case) {
		for (int y = 0; y < 22; ++y) {
			for (int x = 0; x < 22; ++x) {
				map[y][x] = 1;
			}
		}
		scanf("%d %d", &H, &W);
		for (int h = 1; h <= H; ++h) {
			scanf("%s", str);
			for (int w = 0; w < W; ++w) {
				if (str[w] == '#')
					map[h][w+1] = 1;
				else
					map[h][w+1] = 0;
			}
		}
		cout << setBlock() << endl;

	}
	

	return 0;
}
int setBlock(){
	int y, x, isFind = 0;
 	for (y = 1; y <= H; ++y) {
		for (x = 1; x <= W; ++x) {
			if (map[y][x] == 0) {
				isFind = 1;
				break;
			}
		}
		if (isFind == 1) break;
	}
	if (isFind == 0)
		return 1;
	int result = 0;
	for (int i = 0; i < 4; ++i) {
		int next_y[3];
		int next_x[3];
		for (int j = 0; j < 3; ++j) {
			next_y[j] = y + dir[i][j][0];
			next_x[j] = x + dir[i][j][1];
		}
		if ((map[next_y[0]][next_x[0]] == 1) || (map[next_y[1]][next_x[1]] == 1) || (map[next_y[2]][next_x[2]] == 1)) continue;
		for (int j = 0; j < 3; ++j)
			map[next_y[j]][next_x[j]] = 1;
		result += setBlock();
		for (int j = 0; j < 3; ++j)
			map[next_y[j]][next_x[j]] = 0;
	}
	
	return result;
}
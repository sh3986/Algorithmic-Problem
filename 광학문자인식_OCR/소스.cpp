#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#include <string>
#include <cmath>
using namespace std;

int WORD_COUNT, Q;
string WORDS[501];
string sentence[100];
int mapping[100];

double M[501][501];
double T[501][501];

double cache[102][502];
int choices[102][502];

int N;
double solve(int start, int prevword);
void reconstruct(int start, int prevword, vector<string>& seq);
string reconstruct2(int start, int prevword);
int main() {
	freopen("Text.txt", "r", stdin);
	
	cin >> WORD_COUNT >> Q;
	for (int i = 0; i < 102; ++i) {
		for (int j = 0; j < 502; ++j) {
			cache[i][j] = 1.0;
		}
	}
	for (int w = 1; w <= WORD_COUNT; ++w) {
		/*char str[12];
		scanf("%s", str);
		WORDS[w] = str;*/
		cin >> WORDS[w];
	}

	for (int i = 1; i <= WORD_COUNT; ++i) {
		//scanf("%lf", T[0] + i);
		cin >> T[0][i];
		T[0][i] = log(T[0][i]);
	}
		
	for (int i = 1; i <= WORD_COUNT; ++i) {
		for (int j = 1; j <= WORD_COUNT; ++j) {
			//scanf("%lf", T[i] + j);
			cin >> T[i][j];
			T[i][j] = log(T[i][j]);
		}
	}
	for (int i = 1; i <= WORD_COUNT; ++i) {
		for (int j = 1; j <= WORD_COUNT; ++j) {
			//scanf("%lf", M[i] + j);
			cin >> M[i][j];
			M[i][j] = log(M[i][j]);
		}
	}

	for (int q = 0; q < Q; ++q) {
		//scanf("%d", &N);
		cin >> N;
		for (int n = 0; n < N; ++n) {
			/*char str[12];
			scanf("%s", str);*/
			string str;
			cin >> str;
			sentence[n] = str;
			for (int i = 1; i <= WORD_COUNT; ++i) {
				if (WORDS[i] == str) {
					mapping[n] = i;
					break;
				}
			}
		}
		solve(0, 0);
		/*vector<string> seq;
		reconstruct(0, 0, seq);*/

		string ret = reconstruct2(0, 0);
		cout << ret  << endl;
		/*for (int i = 0; i < seq.size(); ++i) {
			cout << seq[i];
			if (i != seq.size() - 1)
				cout << " ";
			else
				cout << endl;
		}*/

	}
	return 0;
}
double solve(int start, int prevword) {
	if (start == N) return 0;
	double& ret = cache[start][prevword];
	
	if (ret != 1.0) return ret;

	ret = -1e200;
	int& choose = choices[start][prevword];

	for (int i = 1; i <= WORD_COUNT; ++i) {
		double cand = T[prevword][i] + M[i][mapping[start]] + solve(start + 1, i);
		if (cand > ret) {
			choose = i;
			ret = cand;
		}
	}

	return ret;
}
void reconstruct(int start, int prevword, vector<string>& seq) {
	if (start == N) return;
	
	int select = choices[prevword][start];
	seq.push_back(WORDS[select]);
	return reconstruct(select, start + 1, seq);
	
}

string reconstruct2(int start, int prevword) {
	int select = choices[prevword][start];
	string ret = WORDS[select];

	if(start < N-1)
		ret = ret + " " + reconstruct2(start + 1, select);
	return ret;
}
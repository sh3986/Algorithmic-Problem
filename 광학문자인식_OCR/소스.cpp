#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#include <string>
#include <cmath>
using namespace std;

int WORD_COUNT, Q;
string WORDS[501];
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

	if (WORD_COUNT < 1 || WORD_COUNT>500 || Q < 1 || Q>100)
		exit(-1);

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
		if (N < 1 || N>100)
			exit(-1);

		for (int n = 0; n < N; ++n) {
			/*char str[12];
			scanf("%s", str);*/
			string str;
			cin >> str;
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
	if (start == N)

		return 0;

	double& result = cache[start][prevword];

	if (result != 1.0)

		return result;

	result = -1e200; //log(0)=음의 무한대

	int& choose = choices[start][prevword];

	//classified[segment]에 대응되는 단어

	for (int thisMatch = 1; thisMatch <= WORD_COUNT; thisMatch++)

	{
		double candidate = T[prevword][thisMatch] + M[thisMatch][mapping[start]] + solve(start + 1, thisMatch);
		if (result < candidate)
		{
			result = candidate;
			choose = thisMatch;
		}
	}
	return result;
}
void reconstruct(int start, int prevword, vector<string>& seq) {
	if (start == N) return;
	
	int select = choices[prevword][start];
	seq.push_back(WORDS[select]);
	return reconstruct(select, start + 1, seq);
	
}

string reconstruct2(int start, int prevword) {
	int choose = choices[start][prevword];

	string result = WORDS[choose];

	if (start < N - 1)

		result = result + " " + reconstruct2(start + 1, choose);

	return result;
}
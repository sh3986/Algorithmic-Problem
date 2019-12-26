#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

int cache[100][100];
string pattern;
string word;
int solve(int p, int w);
//int solve2(int p, int w);
int main() {
	freopen("Text.txt", "r", stdin);

	int C, test_case;
	cin >> C;

	int count;
	for (test_case = 0; test_case < C; ++test_case) {
		cin >> pattern;
		cin >> count;
		vector<string> wordList;
		for (int i = 0; i < count; ++i) {
			for (int i = 0; i < 100; ++i) {
				for (int j = 0; j < 100; ++j) {
					cache[i][j] = -1;
				}
			}
			cin >> word;
			int result = solve(0, 0);
			if (result == 1)
				wordList.push_back(word);
		}
		sort(wordList.begin(), wordList.end());
		for (int i = 0; i < wordList.size(); ++i)
			cout << wordList[i] << endl;
	}
	return 0;
 }

int solve(int p, int w) {
	int& ret = cache[p][w];
	if (ret != -1) return ret;
	ret = 0;
	if (p < pattern.size() && w < word.size() && (pattern[p] == '?' || pattern[p] == word[w]))
		return ret = solve(p + 1, w + 1);

	if (p == pattern.size()) return ret = (w == word.size());
	if (pattern[p] == '*') {
		if (solve(p + 1, w) || (w < word.size() && solve(p, w + 1)))
			return ret = 1;
	}
	return ret;
}
/*
int solve2(int p, int w) {
	if (p == pattern.size() && w == word.size())
		return 1;
	else if (p == pattern.size() - 1 && pattern[p] == '*')
		return 1;
	else if (p == pattern.size() || w == word.size())
		return 0;

	int& ret = cache[p][w];
	if (ret != -1) return ret;

	ret = 0;
	if (pattern[p] != '*') {
		if (pattern[p] == '?' || pattern[p] == word[w])
			return ret = solve(p + 1, w + 1);
		else
			return ret = 0;
	}
	for (int i = w; i < word.size(); ++i) {
		ret = solve(p + 1, i);
		if (ret == 1)
			break;
	}
	return ret;
}
*/

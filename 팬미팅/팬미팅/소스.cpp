#include <iostream>
#include <vector>
#include <string>
using namespace std;

int ABS(int a) {
	return a < 0 ? a * -1 : a;
}
int MAX(int x, int y) {
	return x > y ? x : y;
}
int MIN(int x, int y) {
	return x > y ? y : x;
}
void normalize(vector<int>& num) {
	num.push_back(0);
	for (int i = 0; i < num.size()-1; ++i) {
		if (num[i] < 0) {
			int abs = ABS(num[i]);
			int borrow = abs%2 ==0 ? abs/2 : (abs+1)/2;
			num[i + 1] -= borrow;
			num[i] += borrow * 2;
		}
		else {
			num[i + 1] += num[i] / 10;
			num[i] %= 10;
		}
	}
}
vector<int> multiply(const vector<int>& a, const vector<int>& b) {
	vector<int> c = vector<int>(a.size() + b.size() + 1, 0);
	for (int i = 0; i < a.size(); ++i) {
		for (int j = 0; j < b.size(); ++j) {
			c[i + j] += a[i] * b[j];
		}
	}
    //normalize(c);
	return c;
}
void addTo(vector<int>& a, const vector<int>& b, int k) {
	vector<int> temp = b;
	if (k > 0) {
		for (int i = 0; i < k; ++i) {
			temp.insert(temp.begin(), 0);
		}
	}
	int an = a.size();
	for (int i = 0; i < temp.size(); ++i) {
		if (i < an)
			a[i] += temp[i];
		else
			a.push_back(temp[i]);
	}
	//normalize(a);
	
	
}
void subTo(vector<int>& a, const vector<int>& b) {
	for (int i = 0; i < b.size(); ++i) {
		a[i] -= b[i];
	}
	//normalize(a);
}
vector<int> karatsuba(const vector<int>& a, const vector<int>& b) {
	int an = a.size(), bn = b.size();
	if (an < bn)
		return karatsuba(b, a);
	if (an == 0 || bn == 0) return vector<int>();

	if (an <= 100000) return multiply(a, b);

	int half = an / 2;
	vector<int> a0(a.begin(), a.begin() + half);
	vector<int> a1(a.begin() + half, a.end());

	vector<int> b0(b.begin(), b.begin() + MIN(half, bn));
	vector<int> b1(b.begin() + MIN(half, bn), b.end());

	vector<int> z2 = karatsuba(a1, b1);
	vector<int> z0 = karatsuba(a0, b0);
	
	addTo(a0, a1, 0);
	addTo(b0, b1, 0);
	vector<int> z1 = karatsuba(a0, b0);
	subTo(z1, z0);
	subTo(z1, z2);

	vector<int> ret;
	addTo(ret, z0, 0);
	addTo(ret, z2, half+half);
	addTo(ret, z1, half);

	return ret;
}
void print(vector<int>& a) {
	int sum = 0;
	for (int i = a.size()-1; i >= 0; --i) {
		cout << a[i];
	}
	cout << endl;
}
int hug(const string& member, const string& fan);
int main() {
	//freopen("Text.txt", "r", stdin);
	int T, test_case;
	cin >> T;
	string member, fan;
	for (test_case = 0; test_case < T; ++test_case) {
		cin >> member >> fan;
		int result = hug(member, fan);
		cout << result << endl;
	}
	
	
	return 0;
}
int hug(const string& member, const string& fan) {
	int mn = member.size();
	int fn = fan.size();

	vector<int> a(mn, 0);
	vector<int> b(fn, 0);

	for (int i = 0; i < mn; ++i) a[i] = (member[i] == 'M');
	for (int i = 0; i < fn; ++i) b[fn-1-i] = (fan[i] == 'M');
	
	vector<int> ret = karatsuba(a, b);
	int result = 0;
	for (int i = mn-1; i <= fn-1; ++i)
		if (ret[i] == 0)
			result++;
	return result;
}
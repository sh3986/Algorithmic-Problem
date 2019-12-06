#include <iostream>
#include <vector>

template<typename T1, typename T2>
constexpr auto MIN(T1 x, T2 y) { return x > y ? x : y; }

using namespace std;

void normalize(vector<int>& a);
vector<int> multiply(const vector<int>& a, const vector<int>& b);
void addTo(vector<int>& a, const vector<int>& b, int k);
void subFrom(vector<int>& a, const vector<int>& b);

vector<int> karatsuba(const vector<int>& a, const vector<int>& b);
int main() {
	vector<int> a{ 1,2,3,4 };
	vector<int> b{ 4,5,2,1 };
	vector<int> s = multiply(a, b);

	return 0;
}

void normalize(vector<int>& a) {
	a.push_back(0);
	
	for (int i = 0; i < a.size()-1; ++i) {
		if (a[i] < 0) {
			int borrow = (-1 * a[i] + 9) / 10;
			a[i + 1] -= borrow;
			a[i] += borrow * 10;
		}
		else {
			a[i + 1] += a[i] / 10;
			a[i] %= 10;
		}
	}

	while(a.size() > 0 && a.back() == 0)
		a.pop_back();
}

vector<int> multiply(const vector<int>& a, const vector<int>& b) {
	vector<int> c(a.size() * b.size() - 1, 0);

	for (int i = 0; i < a.size(); ++i) {
		for (int j = 0; j < b.size(); ++j) {
			c[i + j] += a[i] * b[j];
		}
	}
	normalize(c);
	return c;
}

void addTo(vector<int>& a, const vector<int>& b, int k) {
	vector<int> c(b.size() + k, 0);
	for (int i = 0; i < b.size(); ++i)
		c[i + k] = b[i];
	
	int aLength = a.size();
	int cLength = c.size();

	for (int i = 0; i < cLength - aLength; ++i) 
		a.push_back(0);  

	for (int i = 0; i < c.size(); ++i) {
		a[i] += c[i];
	}
	normalize(a);
}

void subFrom(vector<int>& a, const vector<int>& b) {
	for (int i = 0; i < b.size(); ++i) {
		a[i] -= b[i];
	}
	normalize(a);
}


vector<int> karatsuba(const vector<int>& a, const vector<int>& b) {
	int an = a.size(), bn = b.size();

	if (an < bn)
		return karatsuba(b, a);

	if (an == 0 || bn == 0) return vector<int>();

	if (an <= 50) return multiply(a, b);

	int half = an / 2;
	vector<int> a0(a.begin(), a.begin() + half);
	vector<int> a1(a.begin() + half, a.end());

	return vector<int>();
	//vector<int> b0(b.begin(), min)
}
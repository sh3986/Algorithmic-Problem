#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

const double PI = 2 * acos(0.0);
const double EPSILON = 1e-9;
const double INFTY = 1e200;



struct vector2 {
	double x, y;

	explicit vector2(double x_, double y_) : x(x_), y(y_) {}

	bool operator == (const vector2& rhs) const {
		return x == rhs.x && y == rhs.y;
	}

	bool operator < (const vector2& rhs) const {
		return x != rhs.x ? x < rhs.x : y < rhs.y;
	}

	vector2 operator + (const vector2& rhs) const {
		return vector2(x + rhs.x, y + rhs.y);
	}
	vector2 operator - (const vector2 & rhs) const {
		return vector2(x - rhs.x, y - rhs.y);
	}

	vector2 operator * (double r) const {
		return vector2(x * r, y * r);
	}

	double norm() const {
		return sqrt(x * x + y * y);
	}
	vector2 normalize() const {
		return vector2(x / norm(), y / norm());
	}

	double polar() const {
		return fmod(atan2(y, x) + 2 * PI, 2 * PI);
	}

	double dot(const vector2 & rhs) const {
		return x * rhs.x + y * rhs.y;
	}
	double cross(const vector2 & rhs) const {
		return x * rhs.y - y * rhs.x;
	}
	vector2 project(const vector2 & rhs) const {
		vector2 r = rhs.normalize();
		return  r * r.dot(*this);
	}
};
int N;
vector<vector2> circles;
vector<int> radiuses;

void swap(vector2 & a, vector2 & b) {
	vector2 temp = a;
	a = b;
	b = temp;
}

double howMuchCloser(vector2 p, vector2 a, vector2 b) {
	return (b - p).norm() - (a - p).norm();
}
double ccw(const vector2 & a, const vector2 & b) {
	return a.cross(b);
}
double ccw(const vector2 & p, const vector2 & a, const vector2 & b) {
	return ccw((a - p), (b - p));
}

bool lineIntersection(vector2 a, vector2 b, vector2 c, vector2 d, vector2 & x) {
	double det = (b - a).cross(d - c);
	if (fabs(det) < EPSILON) return false;
	x = a + (b - a) * ((c - a).cross(d - c) / det);
	return true;
}
bool parallelSegments(vector2 a, vector2 b, vector2 c, vector2 d, vector2 & x) {
	if (b < a) swap(a, b);
	if (d < c) swap(c, d);

	if (ccw(a, b, c) != 0 || b < c || d < a) return false;

	if (a < c) x = c;
	else x = a;
	return true;
}
bool inBoundingRectangle(vector2 x, vector2 a, vector2 b) {
	if (b < a) swap(a, b);
	return a == x || b == x || (a < x && x < b);
}

bool segmentIntersection(vector2 a, vector2 b, vector2 c, vector2 d, vector2 & x) {
	if (!lineIntersection(a, b, c, d, x))
		return parallelSegments(a, b, c, d, x);

	return inBoundingRectangle(x, a, b) && inBoundingRectangle(x, c, d);
}
bool segmentIntersects(vector2 a, vector2 b, vector2 c, vector2 d) {
	double ab = ccw(a, b, c) * ccw(a, b, d);
	double cd = ccw(c, d, a) * ccw(c, d, b);

	if (ab == 0 && cd == 0) {
		if (b < a) swap(a, b);
		if (d < c) swap(c, d);

		return !(b < c || d < a);
	}
	return ab <= 0 && cd <= 0;
}

vector2 perpendicularFoot(vector2 p, vector2 a, vector2 b) {
	return a + (p - a).project(b - a);
}

double pointToLine(vector2 p, vector2 a, vector2 b) {
	return (p - perpendicularFoot(p, a, b)).norm();
}


vector<double> solve2(double a, double b, double c) {
	double d = b * b - 4 * a * c;
	if (d < -EPSILON) {
		return vector<double>();
	}
	if (d < EPSILON) {
		return vector<double>(1, -b / (2 * a));
	}
	vector<double> ret;
	ret.push_back((-b - sqrt(d))/ (2 * a));
	ret.push_back((-b + sqrt(d))/ (2 * a));
	return ret;
}

double hitCircle(vector2 p, vector2 d, vector2 c, int r) {
	double a_ = d.dot(d);
	double b_ = d.dot(p - c) * 2;
	double c_ = (p.dot(p)) + (c.dot(c)) - 2 * (c.dot(p)) - (r * r);

	vector<double> sols = solve2(a_, b_, c_);

	if (sols.empty() || sols[0] < EPSILON) return INFTY;
	return sols[0];
}

vector2 reflect(vector2 dir, vector2 center, vector2 contact) {
	return (dir - dir.project(contact - center)*2).normalize();
}

void simulate(vector2 here, vector2 dir) {
	dir = dir.normalize();
	int cnt = 0;
	while (cnt < 100) {
		int selected = -1;
		double minT = INFTY;
		for (int i = 0; i < N; ++i) {
			vector2 center = circles[i];
			int r = radiuses[i];

			double t = hitCircle(here, dir, center, r+1);
			if (t < minT) {
				selected = i;
				minT = t;
			}
		}
		if (selected == -1)
			break;
		if (cnt++) cout << " ";
		cout << selected;
		vector2 contact = here + (dir * minT);
		vector2 center = circles[selected];

		dir = reflect(dir, center, contact);
		here = contact;
		
	}
	cout << endl;
}


int main() {
	freopen("Text.txt", "r", stdin);
	int Test, test_case;
	cin >> Test;
	for (test_case = 0; test_case < Test; ++test_case) {
		int x, y, dx, dy, r;
		cin >> x >> y >> dx >> dy;
		vector2 here(x, y);
		vector2 dir(dx, dy);

		cin >> N;
		circles.clear();
		radiuses.clear();
		for (int n = 0; n < N; ++n) {
			cin >> x >> y >> r;
			circles.push_back(vector2(x, y));
			radiuses.push_back(r);

		}
		simulate(here, dir);
	}

	return 0;
}
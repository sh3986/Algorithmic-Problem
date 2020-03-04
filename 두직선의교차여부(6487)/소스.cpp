#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cmath>
using namespace std;

const double PI = 2 * acos(0.0);
const double EPSILON = std::numeric_limits<double>::epsilon();
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

	/*if (ccw(a, b, c) != 0 || b < c || d < a) return false;*/
	if (ccw(a, b, c) != 0) return false;

	if (a < c) x = c;
	else x = a;
	return true;
}
bool inBoundingRectange(vector2 x, vector2 a, vector2 b) {
	if (b < a) swap(a, b);
	return a == x || b == x || (a < x && x < b);
}

string segmentIntersection(vector2 a, vector2 b, vector2 c, vector2 d, vector2 & x) {
	if (!lineIntersection(a, b, c, d, x)) {
		if (parallelSegments(a, b, c, d, x))
			return "LINE";
		else
			return "NONE";
	}
	return "POINT";
	/*if (inBoundingRectange(x, a, b) && inBoundingRectange(x, c, d))
		return "POINT";
	
	return "NONE";*/
}

int main() {
	freopen("Text.txt", "r", stdin);
	int TEST, test_case;
	cin >> TEST;
	for (test_case = 0; test_case < TEST; ++test_case) {
		int x1, y1, x2, y2, x3, y3, x4, y4;
		cin >> x1 >> y1 >> x2 >> y2 >> x3 >> y3 >> x4 >> y4;
		vector2 a(x1, y1);
		vector2 b(x2, y2);
		vector2 c(x3, y3);
		vector2 d(x4, y4);
		
		vector2 p(0, 0);
		string ret = segmentIntersection(a, b, c, d, p);
		cout.setf(ios::fixed);
		cout.precision(2);
		if (ret == "POINT")
			cout << ret << " " << p.x << " " << p.y << endl;
		else
			cout << ret << endl;
	}
	return 0;
}

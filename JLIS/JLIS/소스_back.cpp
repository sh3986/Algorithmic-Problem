////�Է�
////�Է��� ù �ٿ��� �׽�Ʈ ���̽��� �� c(1 <= c <= 50) �� �־����ϴ�.
////�� �׽�Ʈ ���̽��� ù �ٿ��� A �� B �� ���� n �� m �� �־����ϴ�(1 <= n, m <= 100).
////���� �ٿ��� n ���� ������ A �� ���ҵ���, �� ���� �ٿ��� m ���� ������ B �� ���ҵ��� �־����ϴ�.
////��� ���ҵ��� 32��Ʈ ��ȣ �ִ� ������ ������ �� �ֽ��ϴ�.
////
////���
////�� �׽�Ʈ ���̽����� �� �ٿ�, JLIS �� ���̸� ����մϴ�.
//#include <iostream>
//#include <vector>
//#include <limits>
//using namespace std;
//const long long NEGINF = numeric_limits<long long>::min();
//
//
//
//int A[101];
//int B[101];
//
//int N, M;
//
//int cache[101][101];
//int max(int a, int b) {
//	return a > b ? a : b;
//}
//int jlis(int indexA, int indexB);
//
//int main() {
//	freopen("Text.txt", "r", stdin);
//	int T, test_case;
//	cin >> T;
//	for (test_case = 0; test_case < T; ++test_case) {
//		cin >> N >> M;
//		for (int n = 0; n < N; ++n) {
//			cin >> A[n];
//		}
//		for (int m = 0; m < M; ++m) {
//			cin >> B[m];
//		}
//		for (int n = 0; n < N + 1; ++n) {
//			for (int m = 0; m < M + 1; ++m) {
//				cache[n][m] = -1;
//			}
//		}
//		int ret = jlis(-1, -1);
//		cout << ret << endl;
//	}
//
//	return 0;
//}
//int jlis(int indexA, int indexB) {
//	int& ret = cache[indexA + 1][indexB + 1];
//	if (ret != -1) return ret;
//
//	ret = 2;
//	long long a = (indexA == -1 ? NEGINF : A[indexA]);
//	long long b = (indexB == -1 ? NEGINF : B[indexB]);
//	long long maxElement = max(a, b);
//
//	for (int next = indexA + 1; next < N + 1; ++next) {
//		if (maxElement < A[next])
//			ret = max(ret, jlis(next, indexB) + 1);
//	}
//	for (int next = indexB + 1; next < M + 1; ++next) {
//		if (maxElement < B[next])
//			ret = max(ret, jlis(indexA, next) + 1);
//	}
//	return ret;
//}
///*if (A[a] <= B[b]) {
//	int next_b = A[a] == B[b] ? b + 1 : b;
//	for (int next = a + 1; next < N + 1; ++next) {
//		if (next == N || A[next] > A[a])
//			ret = max(ret, jlis(next, next_b) + 1);
//	}
//}
//else {
//	for (int next = b + 1; next < M + 1; ++next) {
//		if (next == N || B[next] > B[b])
//			ret = max(ret, jlis(a, next) + 1);
//	}
//}*/
////int lis(char flag, int start, int value) {
////	int end;
////	if (flag == 'A') {
////		S = A;
////		end = N;
////		for (int n = 0; n < N; ++n) 
////			cache[n] = -1;
////	}
////	else {
////		S = B;
////		end = M;
////		for (int m = 0; m < M; ++m)
////			cache[m] = -1;
////	}
////	int ret = 0;
////	for (int begin = start; begin < end; ++begin) {
////		if (S[begin] > value)
////			ret = max(ret, solve(begin, end));
////	}
////	return ret;
////}
////int solve(int start, int end) {
////	int& ret = cache[start];
////	if (ret != ret) return ret;
////
////	ret = 1;
////	for (int next = start + 1; next < end; ++next) {
////		if (S[next] > S[start])
////			ret = max(ret, solve(next, end)+1);
////	}
////	return ret;
////}
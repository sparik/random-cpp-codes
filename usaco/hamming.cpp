/*
	ID: sparik_1
	LANG: C++
	TASK: hamming
*/

#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#include <algorithm>
#include <set>
#include <stack>
#include <queue>
#include <map>
#include <string>
#include <cmath>
#include <stdio.h>
using namespace std;

#define lint long long
#define INF 1000000000
#define MOD 1000000007
#define pb push_back
#define mp make_pair

int n, b, d;

int df[300][300];

int dist(int x, int y) {
	int res = 0;

	for (int i = 0; i < b; ++i) {
		int b1 = (x&(1 << i));
		int b2 = (y&(1 << i));
		res += (b1 != b2);
	}

	return res;
}

int ans[100];

void go(int cnt, int last) {
	if (cnt == n) {
		return;
	}

	for (int i = last; i < (1 << b); ++i) {
		int ok = 1;
		for (int j = cnt - 1; j >= 0; --j) {
			if (df[ans[j]][i] < d) {
				ok = 0;
				break;
			}
		}
		if (ok) {
			ans[cnt] = i;
			go(cnt + 1, i);
			break;
		}
	}
}

int main() {
	freopen("hamming.in", "r", stdin);
	freopen("hamming.out", "w", stdout);

	scanf("%d %d %d", &n, &b, &d);

	for (int i = 0; i < 300; ++i) {
		for (int j = 0; j < 300; ++j) {
			df[i][j] = dist(i, j);
		}
	}

	go(0, 0);

	for (int i = 0; i < n; i += 10) {
		printf("%d", ans[i]);
		for (int j = i + 1; j < i + 10 && j < n; ++j) {
			printf(" %d", ans[j]);
		}
		printf("\n");
	}

	return 0;
}
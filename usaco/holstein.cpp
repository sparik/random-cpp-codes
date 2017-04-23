/*
	ID: sparik_1
	LANG: C++
	TASK: holstein
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

int a[30];
int b[30][30];

int main() {
	freopen("holstein.in", "r", stdin);
	freopen("holstein.out", "w", stdout);

	int v, g;
	scanf("%d", &v);

	for (int i = 0; i < v; ++i) {
		scanf("%d", &a[i]);
	}

	scanf("%d", &g);

	for (int i = 0; i < g; ++i) {
		for (int j = 0; j < v; ++j) {
			scanf("%d", &b[i][j]);
		}
	}

	int ansc = INF;
	int ansm = -1;

	for (int i = 0; i < (1 << g); ++i) {
		int cnt = 0;
		int sum[30];
		for (int j = 0; j < v; ++j) {
			sum[j] = 0;
		}
		for (int j = 0; j < g; ++j) {
			if (i&(1 << j)) {
				++cnt;
				for (int k = 0; k < v; ++k) {
					sum[k] += b[j][k];
				}
			}
		}
		int ok = 1;
		for (int j = 0; j < v; ++j) {
			if (sum[j] < a[j]) {
				ok = 0;
			}
		}
		if (ok) {
			if (cnt < ansc) {
				ansc = cnt;
				ansm = i;
			}
		}
	}

	printf("%d", ansc);

	for (int i = 0; i < g; ++i) {
		if (ansm&(1 << i)) {
			printf(" %d", i + 1);
		}
	}

	printf("\n");
	return 0;
}
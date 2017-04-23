/*
	ID: sparik_1
	LANG: C++
	TASK: wormhole
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

int x[15], y[15];
int rightNeighbour[15];
int n;
int pairing[15];
int badPairings = 0;
int used[15];
int lp;

void go(int v) {
	used[v] = 1;
	if (rightNeighbour[v] != 0) {
		if (used[pairing[rightNeighbour[v]]]) {
			lp = 1;
			return;
		}
		go(pairing[rightNeighbour[v]]);
	}
}

void check() {
	for (int i = 1; i <= n; ++i) {
		for (int j = 1; j <= n; ++j) {
			used[j] = 0;
		}
		lp = 0;
		go(pairing[i]);

		if (lp) {
			++badPairings;
			return;
		}
	}
}

void gen(int ind) {
	if (ind == n + 1) {
		// finished pairing
		check();
		return;
	}

	if (pairing[ind] != 0) {
		// already paired
		gen(ind + 1);
		return;
	}

	for (int i = 1; i <= n; ++i) {
		if (pairing[i] != 0 || i == ind) {
			continue;
		}

		// pair ind-i
		pairing[ind] = i;
		pairing[i] = ind;

		gen(ind + 1);

		pairing[ind] = 0;
		pairing[i] = 0;
	}
}

int main() {
	freopen("wormhole.in", "r", stdin);
	freopen("wormhole.out", "w", stdout);

	scanf("%d", &n);

	for (int i = 1; i <= n; ++i) {
		scanf("%d %d", &x[i], &y[i]);
	}

	for (int i = 1; i <= n; ++i) {
		int nind = -1;
		int mn = INF;
		for (int j = 1; j <= n; ++j) {
			if (j == i) {
				continue;
			}
			if (y[j] == y[i] && x[j] > x[i]) {
				if (x[j] < mn) {
					mn = x[j];
					nind = j;
				}
			}
		}
		if (nind != -1) {
			rightNeighbour[i] = nind;
		}
	}

	gen(1);

	printf("%d\n", badPairings);
	return 0;
}
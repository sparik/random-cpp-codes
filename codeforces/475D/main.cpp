#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <set>
#include <map>
#include <queue>
#include <stack>
#include <deque>
#include <vector>
#include <string.h>
#include <math.h>
#include <cassert>
using namespace std;

#define INF 1000000000
#define lint long long
#define pb push_back
#define mp make_pair
#define MOD 1000000007


inline int gcd(int a, int b) {
	while (b) {
		a %= b;
		swap(a, b);
	}

	return a;
}


int a[100005];
int t[100005][20];
int deg[100005];
map <int, lint> m;

int get(int l, int r) {
	int sz = r - l + 1;
	return gcd(t[l][deg[sz]], t[r - (1 << deg[sz]) + 1][deg[sz]]);
}

int main() {
	int n, q, p = 1;

	scanf("%d", &n);
	for (int i = 1; i <= n; ++i) {
		scanf("%d", &a[i]);
	}

	deg[1] = 0;
	for (int i = 2; i <= n; ++i) {
		if ((1 << deg[i - 1])*2 <= i) {
			deg[i] = deg[i - 1] + 1;
		}
		else {
			deg[i]=deg[i-1];
		}
	}

	for (int i = 1; i <= n; ++i) {
		t[i][0] = a[i];
	}

	for (int j = 1; j <= deg[n]; ++j) {
		for (int i = 1; i <= n; ++i) {
			if (i + (1 << j) - 1 > n) break;
			t[i][j] = gcd(t[i][j - 1], t[i + (1 << (j - 1))][j - 1]);
		}
	}

	for (int i = 1; i <= n; ++i) {
		int g = a[i], ind=i;
		while (ind <= n) {
			int l = ind, r = n + 1;
			while (r - l > 1) {
				int mid = (r + l) / 2;
				if (get(i, mid) < g){
					r = mid;
				}
				else {
					l = mid;
				}
			}
			m[g] += (r - ind);
			ind = r;
			g = get(i, ind);
		}
	}

	int x;
	scanf("%d", &q);

	while (q--) {
		scanf("%d", &x);
		printf("%lld\n", m[x]);
	}
	return 0;
}

// sparse_table, data_structures, rmq, gcd, math, offline
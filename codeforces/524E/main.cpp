#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <set>
#include <map>
#include <queue>
#include <stack>
#include <deque>
#include <vector>
#include <cassert>
#include <string>
using namespace std;

#define INF 1000000000
#define lint long long
#define pb push_back
#define mp make_pair
#define MOD 1000000007

struct query {
	int lx, rx, ly, ry, ind;
};

vector <int> rows[100005], cols[100005];
vector <query> qrow[100005], qcol[100005];

int t[400005][2];
int ansx[200005], ansy[200005];


int get(int v, int l, int r, int li, int ri, int ind) {
	if (li > r || ri < l)
		return INF;
	if (li >= l && ri <= r)
		return t[v][ind];
	int al = get(2 * v, l, r, li, (li + ri) / 2, ind);
	int ar = get(2 * v + 1, l, r, (li + ri) / 2 + 1, ri, ind);
	return min(al, ar);
}

void update(int v, int val, int ind) {
	t[v][ind] = val;
	v /= 2;
	while (v) {
		t[v][ind] = min(t[2 * v][ind], t[2 * v + 1][ind]);
		v /= 2;
	}
}

int main() {
	int n, m, k, q;

	scanf("%d %d %d %d", &m, &n, &k, &q);

	for (int i = 1; i <= k; ++i) {
		int x, y;
		scanf("%d %d", &y, &x);
		rows[x].pb(y);
		cols[y].pb(x);
	}

	for (int i = 1; i <= q; ++i) {
		query Q;
		scanf("%d %d %d %d", &Q.ly, &Q.lx, &Q.ry, &Q.rx);
		Q.ind = i;
		qrow[Q.rx].pb(Q);
		qcol[Q.ry].pb(Q);
	}


	int px = 1;
	while (px < m) {
		px *= 2;
	}

	for (int i = 1; i <= n; ++i) {
		for (int j = 0; j < rows[i].size(); ++j) {
			update(rows[i][j] + px - 1, i, 0);
		}
		for (int j = 0; j < qrow[i].size(); ++j) {
			query Q = qrow[i][j];
			int cur = get(1, Q.ly + px - 1, Q.ry + px - 1, px, px + px - 1, 0);
			ansx[Q.ind] = (cur >= Q.lx);
		}
	}

	int py = 1;
	while (py < n) {
		py *= 2;
	}

	for (int i = 1; i <= m; ++i) {
		for (int j = 0; j < cols[i].size(); ++j) {
			update(cols[i][j] + py - 1, i, 1);
		}
		for (int j = 0; j < qcol[i].size(); ++j) {
			query Q = qcol[i][j];
			int cur = get(1, Q.lx + py - 1, Q.rx + py - 1, py, py + py - 1, 1);
			ansy[Q.ind] = (cur >= Q.ly);
		}
	}

	for (int i = 1; i <= q; ++i) {
		if (ansx[i] || ansy[i]) {
			printf("YES\n");
		}
		else {
			printf("NO\n");
		}
	}
	return 0;
}

// segment_tree, offline, offline_queries, data_structures
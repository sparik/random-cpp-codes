/*

ID: sparik_1
LANG: C++
TASK: castle

*/

#include <cmath>
#include <stdio.h>
#include <ctime>
#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <algorithm>
#include <queue>
using namespace std;

#define INF 1000000000
#define lint long long
#define pb push_back
#define mp make_pair

int a[55][55];
int cmp;
int u[55][55];
int cmpsz[55*55];

int dx[4] = {0, -1, 0, 1};
int dy[4] = {-1, 0, 1, 0};

void dfs(int x, int y) {
	u[x][y] = cmp;
	++cmpsz[cmp];
	for (int i = 0; i < 4; ++i) {
		int nx = x + dx[i];
		int ny = y + dy[i];

		if (u[nx][ny]) {
			continue;
		}

		if (a[x][y]&(1 << i)) {
			continue;
		}

		dfs(nx, ny);
	}
} 

int main() {
	freopen("castle.in", "r", stdin);
	freopen("castle.out", "w", stdout);

	int m, n;
	scanf("%d %d", &m, &n);

	for (int i = 1; i <= n; ++i) {
		for (int j = 1; j <= m; ++j) {
			scanf("%d", &a[i][j]);
		}
	}

	for (int i = 1; i <= n; ++i) {
		for (int j = 1; j <= m; ++j) {
			if (!u[i][j]) {
				++cmp;
				dfs(i, j);
			}
		}
	}

	printf("%d\n", cmp);

	int mxcmp = 0;
	for (int i = 1; i <= cmp; ++i) {
		mxcmp = max(mxcmp, cmpsz[i]);
	}

	printf("%d\n", mxcmp);

	int mx = 0, ansi = -1, ansj = -1, ansk = -1;

	for (int j = 1; j <= m; ++j) {
		for (int i = n; i > 0; --i) {
			for (int k = 1; k < 3; ++k) {
				int nx = i + dx[k];
				int ny = j + dy[k];
				if (nx < 1 || ny > m) {
					continue;
				}
				if (u[i][j] == u[nx][ny]) {
					continue;
				}
				int cur = cmpsz[u[i][j]] + cmpsz[u[nx][ny]];
				if (cur > mx) {
					mx = cur;
					ansi = i;
					ansj = j;
					ansk = k;
				}
			}
		}
	}

	printf("%d\n%d %d %c\n", mx, ansi, ansj, (ansk == 1) ? 'N' : 'E');
    return 0;
}
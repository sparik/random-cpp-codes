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

char a[1005][1005];
int used[1005][1005];
int dx[4] = {0,-1,0,1}, dy[4] = {-1,0,1,0};
int px[1005][1005], py[1005][1005];
int ans = INF, n, m, si, sj, C = 0;

void check(int h, int w)
{
	int spx = si;
	int spy = sj;
	int cnt = h*w;

	while (1) {
		int gr=((spy + w - 1 < m) && a[spx][spy + w] == 'X');
		int gd=((spx + h - 1 < n) && a[spx + h][spy] == 'X');

		if (gr && gd) {
			return ;
		}

		int numr = (py[spx + h - 1][spy + w] - py[spx - 1][spy + w]),
			numd = (px[spx + h][spy + w - 1] - px[spx + h][spy - 1]);

		if (gr) {
			if (numr == h) {
				cnt += numr;
				++spy;
				continue;
			}
			else {
				return ;
			}
		}
		else if (gd) {
			if (numd == w) {
				cnt += numd;
				++spx;
				continue;
			}
			else {
				return ;
			}
		}
		if (numr + numd != 0) {
			return ;
		}
		else {
			break;
		}
	}
	if (cnt < C) {
		return ;
	}
	if (h*w < ans) {
		ans = h*w;
	}

}
int main()
{
	scanf("%d %d",&n,&m);

	for (int i = 1; i <= n; ++i) {
		scanf("%s", a[i] + 1);
	}

	for (int i = 1; i <= n; ++i) {
		for (int j = 1; j <= m; ++j) {
			px[i][j] = px[i][j - 1] + (a[i][j] == 'X');
			py[i][j] = py[i - 1][j] + (a[i][j] == 'X');
			if (a[i][j] == 'X') {
				++C;
				if (si == 0) {
					si = i;
					sj = j;
				}
			}
		}
	}

	queue <pair<int,int> > q;
	q.push(mp(si, sj));
	used[si][sj] = 1;

	while (!q.empty()) {
		int curx=q.front().first,cury=q.front().second;
		q.pop();

		for (int i = 0; i < 4; ++i) {
			int nx = curx + dx[i], ny = cury + dy[i];
			if (nx <= n && nx >= 1 && ny <= m
				 && ny >= 1 && used[nx][ny] == 0 && a[nx][ny] != '.') {
				used[nx][ny] = 1;
				q.push(mp(nx, ny));
			}
		}
	}

	for (int i = 1; i <= n; ++i) {
		for (int j = 1; j <= m; ++j) {
			if (used[i][j] == 0 && a[i][j] != '.') {
				printf("-1");
				return 0;
			}
		}
	}


	int kx=1, ky=1;
	int x = si, y = sj;

	for (int i = y + 1; i <= m; ++i) {
		if (a[x][i] == '.') break;
		++ky;
	}

	for (int i = x + 1; i <= n; ++i) {
		if (a[i][y] == '.')	break;
		++kx;
	}

	for (int i = 1; i <= kx; ++i) {
		check(i, ky);
	}

	for (int i = 1; i <= ky; ++i) {
		check(kx, i);
	}

	if (ans == INF) {
		ans = -1;
	}
	
	printf("%d", ans);
	return 0;
}

// constructive, greedy
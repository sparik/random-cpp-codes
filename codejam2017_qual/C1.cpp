#include <stdio.h>
#include <iostream>
#include <string.h>
using namespace std;

const int INF = 1000000000;

typedef long long lint;

int d[1005];
int l[1005];
int r[1005];

int T;

void solve() {

	printf("Case #%d: ", ++T);

	lint n, k;
	scanf("%lld %lld", &n, &k);

	for (int i = 1; i <= n; ++i) {
		l[i] = i;
		r[i] = n + 1 - i;
	}

	for (int i = 1; i <= k; ++i) {
		int ind = -1;
		int mn = -INF;
		int mnmx = 0;
		for (int j = 1; j <= n; ++j) {
			if (l[j] == INF) {
				continue;
			}
			int ls = l[j];
			int rs = r[j];
			if (min(ls, rs) > mn) {
				mn = min(ls, rs);
				ind = j;
				mnmx = max(ls, rs);
			}
			else {
				if (mn == min(ls, rs)) {
					if (mnmx < max(ls, rs)) {
						mnmx = max(ls, rs);
						ind = j;
					}
				}
			}
		}

		if (i == k) {
			printf("%d %d\n", r[ind] - 1, l[ind] - 1);
			return;
		}

		l[ind] = INF;
		r[ind] = INF;
		for (int j = ind + 1; j <= n; ++j) {
			if (l[j] == INF) {
				break;
			}
			l[j] = j - ind;
		}
		for (int j = ind - 1; j > 0; --j) {
			if (r[j] == INF) {
				break;
			}
			r[j] = ind - j;
		}
	}
}

int main() {
	int tc;
	scanf("%d", &tc);

	while (tc--) {
		solve();
	}
	return 0;
}

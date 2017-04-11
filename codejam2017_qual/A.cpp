#include <stdio.h>
#include <iostream>
#include <string.h>
using namespace std;

char s[1005];
int k;
int T;

void solve() {
	scanf(" %s %d", s + 1, &k);

	int n = strlen(s + 1);

	int cnt = 0;

	for (int i = 1; i <= n; ++i) {
		if (i + k - 1 > n) {
			break;
		}
		if (s[i] == '-') {
			for (int j = i; j < i + k; ++j) {
				if (s[j] == '-') {
					s[j] = '+';
				}
				else {
					s[j] = '-';
				}
			}
			++cnt;
		}
	}

	for (int i = 1; i <= n; ++i) {
		if (s[i] == '-') {
			cnt = -1;
			break;
		}
	}

	printf("Case #%d: ", ++T);
	if (cnt == -1) {
		printf("IMPOSSIBLE\n");
	}
	else {
		printf("%d\n", cnt);
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
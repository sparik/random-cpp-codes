#include <stdio.h>
#include <iostream>
#include <string.h>
#include <set>
using namespace std;

const int INF = 1000000000;

typedef long long lint;


int T;

void solve() {

	printf("Case #%d: ", ++T);

	lint n, k;
	scanf("%lld %lld", &n, &k);

	lint ans = -1;
	while (1) {
		if (k == 1) {
			ans = n;
			break;
		}

		lint lsz, rsz;
		if (n % 2 == 0) {
			lsz = (n - 1) / 2;
			rsz = n / 2;
		}
		else {
			lsz = n / 2;
			rsz = n / 2;
		}

		if (k % 2 == 0) {
			k /= 2;
			n = rsz;
		}
		else {
			k /= 2;
			n = lsz;
		}
	}

	lint l, r;
	if (ans % 2 == 0) {
		l = (ans - 1) / 2;
		r = ans / 2;
	}
	else {
		l = ans / 2;
		r = ans / 2;
	}

	printf("%lld %lld\n", max(l, r), min(l, r));

}

int main() {
	int tc;
	scanf("%d", &tc);

	while (tc--) {
		solve();
	}
	return 0;
}
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

	multiset<lint> s;

	s.insert(n);

	for (int i = 1; i <= k; ++i) {
		lint sz = *(--s.end());

		s.erase(--s.end());

		lint lsz;
		lint rsz;
		if (sz % 2 == 0) {
			lsz = (sz - 1) / 2;
			rsz = sz / 2;

			if (lsz != 0) {
				s.insert(lsz);
			}
			if (rsz != 0) {
				s.insert(rsz);
			}
		}
		else {
			lsz = (sz - 1) / 2;
			rsz = (sz - 1) / 2;

			if (lsz != 0) {
				s.insert(lsz);
			}
			if (rsz != 0) {
				s.insert(rsz);
			}
		}

		if (i == k) {
			printf("%lld %lld\n", max(rsz, lsz), min(lsz, rsz));
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
#include <stdio.h>
#include <iostream>
#include <string.h>
using namespace std;

typedef long long lint;

int check(int *a, int l, int r) {
	for (int i = l; i < r; ++i) {
		if (a[i] < a[i + 1]) {
			return 0;
		}
	}
	return 1;
}

lint cnum(int *a, int l, int r) {
	lint ret = 0;

	for (int i = r; i >= l; --i) {
		ret = 10 * ret + a[i];
	}

	return ret;
}

int T;

void solve() {

	printf("Case #%d: ", ++T);

	lint n;

	scanf("%lld", &n);

	int a[20];
	int l = 0;

	while (n) {
		a[++l] = n % 10;
		n /= 10;
	}

	if (check(a, 1, l)) {
		printf("%lld\n", cnum(a, 1, l));
		return;
	}

	for (int i = 1; i <= l; ++i) {
		if (a[i] == 0) {
			continue;
		}

		int b[20];
		for (int j = 1; j <= l; ++j) {
			b[j] = a[j];
		}
		--b[i];
		for (int j = i - 1; j > 0; --j) {
			b[j] = 9;
		}

		if (check(b, 1, l)) {
			printf("%lld\n", cnum(b, 1, l));
			return;
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
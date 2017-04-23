/*

ID: sparik_1
LANG: C++
TASK: frac1

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

int gcd(int a, int b) {
	while (b) {
		a %= b;
		swap(a, b);
	}

	return a;
}

struct frac {
	int x, y;

	frac(int a, int b) {
		x = a;
		y = b;
	}
};

bool operator == (const frac &a, const frac &b) {
	return a.x*b.y == b.x*a.y;
}

bool operator < (const frac &a, const frac &b) {
	return a.x*b.y < b.x*a.y;
}

vector <frac> f;

int main() {
	freopen("frac1.in", "r", stdin);
	freopen("frac1.out", "w", stdout);

	int n;
	scanf("%d", &n);

	for (int i = 1; i <= n; ++i) {
		for (int j = 0; j <= i; ++j) {
			if (gcd(j, i) > 1) {
				continue;
			}
			f.pb(frac(j, i));
		}
	}

	sort(f.begin(), f.end());

	// unique(f.begin(), f.end());

	for (int i = 0; i < f.size(); ++i) {
		printf("%d/%d\n", f[i].x, f[i].y);
	}
    return 0;
}
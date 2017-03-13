#include <iostream>
#include <algorithm>
#include <cstring>
#include <cassert>
#include <cstdio>
#include <stack>
#include <string>
#include <vector>
#include <queue>
#include <cmath>
#include <time.h>
#include <map>
#include <set>

using namespace std;

#define INF 1000000000
#define MOD 1000000007
#define MP make_pair
#define PB push_back

typedef long long lint;
typedef unsigned long long ulint;

int ind[1000005];
int revind[1000005];
int a[1000005];
int b[1000005];

void solution() {
	int n;
	scanf("%d", &n);

	vector <vector<int> > res;
	set <pair<int, int> > ends;
	set <pair<int, int> > :: iterator it;

	int pp = 0;
	for (int i = 1; i <= n; ++i) {
		scanf("%d", &a[i]);
		ind[a[i]] = ++pp;
		revind[pp] = a[i];
	}

	for (int i = 1; i <= n; ++i) {
		scanf("%d", &b[i]);
		b[i] = ind[b[i]];
	}

	for (int i = 1; i <= n; ++i) {
		it = ends.upper_bound(MP(-b[i], 0));
		if (it == ends.end()) {
			vector<int> nv;
			nv.PB(revind[b[i]]);
			res.PB(nv);
			ends.insert(MP(-b[i], res.size() - 1));
		}
		else {
			int vind = it->second;
			res[vind].PB(revind[b[i]]);
			ends.erase(it);
			ends.insert(MP(-b[i], vind));
		}
	}

	printf("%d\n", res.size());
	for (int i = 0; i < res.size(); ++i) {
		printf("%d", res[i].size());
		for (int j = 0; j < res[i].size(); ++j) {
			printf(" %d", res[i][j]);
		}
		printf("\n");
	}
}

int main() {

	int tc;

	scanf("%d", &tc);

	while (tc--) {
		solution();
	}

	return 0;
}
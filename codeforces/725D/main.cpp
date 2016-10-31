#include <iostream>
#include <vector>
#include <algorithm>
#include <set>
#include <stack>
#include <queue>
#include <map>
#include <string>
#include <cmath>
#include <stdio.h>
using namespace std;

#define lint long long
#define INF 1000000000
#define MOD 1000000007
#define pb push_back
#define mp make_pair

lint a[300005], w[300005];
priority_queue <pair<lint, lint> > s;
priority_queue <lint> b;

int main() {
    int n;
    scanf("%d", &n);

    scanf("%lld %lld", &a[1], &w[1]);
    for (int i = 2; i <= n; ++i) {
        scanf("%lld %lld", &a[i], &w[i]);
        if (a[i] <= a[1]) {
            s.push(mp(a[i], w[i]));
        }
        else {
            b.push(a[i] - w[i] - 1);
        }
    }

    int ans = b.size() + 1;

    while (a[1]) {
        if (b.size() == 0) {
            break;
        }

        lint cur = b.top();
        b.pop();

        if (a[1] >= -cur) {
            a[1] += cur;
        }
        else {
            break;
        }

        while (s.size() > 0 && s.top().first > a[1]) {
            b.push(s.top().first - s.top().second - 1);
            s.pop();
        }

        ans = min(ans, (int)b.size() + 1);
    }

    printf("%d", ans);
    return 0;
}

// priority_queue, greedy
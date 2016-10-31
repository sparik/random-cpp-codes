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
using namespace std;

#define INF 1000000000
#define lint long long
#define pb push_back
#define mp make_pair
#define MOD 1000000007

int d[2005][2050][2], a[2005];
int main()
{
    int n, k;

    scanf("%d %d", &n, &k);

    for (int i = 1; i <= n; ++i) {
        scanf("%d", &a[i]);
    }

    if (a[1] == 2) {
        d[1][1 << 0][0] = 1;
    }
    else if (a[1] == 4) {
        d[1][1 << 1][0] = 1;
    }
    else {
        d[1][1 << 0][0] = 1;
        d[1][1 << 1][0] = 1;
    }

    int ans = 0;
    for (int i = 2; i <= n; ++i) {
        for (int j = 1; j < (1 << k); ++j) {
            for (int f = 0; f < 2; ++f) {
                if (a[i] == 4 || a[i] == 0) {
                    if (j&1) {
                        d[i][1 << 1][f] += d[i - 1][j][f];
                        d[i][1 << 1][f] %= MOD;
                    }
                    else {
                        int mask = j;
                        for (int b = 1; b < 15; ++b) {
                            if ((j&(1 << b))) {
                                mask -= (1 << b);
                            }
                            else {
                                mask += (1 << b);
                                break;
                            }
                        }

                        mask = min(mask, (1 << k) - 1);
                        if (mask >= (1 << (k - 1))) {
                            d[i][mask][1] += d[i - 1][j][f];
                            d[i][mask][1] %= MOD;
                        }
                        else {
                            d[i][mask][f] += d[i - 1][j][f];
                            d[i][mask][f] %= MOD;
                        }
                    }
                }
                if (a[i] == 2 || a[i] == 0) {
                    int mask = j;
                    for (int b = 0; b < 15; ++b) {
                        if ((j&(1 << b))) {
                            mask -= (1 << b);
                        }
                        else {
                            mask += (1 << b);
                            break;
                        }
                    }

                    mask = min(mask, (1 << k) - 1);
                    if (mask >= (1 << (k - 1))) {
                        d[i][mask][1] += d[i - 1][j][f];
                        d[i][mask][1] %= MOD;
                    }
                    else {
                        d[i][mask][f] += d[i - 1][j][f];
                        d[i][mask][f] %= MOD;
                    }
                }
            }
        }
    }

    for (int i = 0; i < (1 << k); ++i) {
        ans += d[n][i][1];
        ans %= MOD;
    }
    
    printf("%d", ans);
    return 0;
}

// bitmask_dp; dp
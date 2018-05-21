#include <stdio.h>
#include <string.h>
#include <algorithm>
#include <iostream>
using namespace std;

pair<int, int> a[100005];
int res[100005];
int n;

/*
void troubleSort() {
    int done = 0;

    while (!done) {
        done = true;

        for (int i = 0; i < n - 2; ++i) {
            if (b[i] > b[i + 2]) {
                swap(b[i], b[i + 2]);
                done = false;
            }
        }
    }

    for (int i = 0; i < n; ++i) {
        cout << b[i] << " ";
    }
    cout << endl;
}
*/


int main() {

    int tc;
    int T = 0;

    scanf("%d", &tc);


    while (tc--) {

        scanf("%d", &n);

        for (int i = 0; i < n; ++i) {
            scanf("%d", &a[i].first);
            a[i].second = i % 2;
        }

        sort(a, a + n);

        int i0 = 0;
        int i1 = 1;
        for (int i = 0; i < n; ++i) {
            if (a[i].second == 0) {
                res[i0] = a[i].first;
                i0 += 2;
            }
            else {
                res[i1] = a[i].first;
                i1 += 2;
            }
        }

        int ans = -1;
        for (int i = 0; i < n - 1; ++i) {
            if (res[i] > res[i + 1]) {
                ans = i;
                break;
            }
        }
        
        
        if (ans == -1) {
            printf("Case #%d: OK\n", ++T);
        }
        else {
            printf("Case #%d: %d\n", ++T, ans);
        }
    }

    return 0;
}
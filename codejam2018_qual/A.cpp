#include <stdio.h>
#include <string.h>

int main() {

    int tc;
    int T = 0;

    scanf("%d", &tc);

    while (tc--) {
        int d;
        char p[30];
        scanf("%d %s", &d, p);

        int n = strlen(p);

        int a[31];

        for (int i = 0; i <= 30; ++i) {
            a[i] = 0;
        }



        int s = 0;
        int total = 0;
        for (int i = 0; i < n; ++i) {
            if (p[i] == 'C') {
                ++s;
            }
            else {
                ++a[s];
                total += (1 << s);
            }
        }

        int ans = 0;
        while (total > d) {
            ++ans;
            int found = -1;
            for (int i = 30; i > 0; --i) {
                if (a[i] != 0) {
                    found = i;
                    break;
                }
            }

            if (found == -1) {
                ans = -1;
                break;
            }

            --a[found];
            ++a[found - 1];
            total -= (1 << (found - 1));
        }


        if (ans == -1) {
            printf("Case #%d: IMPOSSIBLE\n", ++T);
        }
        else {
            printf("Case #%d: %d\n", ++T, ans);
        }
    }

    return 0;
}
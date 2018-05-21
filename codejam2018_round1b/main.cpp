#include <stdio.h>
#include <iostream>
#include <algorithm>
#include <set>
using namespace std;

#define MP make_pair

const int INF = 1000000000;
const double eps = 1e-8;


int d[100005];
int a[100005];
int b[100005];

int main() {

    int tc;
    scanf("%d", &tc);

    int T = 0;

    while (tc--) {
       
        int n;

        scanf("%d", &n);

        for (int i = 0; i < n; ++i) {
            scanf("%d %d %d", &d[i], &a[i], &b[i]);
        }

        int max_len = 0;
        int cnt_max = 0;

        for (int i = 0; i < n; ++i) {
            int N = d[i] + a[i];
            int M;
            int m_chosen = 0;
            int cur_len = -1;

            for (int j = i; j < n; ++j) {
                //cout << j << " " << d[j] + a[j] << " " << d[j] - b[j] << endl;
                if (d[j] + a[j] != N) {
                    if (!m_chosen) {
                        M = d[j] - b[j];
                        m_chosen = 1;
                    }
                    else {
                        if (d[j] - b[j] != M) {
                            cur_len = j - i;
                            break;
                        }
                    }
                }
            }

            if (cur_len == -1) {
                cur_len = n - i;
            }

            int a_len = cur_len;

            int n_chosen = 0;
            cur_len = -1;
            M = d[i] - b[i];
            N = 0;

            for (int j = i; j < n; ++j) {
                //cout << j << " " << d[j] + a[j] << " " << d[j] - b[j] << endl;
                if (d[j] - b[j] != M) {
                    if (!n_chosen) {
                        N = d[j] + a[j];
                        n_chosen = 1;
                    }
                    else {
                        if (d[j] + a[j] != N) {
                            cur_len = j - i;
                            break;
                        }
                    }
                }
            }

            if (cur_len == -1) {
                cur_len = n - i;
            }

            cur_len = max(cur_len, a_len);

            //cout << i << " x " << cur_len << endl;

            if (cur_len > max_len) {
                max_len = cur_len;
                cnt_max = 1;
            }
            else if (cur_len == max_len) {
                ++cnt_max;
            }
        }

        printf("Case #%d: %d %d\n", ++T, max_len, cnt_max);
    }

    return 0;
}

/*

3
1
1 1 1
5
2 7 12
6 3 11
8 10 1
11 11 12
13 9 14
5
1 3 3
2 2 2
3 1 1
4 2 2
5 3 3

*/
#include <stdio.h>
#include <string.h>
#include <algorithm>
#include <iostream>
#include <math.h>
using namespace std;

int lx, ly;
int rx, ry;

int a[205][205];

void find_best_rect(int &x, int &y) {
    int mn = 10;
    for (int i = lx + 1; i <= rx - 1; ++i) {
        for (int j = ly + 1; j <= ry - 1; ++j) {
            int cur = a[i - 1][j - 1] + a[i - 1][j] + a[i - 1][j + 1]
             + a[i][j - 1] + a[i][j] + a[i][j + 1]
             + a[i + 1][j - 1] + a[i + 1][j] + a[i + 1][j + 1];

            if (cur < mn) {
                mn = cur;
                x = i;
                y = j;
            }
        }
    }
}

int main() {

    int tc;
    scanf("%d", &tc);

    while (tc--) {
        int A;
        scanf("%d", &A);

        for (int i = 1; i <= 200; ++i) {
            for (int j = 1; j <= 200; ++j) {
                a[i][j] = 0;
            }
        }

        lx = 100;
        ly = 100;

        if (A == 20) {
            rx = 104;
            ry = 103;
        }
        else {
            rx = 109;
            ry = 119;
        }

        int rem_moves = 1000;
        int done = 0;
        int cnt = 0;

        while (!done) {
            if (rem_moves == 0) {
                return 0;
            }
            --rem_moves;

            int i, j;
            find_best_rect(i, j);

            cout << i << " " << j << endl;

            int x, y;
            cin >> x >> y;

            if (x + y == -2) {
                return 0;
            }

            if (x + y == 0) {
                done = 1;
            }
            else {
                if (a[x][y] == 0) {
                    ++cnt;
                }
                a[x][y] = 1;
            }
        }
    }

    return 0;
}
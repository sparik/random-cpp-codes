#include <stdio.h>
#include <string.h>
#include <algorithm>
#include <iostream>
#include <math.h>
using namespace std;

const double sqrt2 = 1.41421356237;
const double sqrt3 = 1.73205080757;
const double PI = 3.14159265359;

double findRotX(double A) {
    double l = 0, r = PI / 4.0;

    int it = 100;

    while (it--) {
        double mid = (l + r) / 2;
        double area = sin(mid) + cos(mid);
        if (area < A) {
            l = mid;
        }
        else {
            r = mid;
        }
    }

    return r;
}

double findRotY(double A) {
    double l = 0, r = acos(sqrt2 / sqrt3) / 2.0;

    int it = 100;

    while (it--) {
        double mid = (l + r) / 2;
        double area;
        double rectArea = sqrt2 * cos(2 * mid);
        double triArea = sqrt2 * sqrt2 / 4.0 * sin(2 * mid);

        area = rectArea + triArea * 2;

        if (area < A) {
            l = mid;
        }
        else {
            r = mid;
        }
    }

    return r;
}

void rot(double theta, double &x, double &y) {
    double resx = x * cos(theta) - y * sin(theta);
    double resy = x * sin(theta) + y * cos(theta);

    x = resx;
    y = resy;
}

int main() {

    int tc;
    int T = 0;

    cin >> tc;

    while (tc--) {

        double xs[3] = {0.5, 0, 0};
        double ys[3] = {0, 0.5, 0};
        double zs[3] = {0, 0, 0.5};

        double A;
        cin >> A;

        double rotx = 0, roty = 0;
        if (A <= sqrt2) {
            rotx = findRotX(A);
        }
        else {
            rotx = PI / 4.0;
            roty = findRotY(A);
        }


        for (int i = 0; i < 3; ++i) {
            rot(rotx, xs[i], ys[i]);
        }

        for (int i = 0; i < 3; ++i) {
            rot(roty, zs[i], ys[i]);
        }

        printf("Case #%d:\n", ++T);

        for (int i = 0; i < 3; ++i) {
            printf("%.9f %.9f %.9f\n", xs[i], ys[i], zs[i]);
        }
    }

    return 0;
}
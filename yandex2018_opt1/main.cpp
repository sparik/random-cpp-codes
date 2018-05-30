#include <stdio.h>
#include <iostream>
#include <algorithm>
#include <vector>
#include <set>
#include <map>
#include <queue>
#include <string>
#include <cmath>

using namespace std;

#define MP make_pair
#define PB push_back

const int INF = 1000000000;

struct pt {
    int x;
    int y;

    pt() {
        x = 0;
        y = 0;
    }

    pt(int xx, int yy) {
        x = xx;
        y = yy;
    }

    void print() {
        printf("{x: %d, y: %d}\n", x, y); 
    }

    void setXandY(int xx, int yy) {
        x = xx;
        y = yy;
    }

    long long dist(const pt &other) const {
        return (x - other.x) *1ll* (x - other.x) + (y - other.y) *1ll* (y - other.y);
    }
};

bool operator < (const pt &a, const pt &b) {
    if (a.x != b.x) {
        return a.x < b.x;
    }
    return a.y < b.y;
}

pt taxiDest[21];
int isTaxiFree[21];
pt taxiPassengerPt[21];
pt taxis[21];
pt zones[21];
int T, P, Z;
int initialX[21], initialY[21];

struct passenger {
    pt loc;
    int status; // 0 - waiting, 1 - in taxi, 2 - in zone
    int bestZone;
    int bestTaxi;

    void recalc() {
        int minDist2 = INF;
        bestTaxi = -1;
        for (int j = 0; j < T; ++j) {
            int curDist2 = taxis[j].dist(loc);
            if (!isTaxiFree[j]) {
                continue;
            }
            if (bestTaxi == -1 || minDist2 > curDist2) {
                bestTaxi = j;
                minDist2 = curDist2;
            }
        }

        minDist2 = 0;
        bestZone = -1;
        for (int j = 0; j < Z; ++j) {
            int curDist2 = zones[j].dist(loc);
            if (bestZone == -1 || minDist2 > curDist2) {
                bestZone = j;
                minDist2 = curDist2;
            }
        }
    }
};

bool operator < (const passenger &a, const passenger &b) {
    return a.loc.dist(taxis[a.bestTaxi]) < b.loc.dist(taxis[b.bestTaxi]);
}

passenger passengers[501];

map <pt, int> M;

struct taxi_move {
    int dx;
    int dy;
    vector <int> taxis;
};

vector <taxi_move> answer;

int ddx[4] = {1, 0, -1, 0};
int ddy[4] = {0, 1, 0, -1};

double mult_coeff = 0;

#if 1
int closestPassengerDist(pt p) {
    int minDist2 = INF;
    for (int i = 0; i < P; ++i) {
        if (passengers[i].status != 0) {
            continue;
        }
        if (minDist2 == -1 || minDist2 > p.dist(passengers[i].loc)) {
            minDist2 = p.dist(passengers[i].loc);
        }
    }

    return minDist2;
}
#endif



int outside(int x, int y) {
    return x < -10000 || x > 10000 || y < -10000 || y > 10000;
}

void doMove(int dx, int dy, int tidx, bool moveOthers=true) {
    vector <int> movedTaxis;
    movedTaxis.PB(tidx);

    pt newLoc = {taxis[tidx].x + dx, taxis[tidx].y + dy};

    if (outside(newLoc.x, newLoc.y)) {
        throw std::invalid_argument("jsgkjkgjsa");
    }

    if (dx == 0 && dy == 0) {
        return;
    }

    

    if (M[newLoc]) {
        int taxiToMove = M[newLoc] - 1;


        int minDist2 = -1;
        int si = -10, sj = -10;
        for (int i = -5; i <= 5; ++i) {
            for (int j = -5; j <= 5; ++j) {
                int nx = taxis[taxiToMove].x + i;
                int ny = taxis[taxiToMove].y + j;

                if (outside(nx, ny)) {
                    continue;
                }

                if (M[{nx, ny}]) {
                    continue;
                }

                int curDist2 = i*i + j*j;
                if (minDist2 == -1 || curDist2 < minDist2) {
                    minDist2 = curDist2;
                    si = i;
                    sj = j;
                }
            }
        }


        if (si == -10) {
            throw std::invalid_argument("kajfkjaig");
        }
        doMove(si, sj, taxiToMove, false);
    }

    for (int i = 0; i < T; ++i) {
        if (!moveOthers) {
            break;
        }
        if (tidx == i) {
            continue;
        }

        int curMinDist2 = closestPassengerDist(taxis[i]);

        newLoc = {taxis[i].x + dx, taxis[i].y + dy};

        if (outside(newLoc.x, newLoc.y)) {
            continue;
        }

        if (M[newLoc]) {
            continue;
        }

        int dist2 = dx * dx + dy * dy;

        if (taxiDest[i].x != INF) {
            if (taxiDest[i].dist(newLoc) * 1.0 * T + dist2 * mult_coeff < taxiDest[i].dist(taxis[i]) * 1.0 * T) {
                movedTaxis.PB(i);
            }
        }
        else {
            if (closestPassengerDist(newLoc) * (1.0 + mult_coeff) < curMinDist2) {
                movedTaxis.PB(i);
            }
        }

        
    }

    for (int i = 0; i < movedTaxis.size(); ++i) {
        M[taxis[movedTaxis[i]]] = 0;
    }

    for (int i = 0; i < movedTaxis.size(); ++i) {
        taxis[movedTaxis[i]].x += dx;
        taxis[movedTaxis[i]].y += dy;
        M[taxis[movedTaxis[i]]] = movedTaxis[i] + 1;
    }

    answer.PB({dx, dy, movedTaxis});
}

int rnd = 0;
int fl = 0;

void solve() {
    answer.clear();
    M.clear();

    for (int i = 0; i < T; ++i) {
        taxis[i] = {initialX[i], initialY[i]};
        isTaxiFree[i] = 1;
        taxiDest[i] = {INF, INF};
    }

    for (int i = 0; i < P; ++i) {
        passengers[i].recalc();
        passengers[i].status = 0;
    }

    while (true) {


        sort(passengers, passengers + P);

        if (rnd) {
            int cnt = min(2, P);
            random_shuffle(passengers, passengers + cnt);
        }

        for (int i = 0; i < T; ++i) {
            if (isTaxiFree[i]) {
                taxiDest[i] = {INF, INF};
            }
        }

        int bestTaxi = -1;
        int minDist2 = INF;

        bool changed = true;
        while (changed) {
            changed = false;
            for (int i = 0; i < P; ++i) {
                if (passengers[i].status != 0) {
                    continue;
                }

                if (taxiDest[passengers[i].bestTaxi].x == INF) {
                    taxiDest[passengers[i].bestTaxi] = passengers[i].loc;
                    changed = true;
                }
            }

            if (fl) {
                break;
            }

            for (int i = 0; i < P; ++i) {
                passengers[i].recalc();
            }
        }

        for (int i = 0; i < T; ++i) {
            if (taxiDest[i].x == INF) {
                continue;
            }
            if (taxis[i].dist(taxiDest[i]) < minDist2) {
                minDist2 = taxis[i].dist(taxiDest[i]);
                bestTaxi = i;
            }
        }


        if (bestTaxi == -1) {
            break;
        }

        int bestPassenger = -1;
        pt passengerLoc;

        if (!isTaxiFree[bestTaxi]) {
            passengerLoc = taxiPassengerPt[bestTaxi];
        }
        else {
            passengerLoc = taxiDest[bestTaxi];
        }

        for (int i = 0; i < P; ++i) {
            if (passengers[i].status == 2) {
                continue;
            }

            if (passengers[i].loc.x == passengerLoc.x && passengers[i].loc.y == passengerLoc.y) {
                bestPassenger = i;
                break;
            }
        }

        //cout << bestTaxi << " y " << bestPassenger << endl;
        //cout << "passenger status " << passengers[bestPassenger].status << endl;
        int deltaX = taxiDest[bestTaxi].x - taxis[bestTaxi].x;
        int deltaY = taxiDest[bestTaxi].y - taxis[bestTaxi].y;


        doMove(deltaX, deltaY, bestTaxi);

        ++passengers[bestPassenger].status;

        if (passengers[bestPassenger].status == 1) {
            isTaxiFree[bestTaxi] = 0;
            taxiPassengerPt[bestTaxi] = passengers[bestPassenger].loc;
            taxiDest[bestTaxi] = zones[passengers[bestPassenger].bestZone];
        }
        else {
            isTaxiFree[bestTaxi] = 1;
            taxiPassengerPt[bestTaxi] = {INF, INF};
            taxiDest[bestTaxi] = {INF, INF};
        }

        for (int i = 0; i < P; ++i) {
            if (passengers[i].status == 2) {
                continue;
            }

            passengers[i].recalc();
        }
        //cout << endl << endl;

    }
}

vector <taxi_move> bestAnswer;
long long bestScore = INF*1ll*INF;

void updateAnswer() {
    double score = 0;

    for (size_t i = 0; i < answer.size(); ++i) {
        score += sqrt(answer[i].dx * answer[i].dx + answer[i].dy * answer[i].dy) * (T + (int)answer[i].taxis.size());
    }

    if (score < bestScore) {
        bestAnswer = answer;
        bestScore = score;
    }
}



int main() {

    scanf("%d", &T);

    for (int i = 0; i < T; ++i) {
        scanf("%d %d", &taxis[i].x, &taxis[i].y);
        M[taxis[i]] = i + 1;
        initialX[i] = taxis[i].x;
        initialY[i] = taxis[i].y;
    }

    scanf("%d", &P);

    for (int i = 0; i < P; ++i) {
        scanf("%d %d", &passengers[i].loc.x, &passengers[i].loc.y);
        passengers[i].status = 0;
        passengers[i].bestZone = -1;
        passengers[i].bestTaxi = -1;
    }

    scanf("%d", &Z);

    for (int i = 0; i < Z; ++i) {
        scanf("%d %d", &zones[i].x, &zones[i].y);
    }

    for (fl = 0; fl <= 1; ++fl) {

        rnd = 0;
        mult_coeff = 0;
        solve();
        updateAnswer();

        mult_coeff = 1;
        solve();
        updateAnswer();

        mult_coeff = 0.5;
        solve();
        updateAnswer();

        mult_coeff = 0.8;
        solve();
        updateAnswer();


        rnd = 1;

        mult_coeff = 0;
        solve();
        updateAnswer();

        mult_coeff = 1;
        solve();
        updateAnswer();

        mult_coeff = 0.5;
        solve();
        updateAnswer();

        mult_coeff = 0.8;
        solve();
        updateAnswer();

    }
    




    answer = bestAnswer;

    printf("%lu\n", answer.size());

    for (size_t i = 0; i < answer.size(); ++i) {
        printf("MOVE %d %d %lu", answer[i].dx, answer[i].dy, answer[i].taxis.size());

        for (size_t j = 0; j < answer[i].taxis.size(); ++j) {
            printf(" %d", answer[i].taxis[j] + 1);
        }

        printf("\n");
    }

    cout << bestScore << endl;
    return 0;
}
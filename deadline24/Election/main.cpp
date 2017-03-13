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

vector <int> At[10003];
vector <int> Af[10005];
vector <int> Bt[10003];
vector <int> Bf[10004];
set <int> gs[10004];
int A1[10004], A2[10004], i1[10004], i2[10004], c[10003];
int q1 = 0, q0 = 0;
bool mark[10004];
bool marks[10004];
vector <int> to_sat;

vector <int> g[10005];
int used[10005];
vector <int> A, B;

// color v's component in two colors
void do_partition(int v, int c) {
	used[v] = 1;
	if (c == 0) {
		A.PB(v);
	}
	else {
		B.PB(v);
	}
	for (int i = 0; i < g[v].size(); ++i) {
		int to = g[v][i];
		if (used[to]) {
			continue;
		}

		do_partition(to, 1 - c);
	}
}

int mt[10005];
int isMatched[10005];

bool try_kuhn(int v) {
	if (used[v]) {
		return false;
	}
	used[v] = true;
	for (int i = 0; i < g[v].size(); ++i) {
		int to = g[v][i];
		if (mt[to] == -1 || try_kuhn (mt[to])) {
			mt[to] = v;
			return true;
		}
	}
	return false;
}

set <pair<int, int> > matching;
int inZ[10005];
int inA[10005];
int inB[10005];

// mark every vertex reachable from v by an alternating path
// alternating path = path where matching edges and non-matching edges alternate
void mark_alternating_paths(int v, int kogh) {
	used[v] = 1;
	inZ[v] = 1;

	for (int i = 0; i < g[v].size(); ++i) {
		int to = g[v][i];
		if (used[to]) {
			continue;
		}
		pair<int, int> e1 = MP(v, to);
		pair<int, int> e2 = MP(to, v);

		bool in_matching = true;
		if (matching.find(e1) == matching.end() && matching.find(e2) == matching.end()) {
			in_matching = false;
		}

		if (kogh == -1) {
			mark_alternating_paths(to, (int)in_matching);
		}
		else if (kogh == 0) {
			if (in_matching) {
				mark_alternating_paths(to, (int)in_matching);
			}
		}
		else {
			if (!in_matching) {
				mark_alternating_paths(to, (int)in_matching);
			}
		}
	}
}

int minVCover[10005];

// finds the min-vertex-cover of v's component
// every component is bipartite
void solve(int v) {
	A.clear();
	B.clear();
	matching.clear();

	do_partition(v, 0);

	for (int i = 0; i < B.size(); ++i) {
		isMatched[B[i]] = 0;
	}
	for (int i = 0; i < A.size(); ++i) {
		isMatched[A[i]] = 0;
	}

	
	// find maximum matching
	for (int i = 0; i < B.size(); ++i) {
		mt[B[i]] = -1;
	}

	for (int i = 0; i < A.size(); ++i) {
		for (int j = 0; j < A.size(); ++j) {
			used[A[j]] = 0;
		}
		try_kuhn(A[i]);
	}
 
	for (int i = 0; i < B.size(); ++i) {
		if (mt[B[i]] != -1) {
			isMatched[mt[B[i]]] = 1;
			isMatched[B[i]] = 1;
			matching.insert(MP(B[i], mt[B[i]]));
			matching.insert(MP(mt[B[i]], B[i]));
		}
	}

	for (int i = 0; i < A.size(); ++i) {
		used[A[i]] = 0;
	}
	for (int i = 0; i < B.size(); ++i) {
		used[B[i]] = 0;
	}

	// construct min-cover
	for (int i = 0; i < A.size(); ++i) {
		if (!isMatched[A[i]]) {
			if (!used[A[i]]) {
				mark_alternating_paths(A[i], -1);
			}
		}
	}

	for (int i = 0; i < A.size(); ++i) {
		used[A[i]] = 1;
	}
	for (int i = 0; i < B.size(); ++i) {
		used[B[i]] = 1;
	}

	for (int i = 0; i < A.size(); ++i) {
		inA[A[i]] = 1;
	}
	for (int i = 0; i < B.size(); ++i) {
		inB[B[i]] = 1;
	}

	for (int i = 0; i < A.size(); ++i) {
		if (!inZ[A[i]]) {
			minVCover[A[i]] = 1;
		}
	}
	for (int i = 0; i < B.size(); ++i) {
		if (inZ[B[i]]) {
			minVCover[B[i]] = 1;
		}
	}
}

int main() {
    int T;
    scanf("%d", &T);
    while(T--) {
        to_sat.clear();
        for(int i = 0; i < 10002; ++i) {
            mark[i] = false;
            marks[i] = false;
            inA[i] = 0;
            inB[i] = 0;
            inZ[i] = 0;
            used[i] = 0;
            isMatched[i] = 0;
            mt[i] = 0;
            minVCover[i] = 0;
            g[i].clear();
            gs[i].clear();
            At[i].clear();
            Af[i].clear();
            Bt[i].clear();
            Bf[i].clear();
        }
        int n, a, b;
        scanf("%d%d%d", &n, &a, &b);
        for(int i = 0; i < n; ++i) {
            int iT, iF, nt, nf;
            scanf("%d%d%d%d", &iT, &nt, &iF, &nf);
            i1[i] = iT;
            A1[i] = nt;
            i2[i] = iF;
            A2[i] = nf;
            if(iT == 1){
                At[nt].push_back(i);
                Bf[nf].push_back(i);
            }
            else {
                Af[nf].push_back(i);
                Bt[nt].push_back(i);
            }
        }
        for(int i = 0; i < n; ++i) {
            if(i1[i] == 1) {
                for(int j = 0; j < Af[A1[i]].size(); j++) {
                    gs[i].insert(Af[A1[i]][j]);
                }
                for(int j = 0; j < Bt[A2[i]].size(); j++) {
                    gs[i].insert(Bt[A2[i]][j]);
                }
            }
            else{
                for(int j = 0; j < Bf[A1[i]].size(); j++) {
                    gs[i].insert(Bf[A1[i]][j]);
                }
                for(int j = 0; j < At[A2[i]].size(); j++) {
                    gs[i].insert(At[A2[i]][j]);
                }
            }

            set <int>::iterator it;
            for (it = gs[i].begin(); it != gs[i].end(); ++it) {
            	g[i].PB(*it);
            }
        }

        for (int i = 0; i < n; ++i) {
        	if (!used[i]) {
        		solve(i);
        	}
        }

        vector <int> to_sat;
        for (int i = 0; i < n; ++i) {
        	if (!minVCover[i]) {
        		to_sat.PB(i);
        	}
        }

        // construct the answer
        set <int> ans1;
        set <int> ans2;
        for(int i = 0; i < to_sat.size(); ++i){
            int v = to_sat[i];
            if(i1[v] == 1) {
                ans1.insert(A1[v]);
            }
            else {
                ans2.insert(A1[v]);
            }
        }
        
        printf("%d\n", ans1.size());
        set <int>::iterator it;
        for(it=ans1.begin(); it != ans1.end(); ++it) {
            printf("%d ", *it);
        }
        printf("\n%d\n", ans2.size());
        for(it=ans2.begin(); it != ans2.end(); ++it) {
            printf("%d ", *it);
        }
        printf("\n");

    }
    return 0;
}

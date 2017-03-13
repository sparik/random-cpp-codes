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
#include <fstream>
#include <set>

using namespace std;

#define INF 1000000000
#define MOD 1000000007
#define MP make_pair
#define PB push_back

typedef long long lint;
typedef unsigned long long ulint;


int buf[200]; // number of each char in the buffer
int values[200];   // score of each letter
char field[55][55]; // the crossword field
int overall_score = 0;  // result score
int m, n; // dimensions of the crossword
int used[200000]; // used[n] = true if n-th word is already used

// vector of {{start_y, start_x}, {word, orientation('V' or 'H')}}
vector <pair<pair<int, int>, pair<string, char> > > overral_result;


bool avail(int x, int y){
    if (x < 0 || y < 0) return true;
    if (x >= n || y >= m) return true;
    char c = field[x][y];
    return (c == '.' || c == '5' || c == '4' || c == '2' || c == '3');
}

// check if a word can be constructed with the current buffer
bool buf_word(const string& word) {
    int cnt_letter[200];

    for (int i = 0; i < 200; ++i) {
        cnt_letter[i] = 0;
    }

    for (int i = 0; i < word.size(); ++i) {
        ++cnt_letter[word[i]];
    }

    for (int i = 0; i < 200; ++i) {
        if (cnt_letter[i] > buf[i]) {
            return false;
        }
    }
    return true;
}

// true if the first word is already placed
bool first_done = false;

// try to put a word on the crossword in the best possible way
// and return score, or -1 if not possible
lint put_word(const string &word) {
    lint max_score = -1;

    char O = 0;
    int ri = -1;
    int rj = -1;

    for(int i = 0; i <= n - (int)word.size(); ++i){
        for(int j = 0; j < m; ++j) {
            lint cur_score;
            cur_score = 0;

            bool ok = true;
            bool hatvela = false;

            if (!avail(i - 1, j)) {
                ok = false;
            }

            lint wm = 1;
            for(int k = 0; k < word.size(); ++k) {
                int cm = 1;
                if(field[i + k][j] == '2') {
                    cm = 2;
                    if (!avail(i + k, j - 1) || !avail(i + k, j + 1)) {
                        ok = false;
                        break;
                    }
                }
                else if(field[i+k][j] == '3') {
                    cm = 3;
                    if (!avail(i + k, j - 1) || !avail(i + k, j + 1)) {
                        ok = false;
                        break;
                    }
                }
                else if(field[i+k][j] == '4') {
                    wm *= 2;
                    if (!avail(i + k, j - 1) || !avail(i + k, j + 1)) {
                        ok = false;
                        break;
                    }
                }
                else if (field[i + k][j] == '5') {
                    wm *= 3;
                    if (!avail(i + k, j - 1) || !avail(i + k, j + 1)) {
                        ok = false;
                        break;
                    }
                }
                else if (field[i + k][j] != '.') {
                    hatvela = true;
                    if (field[i + k][j] != word[k]) {
                        ok = false;
                        break;
                    }
                    if (!avail(i + k + 1, j)) {
                        ok = false;
                        break;
                    }
                }
                else {
                    if (!avail(i + k, j - 1) || !avail(i + k, j + 1)) {
                        ok = false;
                        break;
                    }
                }
                cur_score += cm * values[word[k]];
            }

            if (!avail(i + word.size(), j)) {
                ok = false;
            }

            if (first_done) ok &= hatvela;

            if (ok) {
                cur_score *= wm;
                if (cur_score > max_score) {
                    max_score = cur_score;
                    O = 'V';
                    ri = i;
                    rj = j;
                }
            }
        }
    }

    for(int i = 0; i < n; ++i){
        for(int j = 0; j <= m - (int)word.size(); ++j) {
            lint cur_score;
            cur_score = 0;

            bool ok = true;
            bool hatvela = false;

            if (!avail(i, j - 1)) {
                ok = false;
            }
            lint wm = 1;
            for(int k = 0; k < word.size(); ++k) {
                int cm = 1;
                if(field[i][j + k] == '2') {
                    cm = 2;
                    if (!avail(i - 1, j + k) || !avail(i + 1, j + k)) {
                        ok = false;
                        break;
                    }
                }
                else if(field[i][j + k] == '3') {
                    cm = 3;
                    if (!avail(i - 1, j + k) || !avail(i + 1, j + k)) {
                        ok = false;
                        break;
                    }
                }
                else if(field[i][j + k] == '4') {
                    wm *= 2;
                    if (!avail(i - 1, j + k) || !avail(i + 1, j + k)) {
                        ok = false;
                        break;
                    }
                }
                else if (field[i][j + k] == '5') {
                    wm *= 3;
                    if (!avail(i - 1, j + k) || !avail(i + 1, j + k)) {
                        ok = false;
                        break;
                    }
                }
                else if (field[i][j + k] != '.') {
                    hatvela = true;
                    if (field[i][j + k] != word[k]) {
                        ok = false;
                        break;
                    }
                    if (!avail(i, j + k + 1)) {
                        ok = false;
                        break;
                    }
                }
                else {
                    if (!avail(i - 1, j + k) || !avail(i + 1, j + k)) {
                        ok = false;
                        break;
                    }
                }
                cur_score += cm * values[word[k]];
            }

            if (!avail(i, j + word.size())) {
                ok = false;
            }

            if (first_done) ok &= hatvela;
            if (ok) {
                cur_score *= wm;
                if (cur_score > max_score) {
                    max_score = cur_score;
                    O = 'H';
                    ri = i;
                    rj = j;
                }
            }
        }
    }

    if (max_score == -1) {
        return -1;
    }

    if (O == 'H') {
        for (int i = 0; i < word.size(); ++i) {
            field[ri][rj + i] = word[i];
        }
    }
    else {
        for (int i = 0; i < word.size(); ++i) {
            field[ri + i][rj] = word[i];
        }
    }

    overral_result.PB(MP(MP(rj, ri), MP(word, O)));

    return max_score;
}

// puts the word on the crossword and returns 1
// or fails and returns 0
int go(const string &word) {
    if (buf_word(word) == false) {
        return 0;
    }

    int addedScore = put_word(word);
    if (addedScore == -1) {
        return 0;
    }
    else {
        overall_score += addedScore;
        for (int i = 0; i < word.size(); ++i) {
            --buf[word[i]];
        }
        return 1;
    }
}

int main() {
    int T;
    scanf("%d", &T);
    while(T--) {
        int D;
        vector <pair<int , string> > words;
        string dictfilename = "dict";

        scanf("%d", &D);
        dictfilename += char(D + '0');
        dictfilename += ".in";


        scanf("%d %d", &m, &n);

        for(int i = 0; i < n; ++i) {
            for(int j = 0; j < m; ++j) {
                scanf(" %c", &field[i][j]);
                // change 'x' and 'X' fields to '4' and '5' to avoid conflict with words
                if (field[i][j] == 'x') {
                    field[i][j] = '4';
                }
                else if (field[i][j] == 'X') {
                    field[i][j] = '5';
                }
            }
        }


        // read score of each letter
        int l;
        scanf("%d", &l);
        for(int i = 0; i < l; ++i) {
            char c;
            int v;
            scanf(" %c %d", &c, &v);
            values[c] = v;
        }

        // read words from dict file and save them in 'words', sorted by score
        // and set all words as unused (used[i] = 0)
        ifstream dict_file;
        dict_file.open(dictfilename.c_str());
        string dictword;
        while(dict_file >> dictword) {
            // min score for current word
            int score = 0;
            for(int i = 0; i < dictword.size(); ++i) {
                score += values[dictword[i]];
            }
            words.push_back(make_pair(-score, dictword));
            used[words.size() - 1] = 0;
        }
        dict_file.close();

        sort(words.begin(), words.end());

        int b,q;
        scanf("%d %d", &b, &q);

        char letterseq[2500];
        scanf(" %s", letterseq);

        for (int i = 0; i < 200; ++i) {
            buf[i] = 0;
        }

        overral_result.clear();
        overall_score = 0;

        int seqind = 0;
        int bufsz = 0;

        first_done = false;
        while(true) {
            // update buffer
            while(seqind < q && bufsz < b) {
                ++bufsz;
                buf[letterseq[seqind++]]++;
            }

            bool couldPlace = false;
            // try to put some word
            for(int i = 0; i < words.size(); ++i) {
                if (used[i]) {
                    continue;
                }
                if (go(words[i].second) == 1) {
                    first_done = true;
                    couldPlace = true;
                    used[i] = 1;
                    break;
                }
            }
            // if couldn't place any word, terminate
            if (!couldPlace) {
                break;
            }
        }

        printf("%d %d\n", overral_result.size(), overall_score);
        for (int i = 0; i < overral_result.size(); ++i) {
            printf("%d %d %s %c\n", overral_result[i].first.first + 1, overral_result[i].first.second + 1,
                overral_result[i].second.first.c_str(), overral_result[i].second.second);
        }
    }

    return 0;
}
#include "bits/stdc++.h"
using namespace std;

string v[67346];

bool init = 0;


void go_init() {
    init = 1;
    FILE* fs = fopen("equations.txt", "r");
    int n;
    fscanf(fs, "%d", &n);
    char gg;
    fscanf(fs, "%c", &gg);
    assert(n == 67346);
    for(int i=0; i<67346; i++) {
        v[i] = "????????";
        for(int j=0; j<8; j++) fscanf(fs, "%c", &v[i][j]);
        fscanf(fs, "%c", &gg);
    }
    fclose(fs);
}

string get_eq(int i) {
    if(init == 0) {
        go_init();
    }
    return v[i];
}

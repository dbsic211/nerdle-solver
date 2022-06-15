#include <bits/stdc++.h>
using namespace std;

string v[67346];

bool init = 0;


void go_init() {
    init = 1;
    freopen("equations.txt", "r", stdin);
    int n;
    cin >> n;
    assert(n == 67346);
    for(int i=0; i<67346; i++) {
        cin >> v[i];
    }
}

string get_eq(int i) {
    if(!init) {
        go_init();
    }
    return v[i];
}

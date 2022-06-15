#include <bits/stdc++.h>
#include "testlib.h"
using namespace std;
int main(int argc, char* argv[]) {
    // This command initializes checker environment.
    registerTestlibCmd(argc, argv);
    
    int qcnt = ouf.readInt();
    if(qcnt <= 6) quitf(_ok, "Full score");
    else if(qcnt > 70000) quitf(_wa, "too many queries");
    else {
        double ok = 100 * (1.0 - sqrt(1.0 - pow((70000 - qcnt) * 1.0 / 69994, 20.0)));
        quitp(_pc(ok - 16), "number of queries = %d", qcnt);
    }
}

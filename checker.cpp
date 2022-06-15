#include <bits/stdc++.h>
#include "testlib.h"
using namespace std;
int main(int argc, char* argv[]) {
    // This command initializes checker environment.
    registerTestlibCmd(argc, argv);
    
    int qcnt = ouf.readInt();
    if(qcnt <= 6) quitf(_ok, "Full score");
    else if(qcnt > 1006) quitf(_wa, "too many queries");
    else {
        double ok = 100 * (1.0 - sqrt(1.0 - (1006 - qcnt) * 1.0 / 1000));
        quitp(_pc(ok - 16), "number of queries = %d", qcnt);
    }
}

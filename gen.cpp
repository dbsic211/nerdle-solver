#include "bits/stdc++.h"
using namespace std;
#define int long long
#ifdef ONLINE_JUDGE
const int MAXN = 3e5 + 10;
#endif
#ifndef ONLINE_JUDGE
const int MAXN = 1029;
#endif
const int MOD = 998244353;
#define ll __int128
mt19937_64 rng((int)std::chrono::steady_clock::now().time_since_epoch().count());
int rnd(int x, int y) {
  int u = uniform_int_distribution<int>(x, y)(rng); return u;
}
ll read() { int x; cin >> x; return (ll)x; }
long long bm(long long b, long long p) {
  if(p==0) return 1 % MOD;
  long long r = bm(b, p >> 1);
  if(p&1) return (((r*r) % MOD) * b) % MOD;
  return (r*r) % MOD;
}
long long inv(long long b) { 
  return bm(b, MOD-2);
}
long long f[MAXN];
long long nCr(int n, int r) { 
  long long ans = f[n]; ans *= inv(f[r]); ans %= MOD;
  ans *= inv(f[n-r]); ans %= MOD; return ans;
}
long long fib[MAXN], lucas[MAXN];
void precomp() { 
  for(int i=0; i<MAXN; i++) f[i] = (i == 0 ? 1 % MOD : (f[i-1] * i) % MOD); 
  lucas[0] = 2;
  lucas[1] = 1;
  for(int i=2; i<MAXN; i++) lucas[i] = (lucas[i-2] + lucas[i-1]) % MOD;
  fib[0] = 0;
  fib[1] = 1;
  for(int i=2; i<MAXN; i++) fib[i] = (fib[i-2] + fib[i-1]) % MOD;
}
int fastlog(int x) {
  return (x == 0 ? -1 : 64 - __builtin_clzll(x) - 1);
}
void gay(int i) { cout << "Case #" << i << ": "; }
int csb(int l, int r, int k) { // count number of [l, r] such that i & 2^k > 0
  if(l > r) return 0;
  if(l == 0) {
    int s = r / (1ll << (k+1)); // number of complete cycles
    int t = r % (1ll << (k+1));
    int ans = s * (1ll << k);
    ans += (t >= (1ll << k) ? t - (1ll << k) + 1 : 0);
    return ans;
  }
  else return csb(0, r, k) - csb(0, l - 1, k);
}
int lis(vector<int> a) {
  int n = a.size();
  int bucket[n+1];
  for(int i=1; i<=n; i++) bucket[i] = 1e18;
  int ans = 1;
  for(int x: a) {
    auto it = lower_bound(bucket + 1, bucket +n +1, x);
    int d = distance(bucket, it);
    ans = max(ans, d);
    bucket[d] = min(bucket[d], x);
  }
  return ans;
}

vector<string> vt;
string chars = "0123456789+-*/";
string cur = "???????????????";

int eval(string expr) { 
  //cout << "eval(" << expr << ") = ";
  string newexpr;
  vector<string> v;
  for(int i=0; i<expr.size(); i++) {
    if(isdigit(expr[i])) {
      int j = i;
      string wow;
      wow += expr[i];
      while(j+1 < expr.size() && isdigit(expr[j+1])) {
        j++;
        wow += expr[j];
      }
      v.push_back(wow);
      i = j;
    }
    else {
      string s;
      s += expr[i];
      v.push_back(s);
    }
  }
  for(int i=0; i<v.size(); i++) {
    if(i+1 < v.size() && (v[i+1] == "*" || v[i+1] == "/")) {
      double cur = stoi(v[i]);
      int sto = i;
      for(int j=i+1; j<v.size(); j+=2) {
        if(v[j] == "+" || v[j] == "-") {
          break;
        }
        if(v[j] == "*") {
          cur *= stoi(v[j+1]);
        }
        else {
          if(v[j+1] == "0") {
            //cout << "-1\n";
            return -1;
          }
          cur *= 1.0 / stoi(v[j+1]);
        }
        i = j;
      }
      i++;
      v[sto] = to_string(cur);
      for(int j=sto+1; j<=i; j+=2) {
        v[j] = "+";
        v[j+1] = "0";
      }
    }
  }
  double ans = stod(v[0]);
  for(int i=1; i<v.size(); i+=2) {
    if(v[i] == "+") {
      ans += stod(v[i+1]);
    }
    else {
      ans -= stod(v[i+1]);
    }
  }
  int ok = -12269;
  for(int i = ans - 2; i <= ans + 2; i++) {
    if(abs(i - ans) <= 1e-7) ok = i;
  }
  if(ok == -12269) {
    //cout << "-1\n";
    return -1;
  }
  //cout << ok << "\n";
  return ok;
}

int fcnt = 0;
void exhaust(int idx, int len, int res) {
  fcnt++;
  if(fcnt % 10000 == 0) cout << fcnt << " exhaust() function calls, progress is around " << fcnt * 100.0 / 86130000 << "%\n";
  if(idx == len) { // S223 again
    if(!isdigit(cur[len - 1])) return;
    if(eval(cur.substr(0, len)) == res) {
      vt.push_back(cur.substr(0, len) + "=" + to_string(res));
    }
    return;
  }
  if((idx == 1 && cur[idx - 1] == '0') || (idx > 1 && cur[idx - 1] == '0' && !isdigit(cur[idx - 2]))) {
    for(int i=10; i<14; i++) {
      cur[idx] = chars[i];
      exhaust(idx + 1, len, res);
    }
  }
  else if(idx == 0 || !isdigit(cur[idx - 1])) {
    for(int i=0; i<10; i++) {
      cur[idx] = chars[i];
      exhaust(idx + 1, len, res);
    }
  }
  else {
    for(int i=0; i<14; i++) {
      cur[idx] = chars[i];
      exhaust(idx + 1, len, res);
    }
  }
}

void solve(int tc) {
  // Program for generating all possible equations
  // = in position 5, 6, 7 only
  // Takes around a minute
  for(int pos = 5; pos <= 7; pos++) {
    int rem = 8 - pos;
    int gg = bm(10, rem);
    int ro = (gg == 10 ? 0 : (gg == 100 ? 10 : 100));
    for(int j=ro; j<gg; j++) {
      exhaust(0, pos - 1, j); 
    }
  }
  freopen("equations.txt", "w", stdout);
  cout << vt.size() << "\n";
  for(string v: vt) cout << v << "\n";
}

int32_t main() {
  precomp();
  ios::sync_with_stdio(0); cin.tie(0);
  int t = 1; cin >> t;
  for(int i=1; i<=t; i++) solve(i);
}
// I don't know geometry.
// Teaming is unfair.
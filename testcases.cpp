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
void solve(int tc) {
  freopen("equations.txt", "r", stdin);
  int n;
  cin >> n;
  vector<string> v(n);
  for(int i=0; i<n; i++) {
    cin >> v[i];
  }
  for(int i=0; i<202; i++) {
    int r = rnd(0, 2);
    if(r == 0) r = rnd(0, 1317);
    else if(r == 1) r = rnd(1318, 12231);
    else r = rnd(12232, n-1);
    string filename = "test" + to_string(i + 1) + ".txt";
    freopen(filename.c_str(), "w", stdout);
    cout << v[r] << "\n";
  }
}
int32_t main() {
  //precomp();
  ios::sync_with_stdio(0); cin.tie(0);
  int t = 1; cin >> t;
  for(int i=1; i<=t; i++) solve(i);
}
// I don't know geometry.
// Teaming is unfair.
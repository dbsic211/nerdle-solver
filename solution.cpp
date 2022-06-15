#include "bits/stdc++.h"
using namespace std;
#include "brute.h"
#define int long long
#ifdef ONLINE_JUDGE
const int MAXN = 3e5 + 10;
#endif
#ifndef ONLINE_JUDGE
const int MAXN = 1029;
#endif
const int MOD = 998244353;
mt19937_64 rng((int)std::chrono::steady_clock::now().time_since_epoch().count());
int rnd(int x, int y) {
  int u = uniform_int_distribution<int>(x, y)(rng); return u;
}
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
 
 
string get_rep(string ans, string guess) {
    string g = "1234567890+-*/=";
    string res = "????????";
    for(char c: g) {
        int cnt[3] = {0, 0, 0};
        for(int i=0; i<8; i++) {
            if(ans[i] == c && guess[i] == c) cnt[0]++;
            else if(ans[i] == c && guess[i] != c) cnt[1]++;
            else if(ans[i] != c && guess[i] == c) cnt[2]++;
        }
        int mm = min(cnt[1], cnt[2]);
        for(int i=0; i<8; i++) {
            if(guess[i] == c) {
                if(ans[i] == c) res[i] = 'G';
                else {
                    if(mm > 0) {
                        mm--;
                        res[i] = 'P';
                    }
                    else {
                        res[i] = 'B';
                    }
                }
            }
        }
        
    }
    for(char c: res) assert(c != '?');
    return res;
}
 
 
void solve(int tc) {
  string v[67346];
  for(int i=0; i<67346; i++) v[i] = get_eq(i);
  string s1, s2, s3;
  s1 = "9+6*8=57";
  s2 = "12/4-0=3";
  s3 = "20*5=100";
  cout << s1 << "\n";
  fflush(stdout);
  string r1, r2, r3;
  cin >> r1;
  cout << s2 << "\n";
  fflush(stdout);
  cin >> r2;
  cout << s3 << "\n";
  fflush(stdout);
  cin >> r3;
  vector<string > s, r;
  s.push_back(s1);
  r.push_back(r1);
  s.push_back(s2);
  r.push_back(r2);
  s.push_back(s3);
  r.push_back(r3);
  for(int i=0; i<67346; i++) {
    bool ok = 1;
    for(int j=0; j<s.size(); j++) ok &= (get_rep(v[i], s[j]) == r[j]);
    if(ok) {
      cout << v[i] << "\n";
      fflush(stdout);
      string re;
      cin >> re;
      if(re == "GGGGGGGG") {
        return;
      }
      s.push_back(v[i]);
      r.push_back(re);
    }
  }
}
 
int32_t main() {
  precomp();
  int t = 1; //cin >> t;
  for(int i=1; i<=t; i++) solve(i);
}
// I don't know geometry.
// Teaming is unfair.

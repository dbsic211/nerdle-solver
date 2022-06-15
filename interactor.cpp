#include <bits/stdc++.h>
#include "testlib.h"
using namespace std;

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

int main(int argc, char* argv[]) {
    // This command initializes checker environment.
    registerInteraction(argc, argv);
    string ans = inf.readToken();
    int qcnt = 0;
    while(1) {
        qcnt++;
        string guess;
        cin >> guess;
        if(guess.size() != 8) {
            quitf(_wa, "guess length not 8");
        }
        for(char c: guess) {
            if(!isdigit(c) && c != '+' && c != '-' && c != '*' && c != '/' && c != '=') {
                quitf(_wa, "guess contains invalid characters");
            }
        }
        int ct = 0;
        for(char c: guess) ct += (c == '=');
        if(ct != 1) quitf(_wa, "guess should only contain one zero");
        for(int i = 0; i<guess.size(); i++) {
            if(guess[i] == '=') {
                if(i < 4 || i > 6) quitf(_wa, "guess does not compute or invalid format: = sign should only be placed in positions 5, 6, 7 (1-based)");
                for(int j=i+1; j<guess.size(); j++) {
                    if(!isdigit(guess[j])) {
                        quitf(_wa, "there should not be non-digit characters to the right of = sign");
                    }
                }
            }
        }
        if(!isdigit(guess[0])) quitf(_wa, "first character should be a digit regardless");
        for(int i=0; i+1<guess.size(); i++) {
            if(!isdigit(guess[i]) && !isdigit(guess[i+1])) quitf(_wa, "there should not be two consecutive non-digit characters");
        }
        if(guess[0] == '0' && isdigit(guess[1])) {
            quitf(_wa, "leading zero not allowed");
        }
        for(int i=0; i+2<guess.size(); i++) {
            if(!isdigit(guess[i]) && guess[i+1] == '0' && isdigit(guess[i+2])) {
                quitf(_wa, "leading zero not allowed");
            }
        }
        string wow;
        int ress;
        for(int i=0; i<guess.size(); i++) {
            if(guess[i] == '=') {
                for(int j=0; j<i; j++) wow += guess[j];
                ress = 0;
                for(int j=i+1; j<guess.size(); j++) {
                    ress *= 10;
                    ress += guess[j] - '0';
                }
                if(eval(wow) != ress) {
                    quitf(_wa, "equation is incorrect (e.g. 1 + 2 = 4 is incorrect)");
                }
                break;
            }
        }
        string rep = get_rep(ans, guess);
        cout << rep << endl << flush;
        if(rep == "GGGGGGGG") {
            tout << qcnt << "\n";
            if(qcnt <= 6) quitf(_ok, "Correct guess");
            else if(qcnt<= 70000) quitp(_pc(16), "Correct guess");
            else quitf(_wa, "Too many queries");
        }
        if(qcnt == 140000) {
            quitf(_wa, "Too many queries, program auto terminated (query count = 140000)");
        }
    }
}
/*
cin: output from contestant
cout: input to contestant
inf.readXXX(): from actual input file
tout: send to checker
*/

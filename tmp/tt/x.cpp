#include <string.h>
#include <iostream>
using namespace std;
const int maxn = 50050;
int Next[maxn], extend[maxn];

void get_Next(char *s) {
  int n = strlen(s);
  int i, j, k;
  for (j = 0; 1 + j < n && s[j] == s[1 + j]; ++j)
    ;
  Next[1] = j;
  k = 1;
  for (i = 2; i < n; ++i) {
    int len = k + Next[k], L = Next[i - k];
    if (L < len - i) {
      Next[i] = L;
    } else {
      for (j = max(0, len - i); i + j < n && s[j] == s[i + j]; ++j)
        ;
      Next[i] = j;
      k = i;
    }
  }
  Next[0] = n;
}
void ex_kmp(char *T, char *s) {
  int n = strlen(T), m = strlen(s);
  int i, j, k;
  for (j = 0; j < n && j < m && T[j] == s[j]; ++j)
    ;
  extend[0] = j;
  k = 0;
  for (i = 1; i < n; ++i) {
    int len = k + extend[k], L = Next[i - k];
    if (L < len - i) {
      extend[i] = L;
    } else {
      for (j = max(0, len - i); j < m && i + j < n && s[j] == T[i + j]; ++j)
        ;
      extend[i] = j;
      k = i;
    }
  }
}

int main() {
  char s[maxn], T[maxn];
  cin >> s >> T;
  get_Next(s);
  ex_kmp(T, s);
  int in = 0;
  for (int i = 0; i < strlen(T); ++i) {
    if (extend[i] > in) {
      in = extend[i];
    }
  }
  for (int i = 0; i < in; i++) {
    cout << s[i];
  }
  if (in != 0) cout << " ";
  cout << in << endl;

  return 0;
}
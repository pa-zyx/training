#include <algorithm>
#include <cmath>
#include <iostream>
using namespace std;

double fR(double P) {
  // 以 P 求 R
  double R =
      0.929108 *
      pow(2.71828, (0.00110424 * P -
                    0.164566 * log(1.40316 + pow(2.71828, 0.00671 * P))));
  return R;
}

double fP(double R) {
  // 以 R 求 P
  double P;
  double lp = 0, rp = 200;
  while (abs(lp - rp) > 1e-5) {
    double mid = (lp + rp) / 2.0;
    if (fR(mid) > R) {
      rp = mid;
    } else {
      lp = mid;
    }
  }
  P = rp;

  return P;
}

double Q(double P) {
  double re = 0.85 * 0.49 * 3.1415926 * sqrt((2 * (160 - P)) / 0.8711);
  return re;
}

double X(int i) {
  if (i < 0 || i > 240) {
    return 0;
  }
  if (i >= 20 && i < 220) {
    return 20 * 0.01;
  } else {
    if (i < 20) {
      return i * 0.01;
    } else {
      return (240 - i) * 0.01;
    }
  }
}

double B(int i, int x) {
  i += x;
  return X(i);
}

double arr[100];
int main() {
  const double V = 500 * 25 * 3.1415926;
  double M = fR(100) * V;
  double P = fP(M / V);
  double dQ = Q(100);
  arr[0] = P;
  for (int i = 1; i <= 350; i++) {
    double inM = Q(P) * 0.01 * fR(P);
    M = M + inM - B(i, -45);
    double R = M / V;
    P = fP(R);
    arr[i] = P;
  }
  double MA = -1, MI = 0x3f3f3f3f;
  for (int i = 0; i <= 350 - 13; i++) {
    cout << arr[i] << " ";
    MA = max(MA, arr[i]);
    MI = min(MI, arr[i]);
  }
  cout << endl;
  cout << MA << " " << MI << " " << MA - MI << endl;
  return 0;
}


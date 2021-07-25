# include <bits/stdc++.h>
using namespace std;
typedef vector<int> vi;
// Ways to write n as a sum of positive numbers.
// parition(4)=5 because 4 = 3 + 1 = 2 + 2 = 2 + 1 + 1 = 1 + 1 + 1 + 1
int partition(int n) {
    if(n==0) return 1;
    assert(n > 0);
    vi dp = vi(n + 1);
    dp[0] = 1;
    for (int i = 1; i <= n; i++) {
        for (int j = 1, r = 1; i - (3 * j * j - j) / 2 >= 0; j++, r *= -1) {
            dp[i] += dp[i - (3 * j * j - j) / 2] * r;
            if (i - (3 * j * j + j) / 2 >= 0) {
                dp[i] += dp[i - (3 * j * j + j) / 2] * r;
            }
        }
    }
    return dp[n];
}
int main() {
    // 0 1, 1 1, 2 2, 3 3, 4 5, 5 7, 6 11, 7 15, 8 22, 9 30, 10 42
    // 11 56, 12 77, 13 101, 14 135, 15 176, 16 231, 17 297
    for (int i = 0; i <= 17; ++i) {
        cout << i << " " << partition(i) << ", ";
    }
    return 0;
}

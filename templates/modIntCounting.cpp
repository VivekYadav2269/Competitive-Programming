#include <bits/stdc++.h>
using i64 = long long;

const int mod = 1E9 + 7;
const int N = 1E6 + 7;

int Add(int x, int y) {
    x += y;
    if (x >= mod) {
        x -= mod;
    }
    return x;
}

int Sub(int x, int y) {
    x -= y;
    if (x < 0) {
        x += mod;
    }
    return x;
}

int Mul(int x, int y) {
    return 1LL * x * y % mod;
}

int Power(int x, int y) {
    int ans = 1;
    for (; y != 0; x = Mul(x, x), y >>= 1) {
        if (y & 1) {
            ans = Mul(ans, x);
        }
    }
    return ans;
}

std::vector <int> Fact(N), Inv(N), invFact(N);

void comb() {
    Fact[0] = 1, Inv[0] = 1, invFact[0] = 1;
    Fact[1] = 1, Inv[1] = 1, invFact[1] = 1;
    for (int i = 2; i < N; i++) {
        Inv[i] = Sub(0, Mul(Inv[mod % i], mod / i));
        Fact[i] = Mul(Fact[i - 1], i);
        invFact[i] = Mul(invFact[i - 1], Inv[i]);
    }
}

int C(int n, int r) {
    if (n < 0 || r < 0 || n < r) {
        return 0;
    }
    return Mul(Fact[n], Mul(invFact[n - r], invFact[r]));
}

void solve() {
    std::array <int, 26> c;
    for (int i = 0; i < 26; i++) {
        std::cin >> c[i];
    }
    
    int n = std::accumulate(c.begin(), c.end(), 0);
    std::vector <int> dp(n / 2 + 1);
    dp[0] = 1;
    for (int i = 0; i < 26; i++) {
        if (c[i] == 0) {
            continue;
        }
        std::vector <int> ndp = dp;
        for (int j = n / 2; j >= c[i]; j--) {
            ndp[j] = Add(ndp[j], dp[j - c[i]]);
        }
        std::swap(dp, ndp);
    }
    
    int inv = 1;
    for (int i = 0; i < 26; i++) {
        inv = Mul(inv, invFact[c[i]]);
    }
    
    int ans = Mul(Mul(Fact[n / 2], Fact[(n + 1) / 2]), Mul(inv, dp[n / 2]));
    std::cout << ans << '\n';
}
 
int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    
    comb();
    
    int t;
    std::cin >> t;
    
    while (t--) {
        solve();
    }
    
    return 0;
}




// Educational Codeforces Round 177 (Rated for Div. 2) Problem - D
// Problem link : https://codeforces.com/problemset/problem/2086/D
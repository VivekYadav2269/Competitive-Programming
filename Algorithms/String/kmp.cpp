#include <bits/stdc++.h>
using i64 = long long;

std::vector <int> LPS(int m, std::string &s) {
    std::vector <int> f(m);
    for (int i = 1; i < m; i++) {
        int j = f[i - 1];
        while (j > 0 && s[j] != s[i]) {
            j = f[j - 1];
        }
        f[i] = j + (s[i] == s[j]);
    }
    return f;
}

std::vector <int> KMP(int n, int m, std::string &s, std::string &p, std::vector <int> &lps) {
    std::vector <int> res;
    for (int i = 0, j = 0; i < n; i++) {
        if (s[i] == p[j]) {
            j++;
        } else {
            if (j) {
                j = lps[j - 1];
                i--;
            }
        }
        if (j == m) {
            res.push_back(i - m + 1);
            j = lps[j - 1];
        }
    }
    return res;
}

void solve() {
    int n, m;
    std::cin >> n >> m;
    
    std::string s, p;
    std::cin >> s >> p;
    
    std::vector <int> lps = LPS(m, p);
    std::vector <int> kmp = KMP(n, m, s, p, lps);
    
    std::cout << kmp.size() << '\n';
    for (int i = 0; i < kmp.size(); i++) {
        std::cout << kmp[i] + 1 << " \n"[i == kmp.size() - 1];
    }
}
    
int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int t;
    std::cin >> t;
 
    while (t--) {
        solve();
    }
    
    return 0;
}
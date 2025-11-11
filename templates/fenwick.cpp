#include <bits/stdc++.h>
using i64 = long long;

template <class T>
struct fenwick {
    int n;
    std::vector <T> f;
    
    fenwick() : n(0) {}
    fenwick(int N) : n(N), f(n + 1, T{}) {}
    fenwick(std::vector <T> const &F) : n(F.size()), f(n + 1, T{}) {
        for (int i = 0; i < n; i++) {
            add(i, F[i]);
        }
    }
    
    void add(int x, const T &F) {
        for (int i = x + 1; i <= n; i += i & -i) {
            f[i] = f[i] + F;
        }
    }
    
    T sum(int x) {
        T res{};
        for (int i = x + 1; i > 0; i -= i & -i) {
            res = res + f[i];
        }
        return res;
    }
    
    T query(int l, int r) {
        return sum(r) - sum(l - 1);
    }
};

void solve() {
    int n, k;
    std::cin >> n >> k;

    std::vector <int> a(n);
    for (int i = 0; i < n; i++) {
        std::cin >> a[i];
    }

    std::vector <int> pre(n + 1);
    for (int i = 0; i < n; i++) {
        pre[i + 1] = pre[i] + (a[i] == k ? 1 : -1);
    }

    int cc = *std::min_element(pre.begin(), pre.end());
    cc = -cc;
    int m = *std::max_element(pre.begin(), pre.end()) + cc + 1;
    fenwick <int> fn(m);
    pre[0] = cc;
    for (int i = 0; i < n; i++) {
        pre[i + 1] += cc;
        fn.add(pre[i + 1], 1);
    }

    i64 ans = 0;
    for (int i = 0; i < n; i++) {
        ans += fn.query(std::min(pre[i] + 1, m), m - 1);
        fn.add(pre[i + 1], -1);
    }
    std::cout << ans << '\n';
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

// Problem statement : You are given an integer array a and an integer k.
// Return the number of subarrays of nums in which target is the majority element.
// The majority element of a subarray is the element that appears strictly more than half of the times in that subarray.

// constraints :
// 1 <= t <= 10 ^ 4
// 1 <= n <= 10 ​​​​​​^ ​5
// 1 <= a[i] <= 10 ^ ​​​​​​​9
// 1 <= k <= 10 ^ 9
// The sum of n over all test cases does not exceed 10 ^ 5.
#include <bits/stdc++.h>
using i64 = long long;

struct DSU {
    std::vector <int> p, size;
    int component_count;
 
    DSU() : component_count(0) {}
    DSU(int n) {
        init(n);
    }
 
    void init(int n) {
        p.resize(n);
        std::iota(p.begin(), p.end(), 0);
        size.assign(n, 1);
        component_count = n;
    }
 
    void reset(int n) {
        p.clear();
        size.clear();
        init(n);
    }
 
    int find(int x) {
        if (x == p[x]) {
            return x;
        }
        return p[x] = find(p[x]);
    }
 
    bool same(int x, int y) {
        return find(x) == find(y);
    }
 
    void merge(int x, int y) {
        x = find(x);
        y = find(y);
        if (x == y) {
            return;
        }
 
        if (size[x] >= size[y]) {
            p[y] = x;
            size[x] += size[y];
        } else {
            p[x] = y;
            size[y] += size[x];
        }
        component_count--;
    }
 
    int Size(int x) {
        return size[find(x)];
    }
 
    int count_components() const {
        return component_count;
    }
};

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    
    int n, q;
    std::cin >> n >> q;
    
    DSU dsu(n);
    std::vector <int> b(n);
    std::vector <int> B(n);
    for (int i = 0; i < q; i++) {
        int type;
        std::cin >> type;
        
        if (type == 1) {
            int u, v;
            std::cin >> u >> v;
            u--, v--;
            int U = b[dsu.find(u)], V = b[dsu.find(v)];
            if (!dsu.same(u, v)) {
                b[dsu.find(u)] = 0;
                b[dsu.find(u)] = 0;
                dsu.merge(u, v);
                b[dsu.find(u)] = U + V;
            }
        } else if (type == 2) {
            int v;
            std::cin >> v;
            v--;
            if (B[v] == 0) {
                B[v] = 1;
                b[dsu.find(v)]++;
            } else {
                B[v] = 0;
                b[dsu.find(v)]--;
            }
        } else {
            int v;
            std::cin >> v;
            v--;
            std::cout << (b[dsu.find(v)] > 0 ? "Yes" : "No") << '\n';
        }
    }
    
    return 0;
}

// Problem link : https://atcoder.jp/contests/abc420/tasks/abc420_e
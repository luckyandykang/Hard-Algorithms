#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const int MAXN = 1 << 20;

ll tree[4 * MAXN];
ll lazy[4 * MAXN];
int n, q;

#define mid (s + e >> 1)

void build(int node, int s, int e, vector<ll> &a) {
    if (s == e) {
        tree[node] = a[s];
        return;
    }
    build(node * 2, s, mid, a);
    build(node * 2 + 1, mid + 1, e, a);
    tree[node] = tree[node * 2] + tree[node * 2 + 1];
}

void propagate(int node, int s, int e) {
    if (lazy[node] == 0) return;
    tree[node] += (ll)(e - s + 1) * lazy[node];
    if (s != e) {
        lazy[node * 2] += lazy[node];
        lazy[node * 2 + 1] += lazy[node];
    }
    lazy[node] = 0;
}

void update(int node, int s, int e, int l, int r, ll val) {
    propagate(node, s, e);
    if (r < s || e < l) return;
    if (l <= s && e <= r) {
        lazy[node] += val;
        propagate(node, s, e);
        return;
    }
    update(node * 2, s, mid, l, r, val);
    update(node * 2 + 1, mid + 1, e, l, r, val);
    tree[node] = tree[node * 2] + tree[node * 2 + 1];
}

ll query(int node, int s, int e, int l, int r) {
    propagate(node, s, e);
    if (r < s || e < l) return 0;
    if (l <= s && e <= r) return tree[node];
    return query(node * 2, s, mid, l, r) + query(node * 2 + 1, mid + 1, e, l, r);
}

int main() {
    cin.tie(0)->sync_with_stdio(false);

    int m;
    cin >> n >> m;
    q = m;

    vector<ll> a(n + 1);
    for (int i = 1; i <= n; i++) cin >> a[i];
    build(1, 1, n, a);

    for (int i = 0; i < m; i++) {
        int type;
        cin >> type;
        if (type == 1) {
            int l, r;
            ll val;
            cin >> l >> r >> val;
            update(1, 1, n, l, r, val);
        } else {
            int l, r;
            cin >> l >> r;
            cout << query(1, 1, n, l, r) << '\n';
        }
    }

    return 0;
}

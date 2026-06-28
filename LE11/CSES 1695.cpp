#include <bits/stdc++.h>
using namespace std;

typedef long long int INT;

typedef long long ll;
typedef tuple<int, ll, ll> edge;
typedef vector<int> vi;
typedef pair<int, int> ii;

const ll INF = 1e18;

class max_flow {
public:
    int V;
    vector<edge> EL;
    vector<vi> AL;
    vi d, last;
    vector<ii> p;

    bool BFS(int s, int t) {
        d.assign(V, -1);
        d[s] = 0;
        queue<int> q({s});
        p.assign(V, {-1, -1});
        while (!q.empty()) {
            int u = q.front(); q.pop();
            if (u == t) break;
            for (auto &idx : AL[u]) {
                auto &[v, cap, flow] = EL[idx];
                if ((cap - flow > 0) && (d[v] == -1)) {
                    d[v] = d[u] + 1;
                    q.push(v);
                    p[v] = {u, idx};
                }
            }
        }
        return d[t] != -1;
    }

    ll send_one_flow(int s, int t, ll f = INF) {
        if (s == t) return f;
        auto &[u, idx] = p[t];
        auto &cap = get<1>(EL[idx]);
        auto &flow = get<2>(EL[idx]);
        ll pushed = send_one_flow(s, u, min(f, cap - flow));
        flow += pushed;
        auto &rflow = get<2>(EL[idx ^ 1]);
        rflow -= pushed;
        return pushed;
    }

    ll DFS(int u, int t, ll f = INF) {
        if ((u == t) || (f == 0)) return f;
        for (int &i = last[u]; i < (int)AL[u].size(); ++i) {
            auto &[v, cap, flow] = EL[AL[u][i]];
            if (d[v] != d[u] + 1) continue;
            if (ll pushed = DFS(v, t, min(f, cap - flow))) {
                flow += pushed;
                auto &rflow = get<2>(EL[AL[u][i] ^ 1]);
                rflow -= pushed;
                return pushed;
            }
        }
        return 0;
    }

    max_flow(int initialV) : V(initialV) {
        EL.clear();
        AL.assign(V, vi());
    }

    void add_edge(int u, int v, ll w, bool directed = true) {
        if (u == v) return;
        EL.emplace_back(v, w, 0);
        AL[u].push_back(EL.size() - 1);
        EL.emplace_back(u, directed ? 0 : w, 0);
        AL[v].push_back(EL.size() - 1);
    }

    ll edmonds_karp(int s, int t) {
        ll mf = 0;
        while (BFS(s, t)) {
            ll f = send_one_flow(s, t);
            if (f == 0) break;
            mf += f;
        }
        return mf;
    }

    ll dinic(int s, int t) {
        ll mf = 0;
        while (BFS(s, t)) {
            last.assign(V, 0);
            while (ll f = DFS(s, t))
                mf += f;
        }
        return mf;
    }
};

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;

    max_flow mf(n);

    int a, b;
    for (int i = 0; i < m; i++){
        cin >> a >> b;
        a--; b--;
        mf.add_edge(a, b, 1, false);
    }

    cout << mf.dinic(0, n - 1) << "\n";

    vector<bool> visited(n, false);
    queue<INT> q;
    q.push(0);
    visited[0] = true;

    while (!q.empty()) {
        INT u = q.front(); q.pop();
        for (auto &idx : mf.AL[u]) {
            auto &[v, cap, flow] = mf.EL[idx];
            if (cap - flow > 0 && !visited[v]) {
                visited[v] = true;
                q.push(v);
            }
        }
    }

    for (INT u = 0; u < n; ++u) {
        for (auto &idx : mf.AL[u]) {
            if (idx % 2 == 0) {
                INT v = get<0>(mf.EL[idx]);
                if (visited[u] != visited[v]) {
                    cout << u + 1 << " " << v + 1 << "\n";
                }
            }
        }
    }

    return 0;
}
#include <bits/stdc++.h>
using namespace std;

typedef long long int INT;

INT k = 0;

typedef long long ll;
typedef tuple<INT, ll, ll> edge;
typedef vector<INT> vi;
typedef pair<INT, INT> ii;

const ll INF = 1e18;

class max_flow {
public:
    bool dfsCaminho(INT u, INT t, stack<INT>& st, vector<bool>& vis) {
        if (u == t) {
            st.push(u);
            return true;
        }
        vis[u] = true; 
        for (auto &idx : AL[u]) {
            if (idx % 2 != 0) continue; 
            auto &[v, cap, flow] = EL[idx];
            if (flow == 1 && !vis[v]) { 
                if (dfsCaminho(v, t, st, vis)) {
                    flow = 0; 
                    st.push(u);
                    return true;
                }
            }
        }
        vis[u] = false; 
        return false;
    }

    void obterCaminhos(INT s, INT t, INT fluxo_total) {
        caminhos.resize(fluxo_total);
        for (INT i = 0; i < fluxo_total; ++i) {
            vector<bool> vis(V, false); 
            dfsCaminho(s, t, caminhos[i], vis);
        }
    }

    INT V;
    vector<edge> EL;
    vector<vi> AL;
    vi d, last;
    vector<ii> p;
    vector<stack<INT>> caminhos;

    bool BFS(INT s, INT t) {
        d.assign(V, -1);
        d[s] = 0;
        queue<INT> q({s});
        p.assign(V, {-1, -1});
        while (!q.empty()) {
            INT u = q.front(); q.pop();
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

    ll send_one_flow(INT s, INT t, ll f = INF) {
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

    ll DFS(INT u, INT t, ll f = INF) {
        if ((u == t) || (f == 0)) return f;
        for (INT &i = last[u]; i < (INT)AL[u].size(); ++i) {
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

    max_flow(INT initialV) : V(initialV) {
        EL.clear();
        AL.assign(V, vi());
    }

    void add_edge(INT u, INT v, ll w, bool directed = true) {
        if (u == v) return;
        EL.emplace_back(v, w, 0);
        AL[u].push_back(EL.size() - 1);
        EL.emplace_back(u, directed ? 0 : w, 0);
        AL[v].push_back(EL.size() - 1);
    }

    ll edmonds_karp(INT s, INT t) {
        ll mf = 0;
        while (BFS(s, t)) {
            k++;
            ll f = send_one_flow(s, t);
            if (f == 0) break;
            mf += f;
        }
        obterCaminhos(s, t, k); 

        return mf;
    }

    ll dinic(INT s, INT t) {
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

    INT n, m;
    cin >> n >> m;

    max_flow mf(n);

    INT a, b;
    for (INT i = 0; i < m; i++){
        cin >> a >> b;
        a--; b--;
        mf.add_edge(a, b, 1);
    }

    mf.edmonds_karp(0, n - 1);

    cout << k << "\n";

    for (INT i = 0; i < mf.caminhos.size(); i++){
        cout << mf.caminhos[i].size() << "\n";
        while (!mf.caminhos[i].empty()){
            cout << mf.caminhos[i].top() + 1 << " ";
            mf.caminhos[i].pop();
        }
        cout << "\n";
    }

    return 0;
}
#include <bits/stdc++.h>
using namespace std;

typedef long long int INT;

pair<INT, INT> bfs(INT startNode, INT n, const vector<vector<INT>>& adj) {
    vector<INT> dist(n, -1);
    queue<INT> q;

    dist[startNode] = 0;
    q.push(startNode);

    INT farthestNode = startNode;
    INT maxDist = 0;

    while (!q.empty()) {
        INT u = q.front();
        q.pop();

        if (dist[u] > maxDist) {
            maxDist = dist[u];
            farthestNode = u;
        }

        for (INT v : adj[u]) {
            if (dist[v] == -1) {
                dist[v] = dist[u] + 1;
                q.push(v);
            }
        }
    }

    return {farthestNode, maxDist};
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    INT n;
    cin >> n;
    
    if (n == 1) {
        cout << 0 << "\n";
        return 0;
    }

    vector<vector<INT>> adj(n);
    for (INT i = 0; i < n - 1; i++) {
        INT u, v;
        cin >> u >> v;
        adj[u - 1].push_back(v - 1);
        adj[v - 1].push_back(u - 1);
    }

    pair<INT, INT> p1 = bfs(0, n, adj);
    
    pair<INT, INT> p2 = bfs(p1.first, n, adj);

    cout << p2.second << "\n";

    return 0;
}
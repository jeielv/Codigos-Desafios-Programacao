#include <bits/stdc++.h>
using namespace std;

#define INF 1e18

enum {
    UNVISITED = -1,
    VISITED = -2,
    EXPLORED = -3
};

typedef long long int INT;
typedef pair<INT, INT> ii;
typedef vector<ii> vii;
typedef vector<INT> vi;
typedef tuple<INT, INT, INT> iii;

struct Graph{
        stack<INT> ts;
        stack<INT> S;
        vector<vii> AL_T;
        vi visited;
        stack<INT> St;
        INT numSCC;
        vector<vii> AL;     // lista de adjacencias
        vector<vi> AM;      // matriz de adjacencias
        vi dfs_num;         // para indicar se vertice ja foi visitado e a ordem em q foi na arvore geradora
        vi dist;
        vi parent;
        vi dfs_low, articulation_vertex;
        vi taken;
        priority_queue<ii> pq;
        INT dfsNumberCounter, dfsRoot, rootChildren;
        INT V;

        Graph(INT N) : V(N), AL(N) {};

        void addEdge(INT u, INT v, INT w, bool directed){
            AL[u].push_back(pair(v, w));
            if (!directed)
                AL[v].push_back(pair(u, w));
        }

        void Dijkstra(INT s){       // arestas >= 0, o mais eficiente nesse caso
            dist.assign(V, INF); dist[s] = 0;
            parent.assign(V, -1);
            set<ii> pq;

            for (INT u = 0; u < V; u++)
                pq.emplace(dist[u], u);

            while(!pq.empty()){
                auto [d, u] = *pq.begin();
                pq.erase(pq.begin());

                for (auto &[v, w] : AL[u]){
                    if (dist[u] + w >= dist[v]) continue;
                    pq.erase(pq.find({dist[v], v}));
                    dist[v] = dist[u] + w;
                    parent[v] = u;
                    pq.emplace(dist[v], v);
                }
            }
        }

};

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    INT n, m;
    cin >> n >> m;

    Graph g(n);

    map<ii, INT> map;

    INT a, b, w;
    for (INT i = 0; i < m; i++){
        cin >> a >> b >> w;
        a--; b--;
        if (map.count(pair(a, b)))
            map[pair(a, b)] = min(map[pair(a, b)], w);
        else if (map.count(pair(b, a)))
            map[pair(b, a)] = min(map[pair(b, a)], w);
        else
            map[pair(a, b)] = w;
    }

    for (auto it = map.begin(); it != map.end(); it++){
        g.addEdge((it->first).first, (it->first).second, it->second, false);
    }

    g.Dijkstra(0);

    if (g.dist[n - 1] == INF) cout << -1;
    else{
        stack<INT> s;
        INT v = n - 1;
        while(v != -1){
            s.push(v);
            v = g.parent[v];
        }

        while(!s.empty()){
            cout << s.top() + 1 << " ";
            s.pop();
        }
    }

    return 0;
}
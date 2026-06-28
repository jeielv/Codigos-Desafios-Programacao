#include <bits/stdc++.h>
using namespace std;

#define INF 1e9

enum {
    UNVISITED = -1,
    VISITED = -2,
    EXPLORED = -3
};

typedef pair<int, int> ii;
typedef vector<ii> vii;
typedef vector<int> vi;
typedef tuple<int, int, int> iii;

int H, W;

struct Graph{
    private:
        stack<int> ts;
        stack<int> S;
        vector<vii> AL_T;
        vi visited;
        stack<int> St;
        int numSCC;
        vector<vii> AL;     // lista de adjacencias
        vector<vi> AM;      // matriz de adjacencias
        vi dfs_num;         // para indicar se vertice ja foi visitado e a ordem em q foi na arvore geradora
        vi dist;
        vi parent;
        vi dfs_low, articulation_vertex;
        vi taken;
        priority_queue<ii> pq;
        int dfsNumberCounter, dfsRoot, rootChildren;
        int V;

    public:
        Graph(int N) : V(N), AL(N), dfs_num(N, UNVISITED) {};

        void addEdge(int u, int v, int w, bool directed){
            AL[u].push_back(pair(v, w));
            if (!directed)
                AL[v].push_back(pair(u, w));
        }

        void bfs(int s){
            dist.assign(V, INF);
            parent.assign(V, -1);
            dist[s] = 0;
            queue<int> q; q.push(s);

            int u;
            while (!q.empty()){
                u = q.front(); q.pop();

                if (u == H * W - 1){
                    cout << "Yes\n";
                    /*int v = u;
                    stack<int> s;
                    while (v != -1){
                        s.push(v);
                        v = parent[v];
                    }

                    cout << "(" << (s.top() / W) + 1 << ", " << (s.top() % W) + 1 << ")";
                    s.pop();

                    while(!s.empty()){
                        cout << " -> ";
                        cout << "(" << (s.top() / W) + 1 << ", " << (s.top() % W) + 1 << ")";
                        s.pop();
                    }*/

                    return;   
                }

                for (auto &[v, w] : AL[u]){
                    if (dist[v] != INF) continue;

                    dist[v] = dist[u] + 1;
                    parent[v] = u;

                    q.push(v);
                }
            }

            cout << "No\n";

        }

};

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> H >> W;

    vector<string> grid(H);

    for (int i = 0; i < H; i++){
        cin >> grid[i];
    }

    if (grid[0][0] != 's'){
        cout << "No\n";
        return 0;
    }

    Graph g(H * W);

    int di[] = {-1, 1, 0, 0};
    int dj[] = {0, 0, -1, 1};

    string s = "snuke";

    int nextLet;
    int ni, nj;
    for (int i = 0; i < H; i++){
        for (int j = 0; j < W; j++){
            for (int currLet = 0; currLet < 5; currLet++){
                if (grid[i][j] == s[currLet]){
                    nextLet = (currLet + 1) % 5;
                    for (int k = 0; k < 4; k++){
                        ni = i + di[k];
                        nj = j + dj[k];
                        
                        if (ni >= 0 && ni < H && nj >= 0 && nj < W && grid[ni][nj] == s[nextLet]){
                            g.addEdge(i * W + j, ni * W + nj, 1, true);
                        }
                    }
                }
            }
        }
    }

    g.bfs(0);

    return 0;
}
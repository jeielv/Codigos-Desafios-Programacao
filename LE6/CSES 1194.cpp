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

int n, m;
int posA;
vi posM;
vi posF;

struct Graph{
        stack<int> ts;
        stack<int> S;
        vector<vii> AL_T;
        vi visited;
        stack<int> St;
        int numSCC;
        vector<vii> AL;     // lista de adjacencias
        vector<vi> AM;      // matriz de adjacencias
        vi dfs_num;         // para indicar se vertice ja foi visitado e a ordem em q foi na arvore geradora
        vi distA;
        vi distM;
        vi parent;
        vector<char> move;
        vi dfs_low, articulation_vertex;
        vi taken;
        priority_queue<ii> pq;
        int dfsNumberCounter, dfsRoot, rootChildren;
        int V;

        Graph(int N) : V(N), AL(N), dfs_num(N, UNVISITED) {};

        void addEdge(int u, int v, int w, bool directed){
            AL[u].push_back(pair(v, w));
            if (!directed)
                AL[v].push_back(pair(u, w));
        }

        void bfsA(int s){
            distA.assign(V, INF);
            parent.assign(n * m, -1);
            move.assign(n * m, 'X');
            distA[s] = 0;
            queue<int> q; q.push(s);

            int u;
            int r_u, r_v, c_u, c_v;
            while (!q.empty()){
                u = q.front(); q.pop();

                if (u % m == m - 1 || u % m == 0 || 
                    u < m || (u >= n * m - m && u <= n * m - 1)) 
                        posF.push_back(u);

                for (auto &[v, w] : AL[u]){
                    if (distA[v] != INF) continue;
                    distA[v] = distA[u] + 1;
                    parent[v] = u;

                    r_u = u / m; r_v = v / m;
                    c_u = u % m; c_v = v % m;
                    
                    if (r_v < r_u) move[v] = 'U';
                    else if (r_v > r_u) move[v] = 'D';
                    else if (c_v < c_u) move[v] = 'L';
                    else if (c_v > c_u) move[v] = 'R';

                    q.push(v);
                }
            }
        }

        void bfsM(){
            distM.assign(V, INF);

            queue<int> q;
            for (int i = 0; i < posM.size(); i++){
                distM[posM[i]] = 0;
                q.push(posM[i]);

                //cout << "(" << posM[i] / m << ", " << posM[i] % m << ")\n";
            }

            int u;
            while (!q.empty()){
                u = q.front(); q.pop();

                for (auto &[v, w] : AL[u]){
                    if (distM[v] != INF && distM[u] + 1 >= distM[v]) continue;
                    distM[v] = distM[u] + 1;

                    q.push(v);
                }
            }

            /*cout << "Distancia de monstro\n";
            for (int i = 0; i < V; i++){
                cout << "Ate: (" << i / m << ", " << i % m << ") = " << distM[i] << "\n";
            }*/
        }

        void solve(){
            int v = -1;
            while (!posF.empty()){
                if (distA[posF.back()] < distM[posF.back()]){
                    v = posF.back();
                    break;
                }

                posF.pop_back();
            }

            if (v == -1){
                cout << "NO";
                return;
            }

            string s;
            cout << "YES\n" << distA[v] << "\n";
            while (v != -1){
                s += move[v];
                v = parent[v];
            }
            s.pop_back();
            reverse(s.begin(), s.end());

            cout << s;
        }

};

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    
    cin >> n >> m;

    vector<string> matriz(n);

    char aux;
    for (int i = 0; i < n; i++){
       cin >> matriz[i];
    }

    vi dc = {0, 0, -1, 1};
    vi dr = {-1, 1, 0, 0};

    Graph g(n * m);

    int nr, nc;
    for (int i = 0; i < n; i++){
        for (int j = 0; j < m; j++){
            if (matriz[i][j] == 'A') posA = i * m + j;
            else if (matriz[i][j] == 'M') posM.push_back(i * m + j);
            else if (matriz[i][j] == '#') continue;

            for (int k = 0; k < 4; k++){
                nr = i + dr[k];
                nc = j + dc[k];
                if (nr >= 0 && nr < n && nc >= 0 && nc < m && matriz[nr][nc] != '#'){
                    g.addEdge(i * m + j, nr * m + nc, 1, true);
                }
            }
        }
    }

    g.bfsA(posA);
    g.bfsM();
    g.solve();

    return 0;
}
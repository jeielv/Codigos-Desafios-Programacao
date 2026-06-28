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

class DSU{
    private:
        vector<int> p, rank, setSize;
        int numSets;
    public:
        DSU(int N){
            p.assign(N, 0);
            for (int i = 0; i < N; i++) p[i] = i;

            rank.assign(N, 0);
            setSize.assign(N, 1);
            numSets = N;
        }

        int findSet(int i) {
            if (p[i] == i) return i;
            else{
                p[i] = findSet(p[i]);
                return p[i];
            }
        }
        bool isSameSet(int i, int j){ return findSet(i) == findSet(j); }
        int numDisjointSets() { return numSets; }
        int sizeOfSet(int i) { return setSize[findSet(i)]; }

        void unionSet(int i, int j){
            if (isSameSet(i, j)) return;
            int x = findSet(i);
            int y = findSet(j);
            if (rank[x] < rank[y]){
                p[x] = y;
                setSize[y] += setSize[x];
            }
            else if (rank[x] > rank[y]){
                p[y] = x;
                setSize[x] += setSize[y];
            }
            else{
                p[x] = y;
                setSize[y] += setSize[x];
                rank[y]++; 
            }
            numSets--;
        }

};

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
        vi dist;
        vi dfs_parent;
        vi dfs_low, articulation_vertex;
        vi taken;
        priority_queue<ii> pq;
        int dfsNumberCounter, dfsRoot, rootChildren;
        int V;

        void resetDFSNum(){
            for (int i = 0; i < V; i++)
                dfs_num[i] = UNVISITED;
        }

        Graph(int N) : V(N), dfs_num(N, UNVISITED) {
            AM.assign(N, vi(N));
        };

        Graph() {};
        void assign(int N){                      // fiz esse metodo pra usar com o construtor padrao
            V = N;
            AL.assign(N, {});
            dfs_num.assign(N, UNVISITED);
        }

        void FloydWarshall(){       // arestas >= 0 e < 0, detecta ciclos negativos
            int counter = 0;
            set<int> rem;
            for (int k = 0; k < V; k++)
                for (int i = 0; i < V; i++)
                    for (int j = 0; j < V; j++){
                        if (AM[i][k] + AM[k][j] < AM[i][j]){
                            cout << -1;
                            return;
                        }
                        if (AM[i][k] + AM[k][j] == AM[i][j] && i != k && k != j && !rem.count(i * V + j) && !rem.count(j * V + i)){
                            counter++;
                            rem.insert(i * V + j);
                        }
                    }

            cout << counter;
        }


};

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int N;
    cin >> N;

    Graph g(N);

    for (int i = 0; i < N; i++){
        for (int j = 0; j < N; j++){
            cin >> g.AM[i][j];
        }
    }

    g.FloydWarshall();

    return 0;
}
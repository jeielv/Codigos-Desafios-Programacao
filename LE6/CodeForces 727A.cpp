#include <bits/stdc++.h>
using namespace std;

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

INT a, b;

struct Graph{
    private:
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
        stack<INT> parent;
        vi dfs_low, articulation_vertex;
        vi taken;
        priority_queue<ii> pq;
        INT dfsNumberCounter, dfsRoot, rootChildren;
        INT V;
        bool possible;

        void dfs_help(INT u){
            if (u == a){
                cout << "YES\n";
                parent.push(u);
                solve();
                possible = true;
                return;
            }
            if (!possible && (u - 1) % 10 == 0 && ((u - 1) / 10) >= a) {
                parent.push(u);
                dfs_help((u - 1) / 10);
                if (!parent.empty()) parent.pop();
            }
            if (!possible && u % 2 == 0 && (u / 2) >= a){
                parent.push(u);
                dfs_help(u / 2);
                if (!parent.empty()) parent.pop();
            }

        }

        void resetDFSNum(){
            for (INT i = 0; i < V; i++)
                dfs_num[i] = UNVISITED;
        }

        void solve(){
            cout << parent.size() << "\n";
            while (!parent.empty()){
                cout << parent.top() << " ";
                parent.pop();
            }
            cout << "\n";
        }

    public:
        Graph(INT N) : V(N){};

        void dfs(INT u){
            possible = false;
            dfs_help(u);

            if (!possible) cout << "NO\n";
        }

};

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> a >> b;

    Graph g(b);

    g.dfs(b);

    return 0;
}
#include <bits/stdc++.h>
using namespace std;

#define INF 1e9

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

INT q;

class DSU{
    private:
        vector<INT> p, rank, setSize;
        INT numSets;
    public:
        DSU(INT N){
            p.assign(N, 0);
            for (INT i = 0; i < N; i++) p[i] = i;

            rank.assign(N, 0);
            setSize.assign(N, 1);
            numSets = N;
        }

        INT findSet(INT i) {
            if (p[i] == i) return i;
            else{
                p[i] = findSet(p[i]);
                return p[i];
            }
        }
        bool isSameSet(INT i, INT j){ return findSet(i) == findSet(j); }
        INT numDisjoINTSets() { return numSets; }
        INT sizeOfSet(INT i) { return setSize[findSet(i)]; }

        void unionSet(INT i, INT j){
            if (isSameSet(i, j)) return;
            INT x = findSet(i);
            INT y = findSet(j);
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

int main(){

    INT n, m;
    cin >> n >> m;

    priority_queue<iii> weights;
    DSU cams(n);

    INT u, v, w;
    INT higherW = 0;
    for (INT i = 1; i <= n - 1; i++){
        cin >> u >> v >> w;
        weights.emplace(-w, u - 1, v - 1);
        if (w > higherW) higherW = w;
    }

    vi queries(higherW + 1, 0);

    INT aux1, aux2, aux3;
    for (INT i = 1; i <= higherW; i++){
        tie(w, u, v) = weights.top();
        w = -w;
        queries[i] = queries[i - 1];

        if (i == w){
            aux3 = w;
            while (w == aux3){
                aux1 = cams.sizeOfSet(u);
                aux2 = cams.sizeOfSet(v);
                aux1 = aux1 * (aux1 - 1) / 2;
                aux2 = aux2 * (aux2 - 1) / 2;
                queries[i] -= aux1 + aux2;

                cams.unionSet(u, v);

                aux1 = cams.sizeOfSet(u);
                aux1 = aux1 * (aux1 - 1) / 2;
                queries[i] += aux1;

                weights.pop();
                if (!weights.empty()) tie(w, u, v) = weights.top();
                else break;

                w = -w;
            }
        }
    }
    
    for (INT i = 0; i < m; i++){
        cin >> q;
        q = (q > higherW ? higherW : q);
        cout << queries[q] << " ";
    }

    return 0;
}
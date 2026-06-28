#include <bits/stdc++.h>
using namespace std;

typedef long long int INT;

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
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    INT N, M;
    cin >> N >> M;

    vector<pair<INT, INT>> brdgs(M);

    set<INT> raizesInicial;
    DSU inicial(N);

    INT aux1, aux2;
    for (INT i = 0; i < M; i++){
        cin >> aux1 >> aux2;
        brdgs[i] = pair(aux1 - 1, aux2 - 1);
        inicial.unionSet(aux1 - 1, aux2 - 1);
    }

    for (INT i = 0; i < N; i++){
        if (!raizesInicial.count(inicial.findSet(i))){
            raizesInicial.insert(inicial.findSet(i));
        }
    }

    auto it = raizesInicial.begin();

    INT qtdConex = 0;

    for (; it != raizesInicial.end(); it++){
        aux1 = inicial.sizeOfSet(inicial.findSet(*it));
        qtdConex += aux1 * (aux1 - 1) / 2;
    }

    //agr, qtdConex guarda a quantidade de conexoes na cidade antes das ponte começar quebrar
    
    DSU quebrando(N);
    set<INT> raizesQuebrando;
    vector<INT> vec(M);

    INT conexs = 0;
    for (INT i = M - 1; i >= 0; i--){

        vec[i] = qtdConex - conexs;

        if(raizesQuebrando.count(quebrando.findSet(brdgs[i].first))){
            aux1 = quebrando.sizeOfSet(brdgs[i].first);
            conexs -= aux1 * (aux1 - 1) / 2;

            raizesQuebrando.erase(quebrando.findSet(brdgs[i].first));
        };
        
        if(raizesQuebrando.count(quebrando.findSet(brdgs[i].second))){
            aux1 = quebrando.sizeOfSet(brdgs[i].second);
            conexs -= aux1 * (aux1 - 1) / 2;

            raizesQuebrando.erase(quebrando.findSet(brdgs[i].second));
        }

        quebrando.unionSet(brdgs[i].first, brdgs[i].second);
        aux1 = quebrando.sizeOfSet(brdgs[i].first);

        conexs += aux1 * (aux1 - 1) / 2;
        
        raizesQuebrando.insert(quebrando.findSet(brdgs[i].first));
    }

    for (INT i = 0; i < M; i++){
        cout << vec[i] << "\n";
    }

    return 0;
}
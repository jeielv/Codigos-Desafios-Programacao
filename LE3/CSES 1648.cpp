#include <bits/stdc++.h>
using namespace std;

#define LSOne(S) ((S) & -(S))

typedef long long int INT;

class fenTree{
    private:
        vector<INT> ft;

        void build(vector<INT> &f){
            ft.assign(f.size(), 0);

            for (INT i = 1; i < f.size(); i++){
                ft[i] += f[i];        // assumindo q f[0] nao conta

                if (i + LSOne(i) < f.size()){
                    ft[i + LSOne(i)] += ft[i];
                }
            }
        }

    public:
        fenTree() { }
        
        fenTree(INT m) : ft(m + 1, 0) { }

        fenTree(vector<INT> &f) { 
            build(f);
        }

        INT rsq(INT j){
            INT sum = 0;
            for (; j; j -= LSOne(j)) sum += ft[j];

            return sum;
        }

        INT rsq(INT i, INT j) { return (rsq(j) - rsq(i - 1)); }

        void update(INT i, INT val){
            for(; i < ft.size(); i += LSOne(i)) ft[i] += val;
        }

        INT select(INT k){                      // pega o menor indice cuja soma acumulada de 1 ate esse indice eh maior ou igual a k
            INT lo = 1, hi = ft.size() - 1;
            INT mid;
            for (INT i = 0; i < 30; i++){       // aq, considera-se q o tamanho de f (e de ft) eh menor q aprox. 2^30
                mid = (lo + hi) / 2;
                (rsq(mid) < k ? lo = mid : hi = mid);
            }

            return hi;
        }

};

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    INT n, q;
    cin >> n >> q;

    vector<INT> vec(n + 1);

    for (INT i = 1; i <= n; i++){
        cin >> vec[i];
    }

    fenTree ft(vec);

    char op;
    INT aux1, aux2;
    INT aux3;

    for (INT i = 0; i < q; i++){
        cin >> op >> aux1 >> aux2;
        if (op == '1'){
            ft.update(aux1, aux2 - ft.rsq(aux1, aux1));
        }
        else{
            cout << ft.rsq(aux1, aux2) << "\n";
        }
    }

    return 0;
}
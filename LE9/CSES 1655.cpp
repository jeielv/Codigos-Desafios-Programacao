#include <bits/stdc++.h>
using namespace std;

vector<int> X;

struct vertex {
    vector<vertex*> child;
    vertex() { child.assign(2, NULL); }
};

class Trie {
    private :
        vertex* root;
    public:
        Trie() { root = new vertex(); }

        void insert(int val){
            vertex* cur = root;
            int tam = 30;

            while (tam >= 0){
                int num = (val >> tam--) & 1;
                if (cur->child[num] == NULL)
                    cur->child[num] = new vertex();
                cur = cur->child[num];
            }
        }

        void highest(){
            int result = 0;
            
            for (int val : X) {
                vertex* cur = root;
                int current_xor = 0;
                int tam = 30;
                
                while (tam >= 0) {
                    int bit = (val >> tam) & 1;
                    int toggled = 1 - bit;
                    
                    if (cur->child[toggled] != NULL) {
                        current_xor |= (1 << tam);
                        cur = cur->child[toggled];
                    } else {
                        cur = cur->child[bit];
                    }
                    tam--;
                }
                result = max(result, current_xor);
            }
            
            cout << result << "\n";
        }
};

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    X.assign(n, 0);

    Trie t;

    int val;
    cin >> X[0]; 
    t.insert(0);
    t.insert(X[0]);
    for (int i = 1; i < n; i++){
        cin >> val;
        X[i] = X[i - 1] ^ val;
        t.insert(X[i]);
    }

    t.highest();

    return 0;
}
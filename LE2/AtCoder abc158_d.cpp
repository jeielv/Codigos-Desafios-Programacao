#include <bits/stdc++.h>
using namespace std;

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    list<char> S;
    string aux;
    cin >> aux;

    for (long int i = 0; i < aux.size(); i++){
        S.push_back(aux[i]);
    }

    long int Q;
    cin >> Q;

    bool invertido = false;

    int T;
    int F;
    char C;

    for(long int i = 0; i < Q; i++){
        cin >> T;
        if (T == 1) invertido = !invertido;
        else{
            cin >> F >> C;
            if (F == 1){
                if (invertido) S.push_back(C);
                else S.push_front(C);
            }
            else{
                if (invertido) S.push_front(C);
                else S.push_back(C);
            }
        }
    }

    if (invertido){
        while(!S.empty()){
            cout << S.back();
            S.pop_back();
        }
    }
    else{
        while(!S.empty()){
            cout << S.front();
            S.pop_front();
        }
    }

    return 0;
}
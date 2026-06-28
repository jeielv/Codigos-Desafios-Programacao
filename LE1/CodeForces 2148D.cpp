#include <bits/stdc++.h>
using namespace std;

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    long long int t;
    cin >> t;

    long long int n;
    long long int qtdImp = 0;
    long long int aux;
    long long int sum = 0;

    for (long long int count = 0; count < t; count++){
        qtdImp = 0;
        sum = 0;
        cin >> n;
        vector<long long int> impAux(n, 0);

        for (long long int i = 0; i < n; i++){
            cin >> aux;
            if (aux % 2 == 0) sum += aux;
            else impAux[qtdImp++] = aux;
        }

        sum = (qtdImp > 0 ? sum : 0);

        vector<long long int> imp(qtdImp);

        for (long long int i = 0; i < qtdImp; i++) imp[i] = impAux[i];

        sort(imp.begin(), imp.end());

        for (long long int i = qtdImp / 2; i < qtdImp; i++) sum += imp[i];

        cout << sum << "\n";

    }

    return 0;
}
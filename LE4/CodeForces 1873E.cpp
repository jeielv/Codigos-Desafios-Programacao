#include <bits/stdc++.h>
using namespace std;

typedef long long int INT;

INT sum(INT h, INT x, INT n, array<INT, 200000> &vec){
    INT sum = 0;
    INT aux;
    for (int i = 0; i < n; i++){
        aux = h - vec[i];
        sum += (aux >= 0 ? aux : 0);
        if (sum > x) return sum;
    }

    return sum;
}

int main(){

    INT t;
    cin >> t;
    
    INT n, x;

    array<INT, 200000> vec;

    INT lo, hi, h;
    INT max;
    INT aux;
    for (int teste = 0; teste < t; teste++){
        cin >> n >> x;

        max = 0;
        for (int i = 0; i < n; i++){
            cin >> vec[i];
            if (vec[i] > max) max = vec[i];
        }

        lo = x / n;
        hi = max + lo;
        for (int i = 0; i < 35; i++){ 
            h = (lo + hi) / 2;
            aux = hi - lo;
            (sum(h, x, n, vec) > x ? hi = h : lo = h);

            if (hi - lo == aux && sum(hi, x, n, vec) <= x) lo = hi;
        }

        cout << lo << "\n";
    }

    return 0;
}
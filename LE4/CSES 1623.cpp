#include <bits/stdc++.h>
using namespace std;

#define LSOne(S) ((S) & -(S))

typedef long long int INT;

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    INT n;
    cin >> n;

    vector<INT> vec(n);

    INT groupA = 0, groupB = 0, total = 0;

    for (INT i = 0; i < n; i++){
        cin >> vec[i];
        total += vec[i];
    }

    INT conjs = 1;
    INT aux;
    INT i;
    INT min = total;

    while (conjs < (1 << n)){
        groupA = total;
        groupB = 0;

        aux = conjs;
        while(aux){
            i = __countr_zero(aux);
            groupA -= vec[i];
            groupB += vec[i];
            aux ^= LSOne(aux);
        }
        if (abs(groupA - groupB) < min){
            min = abs(groupA - groupB);
        }
        conjs++;
    }

    cout << min;

    return 0;
}
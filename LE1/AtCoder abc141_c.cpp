#include <bits/stdc++.h>
using namespace std;

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, K, Q;
    cin >> N >> K >> Q;

    int A;
    vector<int> players(N, K);

    for (int i = 0; i < Q; i++){
        cin >> A;
        for (int j = 0; j < N; j++){
            if (j != (A - 1)) players[j] -= 1;
        }
    }

    for (int i = 0; i < N; i++){
        if (players[i] > 0) cout << "Yes\n";
        else cout << "No\n";
    }
    
    return 0;
}
#include <bits/stdc++.h>
using namespace std;

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, q;
    cin >> n >> q;

    queue<pair<string, int>> procs;

    string name;
    int time;

    for (int i = 0; i < n; i++){
        cin >> name >> time;
        procs.push(pair(name, time));
    }

    int sumTime = 0;
    pair<string, int> aux;
    string auxS;
    int auxI;

    while(!procs.empty()){
        if (procs.front().second <= q){
            sumTime += procs.front().second;
            cout << procs.front().first << " " << sumTime << "\n";
            procs.pop();
        }
        else{
            sumTime += q;
            procs.push(pair(procs.front().first, procs.front().second - q));
            procs.pop();
        }
    }


    return 0;
}
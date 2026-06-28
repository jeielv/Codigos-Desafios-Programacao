#include <bits/stdc++.h>
using namespace std;

const int MAX_N = 1000020;

string TXT, P;
int b[MAX_N], n, m;
queue<int> q;

void kmpPreprocess() {
    int i = 0, j = -1; b[0] = -1;
    while (i < m) {
        while ((j >= 0) && (P[i] != P[j])) j = b[j];
        i++; j++;
        b[i] = j;
    }
}

void kmpSearch(){
    int i = 0, j = 0;
    while (i < n){
        while ((j >= 0) && (TXT[i] != P[j])) j = b[j];
        i++; j++;
        if (j == m){
            q.push(i - j + 1);
            j = b[j];
        }
    }
}

void search(){
    n = TXT.length();
    m = P.length();
    kmpPreprocess();
    kmpSearch();

    if (q.empty()){
        cout << "\nNot Found\n";
        return;
    }
    cout << q.size() << "\n";
    while (!q.empty()){
        cout << q.front() << " "; q.pop();
    }
    cout << "\n";
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;

    for (int tst = 0; tst < T; tst++){
        cin >> TXT; cin >> P;
        search();
    }

    return 0;
}
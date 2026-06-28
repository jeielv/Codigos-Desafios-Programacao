#include <bits/stdc++.h>
using namespace std;

vector<vector<int>> memo;
string s, t;
deque<char> p;

int max(int a, int b){
    return (a >= b? a : b);
}

int dp(int i, int j){
    if (i == -1 || j == -1) return 0;

    int &ans = memo[i][j];
    if (ans != -1) return ans;

    if (s[i] == t[j]) {
        return ans = 1 + dp(i - 1, j - 1);
    }
    else return ans = max(dp(i - 1, j), dp(i, j - 1));
}

void substr(int i, int j){
    if (i == -1 || j == -1) return;

    if (s[i] == t[j]){
        p.push_front(s[i]);
        substr(i - 1, j - 1);
    }
    else if (dp(i - 1, j) >= dp(i, j - 1))
        substr(i - 1, j);
    else
        substr(i, j - 1);

    return;
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> s;
    cin >> t;

    int maiorStr = (s.size() > t.size() ? s.size() : t.size());

    memo.assign(maiorStr, {});

    for (int i = 0; i < maiorStr; i++){
        memo[i].assign(maiorStr, -1);
    }

    int tam = dp(s.size() - 1, t.size() - 1);

    substr(s.size() - 1, t.size() - 1);

    for (int i = 0; i < tam; i++){
        cout << p[i];
    }

    return 0;
}
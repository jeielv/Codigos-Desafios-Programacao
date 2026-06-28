#include <bits/stdc++.h>
using namespace std;

const int INF = 1e9;

int n;
array<int, 200010> vec;
array<int, 200010> memo;

/*int dp(int i){
    if (i > n) return INF;
    if (i == n) return 0;

    int &ans = memo[i];
    if (ans != -1) return ans;

    return ans = min(1 + dp(i + 1), dp(i + vec[i] + 1));
}*/

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;

    for (int tst = 0; tst < t; tst++){
        cin >> n;

        for (int i = 0; i < n; i++){ 
            cin >> vec[i];
            memo[i] = -1;
        }

        memo[n - 1] = 1;
        for (int i = n - 2; i >= 0; i--){
            memo[i] = min(1 + memo[i + 1], (i + vec[i] + 1 < n ? memo[i + vec[i] + 1] : (i + vec[i] + 1 == n ? 0 : INF)));
        }
        
        cout << memo[0] << "\n";

    }


    return 0;
}
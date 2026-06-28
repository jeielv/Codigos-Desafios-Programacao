#include <bits/stdc++.h>
using namespace std;

typedef long long int INT;

double n, a, b;
double total;
double events;

vector<vector<double>> memo;

double dp(double left, double score){
    if (score > b) return 0;
    else if (left == 0 && score < a) return 0;
    else if (left == 0 && score >= a) return 1;

    double &ans = memo[left][score];
    if (ans != -1) return ans;

    return 
        ans = dp(left - 1, score + 1) + dp(left - 1, score + 2) + dp(left - 1, score + 3) + 
              dp(left - 1, score + 4) + dp(left - 1, score + 5) + dp(left - 1, score + 6);

}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> a >> b;

    memo.assign(n + 1, vector<double>(6 * n, -1));

    events = dp(n, 0);
    total = pow(6, n);

    cout << fixed << setprecision(6) << (double) events / total;

    return 0;
}
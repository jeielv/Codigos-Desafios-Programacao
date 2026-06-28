#include <bits/stdc++.h>
using namespace std;

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    long long int t;
    cin >> t;

    priority_queue<long long int> bonus;

    long long int n;
    long long int val;
    long long int sum;
    
    for (int i = 0; i < t; i++){
        cin >> n;
        sum = 0;
        for (int j = 0; j < n; j++){
            cin >> val;
            if (val != 0) bonus.push(val);
            else if (!bonus.empty()){
                sum += bonus.top();
                bonus.pop();
            }
        }
        cout << sum << "\n";

        while(!bonus.empty()) bonus.pop();
    }

    return 0;
}
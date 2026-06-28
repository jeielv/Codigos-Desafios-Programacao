#include <bits/stdc++.h>
using namespace std;

vector<int> sticks(200010);

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;
    
    int n;
    int maiorRepetido;
    bool achou;
    for (int tst = 0; tst < t; tst++){
        cin >> n;
        map<int, int> num;
        maiorRepetido = 0;
        achou = false;
        for (int i = 0; i < n; i++){
            cin >> sticks[i];
            num[sticks[i]]++;
            if (num[sticks[i]] == 2){
                if (sticks[i] > maiorRepetido){
                    maiorRepetido = sticks[i];
                }
            }
        }
        if (maiorRepetido == 0){
            cout << "-1\n";
            continue;
        }
        sort(sticks.begin(), sticks.begin() + n);
        int it = lower_bound(sticks.begin(), sticks.begin() + n, maiorRepetido) - sticks.begin();
        sticks[it] = sticks[it + 1] = 0;
        sort(sticks.begin(), sticks.begin() + n);

        for (int i = 1; i < n; i++){
            if (sticks[i] != 0 && sticks[i - 1] != 0 && sticks[i] - sticks[i - 1] < 2 * maiorRepetido){
                achou = true;
                cout << maiorRepetido << " " << maiorRepetido << " " << sticks[i] << " " << sticks[i - 1] << "\n";
                break;
            }
        }

        if (!achou){
            cout << "-1\n";
        }

    }
    
    return 0;
}
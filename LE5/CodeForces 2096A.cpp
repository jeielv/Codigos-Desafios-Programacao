#include <bits/stdc++.h>
using namespace std;

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;

    int n;
    array<int, 100> vec;
    string s;
    int min;
    int max;
    for (int tst = 0; tst < t; tst++){
        cin >> n;
        cin >> s;
        min = 1;
        max = n;

        for (int i = s.size() - 1; i >= 0; i--){
            if (s[i] == '<')
                vec[i + 1] = min++;
            else
                vec[i + 1] = max--;
        }
        vec[0] = min;

        for (int i = 0; i < n; i++)
            cout << vec[i] << (i != n - 1 ? " " : "\n");
    }

    return 0;
}
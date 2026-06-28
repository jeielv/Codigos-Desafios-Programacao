#include <bits/stdc++.h>
using namespace std;

#define EPS 1e-9

typedef long long int INT;

struct point{
    INT x, y;

    point() { x = y = 0.0; }
    point(INT _x, INT _y) : x(_x), y(_y) {}

};

INT area(const vector<point> &P){
    INT ans = 0;

    for (int i = 0; i < P.size() - 1; i++){
        ans += (P[i].x * P[i + 1].y - P[i + 1].x * P[i].y);
    }

    if (ans < 0) ans = -ans;
    return ans;
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    vector<point> P(n + 1);

    for (int i = 0; i < n; i++){
        cin >> P[i].x >> P[i].y;
    }
    P[n].x = P[0].x;
    P[n].y = P[0].y;

    cout << area(P) << "\n";
    
    return 0;
}
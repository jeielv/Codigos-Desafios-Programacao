#include <bits/stdc++.h>
using namespace std;

#define EPS 1e-9

struct point{
    double x, y;

    point() { x = y = 0.0; }
    point(double _x, double _y) : x(_x), y(_y) {}

    bool operator < (point other) const {
        if (fabs(x - other.x) > EPS)
            return x < other.x;
        return y < other.y;
    }

    bool operator == (const point &other) const {
        return (fabs(x - other.x) < EPS) && (fabs(y - other.y) < EPS);
    }

};

double hypot(double dx, double dy){
    return sqrt(dx * dx + dy * dy);
}

double dist(const point &p1, const point &p2){
    return hypot(p1.x - p2.x, p1.y - p2.y);
}

double cosAng(double a, double b, double c){
    return ((a * a + b * b - c * c) / (2 * a * b));
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    double x, y;

    cin >> x >> y;
    point A(x, y);

    cin >> x >> y;
    point B(x, y);

    cin >> x >> y;
    point C(x, y);

    double ab = dist(A, B);
    double ac = dist(A, C);
    double bc = dist(B, C);

    if (fabs(cosAng(ab, ac, bc)) < EPS){
        cout << "RIGHT\n";
        return 0;
    }
    else if (fabs(cosAng(ab, bc, ac)) < EPS){
        cout << "RIGHT\n";
        return 0;
    }
    else if (fabs(cosAng(bc, ac, ab)) < EPS){
        cout << "RIGHT\n";
        return 0;
    }

    int dx[] = {0, 0, -1, 1};
    int dy[] = {1, -1, 0, 0};

    vector<point> vec = {A, B, C};

    for (int i = 0; i < 3; i++){
        for (int k = 0; k < 4; k++){
            vec[i].x += dx[k];
            vec[i].y += dy[k];

            ab = dist(vec[0], vec[1]);
            ac = dist(vec[0], vec[2]);
            bc = dist(vec[1], vec[2]);

            if (fabs(cosAng(ab, ac, bc)) < EPS){
                cout << "ALMOST\n";
                return 0;
            }
            else if (fabs(cosAng(ab, bc, ac)) < EPS){
                cout << "ALMOST\n";
                return 0;
            }
            else if (fabs(cosAng(bc, ac, ab)) < EPS){
                cout << "ALMOST\n";
                return 0;
            }

            vec[i].x -= dx[k];
            vec[i].y -= dy[k];
        }
    }

    cout << "NEITHER\n";

    return 0;
}
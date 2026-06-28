#include <bits/stdc++.h>
using namespace std;

#define INT long long int


bool comp(tuple<INT, INT, INT> a, tuple<INT, INT, INT> b){
    if (get<0>(a) != get<0>(b)) return get<0>(a)< get<0>(b);
    else if (get<1>(a) != get<1>(b)) return get<1>(a) < get<1>(b);
    else return get<2>(a) < get<2>(b);
}

struct myGreatest{
    bool operator()(pair<INT, INT> a, pair<INT, INT> b){
        return a.first > b.first;
    }
};

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    INT n;
    cin >> n;

    map<tuple<INT, INT, INT>, INT> usedRooms;

    INT roomsCnt = 0;

    priority_queue<pair<INT, INT>, vector<pair<INT, INT>>, myGreatest> depDays;

    map<pair<INT, INT>, INT> room;

    vector<tuple<INT, INT, INT>> aux(n);
    vector<tuple<INT, INT, INT>> vec(n);
    INT arrDay;
    INT depDay;
    for (INT i = 0; i < n; i++){
        cin >> arrDay >> depDay;
        vec[i] = tuple(arrDay, depDay, i);
        aux[i] = tuple(arrDay, depDay, i);
    }

    sort(vec.begin(), vec.end(), comp);

    INT idx;
    for (INT i = 0; i < n; i++){
        arrDay = get<0>(vec[i]);
        depDay = get<1>(vec[i]);
        idx = get<2>(vec[i]);

        if (depDays.empty()){
            roomsCnt++;
            depDays.push(pair(depDay, idx));
            room[pair(depDay, idx)] = roomsCnt;
            usedRooms[vec[i]] = room[pair(depDay, idx)];
        }
        else if (arrDay > depDays.top().first){
            // o quarto do novo cliente vai ser o quarto do cara q tava no topo e ja foi embora
            room[pair(depDay, idx)] = room[depDays.top()];
            room.erase(depDays.top());

            // tira o cara q ja foi embora dos dias de saida e coloca o q acabou de chegar
            depDays.pop();
            depDays.push(pair(depDay, idx));

            usedRooms[vec[i]] = room[pair(depDay, idx)];
        }
        else{
            // ja q o cara chega qnd o q sairia antes ainda nn saiu, ent tem q botar um quarto novo
            roomsCnt++;
            depDays.push(pair(depDay, idx));
            room[pair(depDay, idx)] = roomsCnt;
            usedRooms[vec[i]] = roomsCnt;
        }
    }
    cout << roomsCnt << "\n";

    for (int i = 0; i < n; i++){
        cout << usedRooms[aux[i]] << " ";
    }
    cout << "\n";

    return 0;
}
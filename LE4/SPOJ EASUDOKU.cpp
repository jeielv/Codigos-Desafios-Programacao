#include <bits/stdc++.h>
using namespace std;

bool podeColocar(int i, int j, int num, array<int, 10> &chkLin, array<int, 10> &chkCol, array<int, 10> &chkBlk){
    int linBlk = i / 3;
    int colBlk = j / 3;

    
    if (chkLin[num] & (1 << i)) return false;
    if (chkCol[num] & (1 << j)) return false;
    if (chkBlk[num] & (1 << (linBlk * 3 + colBlk))) return false;

    return true;
}

bool backtrack(array<array<int, 9>, 9> &vec, int i, int num, array<int, 10> &chkLin, array<int, 10> &chkCol, array<int, 10> &chkBlk){
    if (i > 8){
        if (num == 9){
            for (int il = 0; il < 9; il++){
                for (int j = 0; j < 9; j++){
                    cout << vec[il][j] << " ";
                }
                cout << "\n";
            }
            return true;
        }

        return backtrack(vec, 0, num + 1, chkLin, chkCol, chkBlk);
    }

    int linBlk, colBlk;
    if (!(chkLin[num] & (1 << i)))
        for (int j = 0; j < 9; j++){
            if (vec[i][j] != 0) continue;
            
            if (podeColocar(i, j, num, chkLin, chkCol, chkBlk)){
                vec[i][j] = num;
                linBlk = i / 3;
                colBlk = j / 3;

                chkLin[num] |= 1 << i;
                chkCol[num] |= 1 << j;
                chkBlk[num] |= 1 << (linBlk * 3 + colBlk);

                if (backtrack(vec, i + 1, num, chkLin, chkCol, chkBlk)) return true;

                vec[i][j] = 0;
                chkLin[num] &= ~(1 << i);
                chkCol[num] &= ~(1 << j);
                chkBlk[num] &= ~(1 << (linBlk * 3 + colBlk));
            }
            
        }
    else {
        return backtrack(vec, i + 1, num, chkLin, chkCol, chkBlk);
    }

    return false;
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;

    array<array<int, 9>, 9> vec;
    array<int, 10> chkLin = {0};
    array<int, 10> chkCol = {0};
    array<int, 10> chkBlk = {0};

    int linBlk, colBlk;
    int aux;
    for (int tst = 0; tst < t; tst++){

        chkLin = {0};
        chkCol = {0};
        chkBlk = {0};

        for (int i = 0; i < 9; i++)
            for (int j = 0; j < 9; j++){
                cin >> aux;
                vec[i][j] = aux;

                linBlk = i / 3;
                colBlk = j / 3;

                chkLin[aux] |= 1 << i;
                chkCol[aux] |= 1 << j;
                chkBlk[aux] |= 1 << (linBlk * 3 + colBlk);
            }

        if (!backtrack(vec, 0, 1, chkLin, chkCol, chkBlk)) cout << "No solution\n";
    }

    return 0;
}
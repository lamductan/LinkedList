#include <stdio.h>

const int INF = 1e9;
const int oo = 1e9;
const int MAXHP = 100;

int xMove[8] = {  2, 1, -1, -2, -2, -1,  1,  2 };
int yMove[8] = {  1, 2,  2,  1, -1, -2, -2, -1 };

int M, N;
int **a, **L;

bool isSafe(int x, int y){
    return (x >= 0 && x < M && y >= 0 && y < N);
}

void init(int **a, int **L, int Size){
    int next_x, next_y, index, index_next;
    for(int i = 0; i < M; ++i){
        for(int j = 0; j < N; ++j){
            index = i*M + j;
            for(int k = 0; k < 8; ++k){
                next_x = i + xMove[k];
                next_y = j + yMove[k];
                index_next = next_x*M + next_y;
                if (isSafe(next_x, next_y)) L[index][index_next] = a[next_x][next_y];
            }
        }
    }
}

int Dijkstra(int **a, int **L, int Size, int x1, int y1, int x2, int y2){
    int start_pos = x1*M + y1, end_pos = x2*M + y2;
    int *BelongT = new int[Size];
    int *Length = new int[Size];
    int *LastV = new int[Size];

    for(int i = 0; i < Size; ++i){
        BelongT[i] = 1;
        Length[i] = INF;
        LastV[i] = -1;
    }
    BelongT[start_pos] = 0;
    Length[start_pos] = 0;

    for(int i = 0; i < Size; ++i)
        if (L[start_pos][i] < INF) {
            Length[i] = L[start_pos][i];
            LastV[i] = start_pos;
        }

    int min_length;
    int v;
    while (BelongT[end_pos]){
        min_length = oo;
        v = -1;
        for(int i = 0; i < Size; ++i)
            if (BelongT[i] && Length[i] < min_length){
                min_length = Length[i];
                v = i;
            }
        if (v == -1) break;
        BelongT[v] = 0;

        for(int i = 0; i < Size; ++i)
        if (BelongT[i] && L[v][i] < INF){
            int dist = Length[v] + L[v][i];
            if (Length[i] > dist){
                Length[i] = dist;
                LastV[i] = v;
            }
        }
    }
    int res = Length[end_pos];

//    freopen("out.txt", "w", stdout);
//    while (v != start_pos){
//        printf("%d\n", LastV[v]);
//        v = LastV[v];
//    }

    delete[]BelongT;
    delete[]Length;
    delete[]LastV;

    return res;
}

void release_Memory(int **&a, int Size_y){
    for(int i = 0; i < Size_y; ++i)
        delete []a[i];
    delete []a;
}

int main(){
    freopen("in.txt", "r", stdin);
    scanf("%d %d", &M, &N);
    int **a = new int*[M];
    for(int i = 0; i < M; ++i){
        a[i] = new int[N];
        for(int j = 0; j < N; ++j)
            scanf("%d", &a[i][j]);
    }
    fclose(stdin);
    int Size = M*N;
    int **L = new int*[Size];
    for(int i = 0; i < Size; ++i){
        L[i] = new int[Size];
        for(int j = 0; j < Size; ++j)
            L[i][j] = INF;
    }

    init(a, L, Size);

    int ans = oo, res;
    for(int i = 0; i < M; ++i)
    for(int j = 0; j < M; ++j){
        res = a[i][j] + Dijkstra(a, L, Size, i, 0, j, N - 1);
        if (res < ans) ans = res;
    }

    freopen("out.txt", "wt", stdout);
    printf("%d\n", MAXHP - ans);
    fclose(stdout);

    release_Memory(a, N);
    release_Memory(L, Size);
}


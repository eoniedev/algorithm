#include<iostream>
#include<vector>
#include<algorithm>
#include<queue>
#include<tuple>
using namespace std;
int N, M, Room=0, Min=2500;
int Lab[51][51];
vector<pair<int,int>> UVirus, Selected; 

bool inRange(int x, int y){
    return x>=0 && y>=0 && x<N && y<N;
}
int bfs() {
    int visited[51][51] = {{0,},};
    int time = -1, cnt=0;
    queue<tuple<int,int,int>> q;
    for(int i=0; i<M; i++){
        visited[Selected[i].first][Selected[i].second] = 1;
        q.emplace(Selected[i].first, Selected[i].second, 0);
    }

    int deltas[4][2] = {{1,0}, {-1,0}, {0,1}, {0,-1}};
    while (!q.empty()){
        int x, y, t;
        tie(x, y, t) = q.front();
        q.pop();
        if(Lab[x][y] == 0){
            cnt++;
        }
        if(t > Min){
            break;
        }
        if(cnt == Room) {
            time = t;
            break;
        }
        for(int i=0; i<4; i++){
            int a = x + deltas[i][0];
            int b = y + deltas[i][1];
            if(inRange(a, b) && !visited[a][b] && Lab[a][b] != 1){
                visited[a][b] = 1;
                q.emplace(a, b, t+1);
            }
        }
    }
    return time;
}

void comb(int cnt, int next) {
    if(cnt == M){
        int time = bfs();
        if(time != -1){
            Min = min(Min, time);
        }
        return;
    }
    for(int i=next; i<UVirus.size(); i++){
        Selected[cnt] = UVirus[i];
        comb(cnt+1, i+1);
    }
}

int main() {
    cin >> N >> M;
    Selected.resize(M);
    for(int i=0; i<N; i++){
        for(int j=0; j<N; j++){
            cin >> Lab[i][j];
            if(Lab[i][j] == 2){
                UVirus.emplace_back(i, j);
            }
            if(Lab[i][j] == 0){
                Room++;
            }
        }
    }
    comb(0,0);
    if(Min == 2500) cout << -1;
    else            cout << Min;
}
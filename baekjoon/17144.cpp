#include<iostream>
#include<vector>
using namespace std;
int R, C, T;
int A[51][51];
vector<pair<int,int>> AirCleaner;

bool inRange(int x, int y) {
    return x >= 0 && y >= 0 && x < R && y < C;
}

void spread() {
    int deltas[4][2] = {{1,0}, {0,1}, {-1,0}, {0,-1}};
    int temp[51][51] = {{0,},};

    for(int i=0; i<R; i++){
        for(int j=0; j<C; j++){
            if(A[i][j] > 0) {
                int cnt = 0;
                for(int k=0; k<4; k++){             // 확산 개수
                    int x = i + deltas[k][0];
                    int y = j + deltas[k][1];
                
                    if(inRange(x, y) && A[x][y] != -1) {
                        cnt++;
                    }
                }

                int spreadA = A[i][j] / 5;
                temp[i][j] -= spreadA * cnt;

                for(int k=0; k<4; k++){             // 확산 진행
                    int x = i + deltas[k][0];
                    int y = j + deltas[k][1];
                
                    if(inRange(x, y) && A[x][y] != -1) {
                        temp[x][y] += spreadA;
                    }
                }
            }
        }
    }

    for(int i=0; i<R; i++){                 //확산 업데이트
        for(int j=0; j<C; j++){
            A[i][j] += temp[i][j];
        }
    }
}
bool inCleaner(int x, int y, int i) {
    if(i == 0)
        return x >= 0 && y >= 0 && x <= AirCleaner[0].first  && y < C;
    else
        return x >= AirCleaner[1].first && y >= 0 && x < R  && y < C;
    
}
void clean() {
    int deltas[2][4][2] = {
        {{-1, 0}, {0, 1}, {1, 0}, {0, -1}},
        {{1, 0}, {0, 1}, {-1, 0}, {0, -1}}
    };

    for(int i=0; i<2; i++) {
        int x = AirCleaner[i].first;
        int y = AirCleaner[i].second;
        

        int nx = x + deltas[i][0][0];
        int ny = y + deltas[i][0][1];
        int direct = 0;
        
        while(!(make_pair(nx, ny) ==  AirCleaner[i])) {
            if(inCleaner(nx, ny, i)) {
                if(make_pair(x, y) != AirCleaner[i]) {
                    A[x][y] = A[nx][ny];
                }
                x = nx;
                y = ny;   
            }
            else {
                direct = (direct+1) % 4;
            }
            nx = x + deltas[i][direct][0];
            ny = y + deltas[i][direct][1];
        }
        A[x][y] = 0;
    }
}

int main() {
    cin >> R >> C >> T;
    for(int i=0; i<R; i++){
        for(int j=0; j<C; j++){
            cin >> A[i][j];
            if(A[i][j] == -1) {
                AirCleaner.emplace_back(i,j);
            }
        }
    }

    for(int i=0; i<T; i++){
        spread();
        clean();
    }

    int sum = 0;
    for(int i=0; i<R; i++){
        for(int j=0; j<C; j++){
            if(A[i][j] != -1)
                sum += A[i][j];
        }
    }

    cout << sum;
}
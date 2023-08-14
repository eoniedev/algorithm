#include<iostream>
#include<algorithm>
#include<cstring>
using namespace std;
int N, K;
int Fish[101][101];
int Length[101], Height[101];
void update(){

}

void organize1() {
    //물고기 넣기
    int m = *min_element(Fish[0], Fish[0]+N);
    for(int i=0; i<N; i++){
        if(Fish[0][i] == m) {
            Fish[0][i]++;
        }
    }
    //왼쪽한개 올리기
    Fish[1][N-2] = Fish[0][N-1];
    Fish[0][N-1] = -1;
    Height[N-1] = 0;
    Height[N-2] = 2;
    Length[0]--;
    Length[1]++;
    //
    int rest = Length[0] - 1;
    int cnt = 1;
    int h = Height[N-2];
    while(rest >= cnt) {
        for(int i=0; i<h; i++){
            for(int j=0; j<cnt; j++){
                int x = i;
                int y = rest+j;
                Fish[i+1][rest-j-1] = Fish[x][y];
                Fish[x][y] = -1;
                Height[rest-j-1]++;
            }
        }
        Length[0] -= cnt;
        rest = Length[0];
        cnt = 0;
        for(int i=rest-1; i>=0; i++){
            if(Height[i] < 2) {
                break;
            }
            cnt++;
        } 
    }
    for(int i=N-1; i>=0; i--){

    }
}
void organize2() {
    
}
int calDiff() {

}


int main() {
    cin >> N >> K;
    memset(Fish, -1, sizeof(Fish));
    memset(Length, 0, sizeof(Length));
    Length[0] = N;
    memset(Height, 0, sizeof(Height));
    fill(Height, Height+N, 1);
    
    for(int i=N-1; i>=0; i--){
        cin >> Fish[0][i];
    }
    int cnt=0;
    // while(calDiff() > K) {
    //     organize1();
    //     organize2();
    //     cnt++;
    // }
    cout << cnt;
    
}
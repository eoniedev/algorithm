#include<iostream>

using namespace std;
int N, R, C;
int House[18][18];
int Blank[18][18];
int dp[18][18][3]; //0 : 가로, 1: 세로, 2: 대각


int main() {
    cin >> N;
    for(int i=1; i<=N; i++){
        for(int j=1; j<=N; j++){
            cin >> House[i][j];
        }
    }
    dp[1][1][0] = dp[1][1][1] = dp[1][1][2] = 0;
    dp[1][2][0] = 1;
    dp[1][2][1] = dp[1][2][2] = 0;

    for(int i=1; i<=N; i++) {
        for(int j=1; j<=N; j++){
            if(!(i==1 && j==1) && !(i==1 && j==2)) {
                //for(int k=0; k<3; k++) {
                // 왼쪽의 가로   대각선의 가로      위의 세로       대각선의 세로     왼쪽의 대각선     위의 대각선  대각선의 대각선
                //dp[i][j-1][0] + dp[i-1][j-1][0] + dp[i-1][j][1] + dp[i-1][j-1][1] + dp[i][j-1][2] + dp[i-1][j][2] + dp[i-1][j-1][2];
                    if(!House[i][j]){
                        dp[i][j][0] = dp[i][j][1] = dp[i][j][2] = 0;
                        if(i-1 > 0) {
                            dp[i][j][1] += (dp[i-1][j][1] + dp[i-1][j][2]);
                        }
                        
                        if(i-1 > 0 && j-1 > 0 && !House[i-1][j] && !House[i][j-1]) {
                            dp[i][j][2] += (dp[i-1][j-1][0] + dp[i-1][j-1][1] + dp[i-1][j-1][2]);
                        }// 

                        if(j-1 > 0) {
                            dp[i][j][0] += (dp[i][j-1][2]+dp[i][j-1][0]);
                        }
                    }
                //}
            }
            //cout << '['<<dp[i][j][0] << ' ' <<dp[i][j][1] <<' '<<dp[i][j][2] << ']';           
        }
        //cout << endl;
    }

    cout << dp[N][N][0] + dp[N][N][1] + dp[N][N][2];
}

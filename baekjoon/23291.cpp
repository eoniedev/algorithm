#include<iostream>
#include<algorithm>
#include<cstring>
#include<string>
using namespace std;
int N, K;
int Fish[101][101];
int Length[101], Height[101];

bool inRange(int x, int y) {
    return x >= 0 && y >= 0 && x < 100 && y < 100;
}
void update() {
    int deltas[2][2] = { {1, 0}, {0, 1} };
    int temp[101][101] = { {0,}, };
    for (int j = 0; j < Length[0]; j++) {
        for (int i = 0; i < Height[j]; i++) {
            for (int k = 0; k < 2; k++) {
                int x = i + deltas[k][0];
                int y = j + deltas[k][1];

                if (inRange(x, y) && Fish[x][y] != -1) {
                    int diff = abs(Fish[i][j] - Fish[x][y]) / 5;
                    if (diff > 0) {
                        if (Fish[i][j] > Fish[x][y]) {
                            temp[i][j] -= diff;
                            temp[x][y] += diff;
                        }
                        else {
                            temp[i][j] += diff;
                            temp[x][y] -= diff;
                        }
                    }
                }
            }
        }
    }

    for (int j = 0; j < Length[0]; j++) {
        for (int i = 0; i < Height[j]; i++) {
            Fish[i][j] += temp[i][j];
        }
    }
}
void reset() {
    memset(Fish, -1, sizeof(Fish));
    memset(Length, 0, sizeof(Length));
    Length[0] = N;
    memset(Height, 0, sizeof(Height));
    fill(Height, Height + N, 1);
}

void inRow() {
    int temp[101];
    int idx = 0;
    for (int j = 0; j < Length[0]; j++) {
        for (int i = Height[j] - 1; i >= 0; i--) {
            temp[idx++] = Fish[i][j];
        }
    }
    reset();
    for (int i = 0; i < N; i++) {
        Fish[0][i] = temp[i];
    }
}
void organize1() {
    //물고기 넣기
    int m = *min_element(Fish[0], Fish[0] + N);
    for (int i = 0; i < N; i++) {
        if (Fish[0][i] == m) {
            Fish[0][i]++;
        }
    }
    //왼쪽한개 올리기
    Fish[1][N - 2] = Fish[0][N - 1];
    Fish[0][N - 1] = -1;
    Height[N - 1] = 0;
    Height[N - 2] = 2;
    Length[0]--;
    Length[1]++;
    //
    int cnt = 1;
    int h = Height[N - 2];
    while (Length[0] - cnt >= h) {
        int point = Length[0] - cnt;
        for (int j = 0; j < cnt; j++) {
            for (int i = 0; i < h; i++) {
                int x = i;
                int y = point + j;
                Fish[j + 1][point - i - 1] = Fish[x][y];
                Fish[x][y] = -1;
                Height[y]--;
                Height[point - i - 1]++;
            }
        }
        Length[0] -= cnt;
        cnt = 0;
        for (int i = Length[0] - 1; i >= 0; i--) {
            if (Height[i] < 2) {
                break;
            }
            cnt++;
        }
        h = Height[Length[0] - 1];
    }
    update();
    inRow();
}
void organize2() {
    int l = Length[0];
    for (int j = l / 2; j < l; j++) {
        Fish[1][l-j-1] = Fish[0][j];
        Fish[0][j] = -1;
        Height[j]--;
        Height[l-j-1]++;

        Length[0]--;
        Length[1]++;
    }
    l = Length[0];

    for (int i = 1; i >= 0; i--) {
        for (int j = l / 2; j < l; j++) {
            int x = Height[l - j - 1];
            Fish[x][l - j - 1] = Fish[i][j];
            Fish[i][j] = -1;

            Height[j]--;
            Height[l - j - 1]++;
        
            Length[i]--;
            Length[x]++;
        }
    }

    update();
    inRow();
}

int calDiff() {
    int maxF = 0;
    int minF = 10001;
    for (int i = 0; i < N; i++) {
        if (maxF < Fish[0][i]) {
            maxF = Fish[0][i];
        }
        if (minF > Fish[0][i]) {
            minF = Fish[0][i];
        }
    }
    return maxF - minF;
}

int main() {
    cin >> N >> K;
    reset();
    for (int i = N - 1; i >= 0; i--) {
        cin >> Fish[0][i];
    }
    int cnt = 0;
    while (calDiff() > K) {
        organize1();
        organize2();
        cnt++;
    }
   
    cout << cnt;
}

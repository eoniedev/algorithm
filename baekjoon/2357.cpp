#include<iostream>
#include<vector>
#include<algorithm>
#include<cmath>
using namespace std;
int N, M;
int Num[100001];
vector<int> MaxSeg, MinSeg;

int generateMin(int node, int start, int end) {
    if(start == end) {
        return MinSeg[node] = Num[start];
    }
    int mid = (start+end) / 2;
    int left = generateMin(node*2, start, mid);
    int right = generateMin(node*2+1, mid+1, end);
    return MinSeg[node] = min(left, right);
}


int generateMax(int node, int start, int end) {
    if(start == end) {
        return MaxSeg[node] = Num[start];
    }
    int mid = (start+end) / 2;
    int left = generateMax(node*2, start, mid);
    int right = generateMax(node*2+1, mid+1, end);
    return MaxSeg[node] = max(left, right);
}

int findMax(int node, int start, int end, int left, int right) {
    if(end < left || start > right) {
        return 0;
    }
    if(start >= left && end <= right) {
        return MaxSeg[node];
    }
    int mid = (start+end) / 2;
    int lmax = findMax(node*2, start, mid, left, right);
    int rmax = findMax(node*2+1, mid+1, end, left, right);
    return max(lmax, rmax);
}


int findMin(int node, int start, int end, int left, int right) {
    if(end < left || start > right) {
        return 1000000001;
    }
    if(start >= left && end <= right) {
        return MinSeg[node];
    }
    int mid = (start+end) / 2;
    int lmin = findMin(node*2, start, mid, left, right);
    int rmin = findMin(node*2+1, mid+1, end, left, right);
    return min(lmin, rmin);
}


int main() {
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);
    cin >> N >> M;
    
    int height = (int)ceil(log2(N));
    MaxSeg.resize(1 << (height+1));
    MinSeg.resize(1 << (height+1));
    
    for(int i=0; i<N; i++){
        cin >> Num[i];
    }
    
    generateMax(1, 0, N-1);
    generateMin(1, 0, N-1);
    
    for(int i=0; i<M; i++){
        int a, b;
        cin >> a >> b;
        cout << findMin(1, 0, N-1, a-1, b-1) << " " << findMax(1, 0, N-1, a-1, b-1) << '\n';
    }
}   
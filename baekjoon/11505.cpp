#include<iostream>
#include<vector>
#include<cmath>
#define MOD 1000000007;
using namespace std;
long long Nums[1000001];
int N, M, K;
vector<unsigned long long> Seg;

long long generate(int node, int start, int end) {
    if(start == end) {
        return Seg[node] = Nums[start];
    }
    int mid = (start + end) / 2;
    unsigned long long left = generate(node*2, start, mid);
    unsigned long long right = generate(node*2+1, mid + 1, end);
    Seg[node] = (left * right) % MOD;
    return Seg[node];
}

void update(int node, int start, int end, int index, long long mul) {
    if(index < start || index > end) {
        return;
    }
    if(start == end) {
        Seg[node] = mul;
        return;
    }
    int mid = (start + end) / 2;
    update(node*2, start, mid, index, mul);
    update(node*2+1, mid+1, end, index, mul);
    Seg[node] = (Seg[node*2] * Seg[node*2+1]) % MOD;
}


long long mult(int node, int start, int end, int left, int right) {
    if(left > end || right < start) {
        return 1;
    }
    if(left <= start && right >= end) {
        return Seg[node];
    }
    int mid = (start + end) / 2;
    unsigned long long lmul = mult(node*2, start, mid, left, right);
    unsigned long long rmul = mult(node*2+1, mid+1, end, left, right);
    return (lmul * rmul) % MOD;
}
int main() {
    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    cin >> N >> M >> K;
    int height = (int)ceil(log2(N));
    Seg.resize(1 << (height+1));

    for(int i=0 ;i<N; i++){
        cin >> Nums[i];
    }

    generate(1, 0, N-1);

    for(int i=0; i<M+K; i++){
        long long a, b, c;
        cin >> a >> b >> c;
        switch(a) {
        case 1:
            update(1, 0, N-1, b-1, c);
            Nums[b-1] = c;
            break;
        case 2:
            cout << mult(1, 0, N-1, b-1, c-1) << '\n';
            break;
        }
    }
}
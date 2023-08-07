#include<iostream>
#include<vector>
#include<cmath>
using namespace std;
long long N, M, K;
long long Nums[1000001];
vector<long long> Seg;

long long generate(long long node, long long start, long long end) {
    if(start == end) {
        return Seg[node] = Nums[start];
    }
    long long mid = (start + end) / 2;
    long long left = generate(node*2, start, mid);
    long long right = generate(node*2+1, mid+1, end);
    Seg[node] = left + right;

    return Seg[node];
}

long long sum(long long node, long long start, long long end, long long left, long long right) {
    if(left > end || right < start) {
        return 0;
    }
    if(left <= start && end <= right) {
        return Seg[node];
    }
    long long mid = (start + end) / 2;
    long long lsum = sum(node*2, start, mid, left, right);
    long long rsum = sum(node*2+1, mid+1, end, left, right);

    return lsum + rsum;
}

void update(long long node, long long start, long long end, long long index, long long diff) {
    if(index > end || index < start) {
        return ;
    }
    Seg[node] += diff;

    if(start != end) {
        long long mid = (start + end) / 2;
        update(node*2, start, mid, index, diff);
        update(node*2+1, mid+1, end, index, diff);
    }
}

int main(){
    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    cin >> N >> M >> K;
    long long height = (long long) ceil(log2(N));
    long long size = 1 << (height + 1);
    Seg.resize(size);

    for(long long i=1; i<=N; i++){
        cin >> Nums[i];
    }
    generate(1, 1, N);

    for(long long i=0; i<M+K; i++){
        long long a, b, c;
        cin >> a >> b >> c;
        switch(a) {
        case 1:
            update(1, 1, N, b, c - Nums[b]);
            Nums[b-1] = c;
            break;
        case 2:
            cout << sum(1, 1, N, b, c) << '\n';
            break;
        }
    }
}
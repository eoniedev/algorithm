#include<iostream>
#include<cmath>
#include<algorithm>
#include<vector>
#include<tuple>

using namespace std;
int N = 0;
vector<int> Nums;
pair<int,int> Cnt[8001];

int main() {
    int sum = 0;   
    int num = 0;

    cin >> N;

    for(int i=0; i<N; i++) {
        cin >> num;
        sum += num;
        Cnt[num + 4000].first++;
        Cnt[num + 4000].second = num;
        Nums.push_back(num);
    }

    sort(Nums.begin(), Nums.end());
    sort(Cnt, Cnt+8001, [](auto const& l, auto const& r) {
        if(l.first == r.first) return l.second < r.second;
        return l.first > r.first;
    });
    
    int freq = Cnt[0].second;
    if(Cnt[0].first == Cnt[1].first){
        freq = Cnt[1].second;
    }

    cout << round((double)sum/N) + 0 << "\n";
    cout << Nums[N/2] << "\n";
    cout << freq << "\n";
    cout << Nums[N-1] - Nums[0] << "\n";
}
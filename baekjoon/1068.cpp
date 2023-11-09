#include<iostream>
#include<vector>
using namespace std;
int N, Root, Target, Cnt;
vector<int> Tree[51];

void dfs(int curr) {
	if (Tree[curr].size() == 0) {
		Cnt++;
		return;
	}
	if (Tree[curr].size() == 1 && Tree[curr][0] == Target) {
		Cnt++;
		return;
	}

	for (int i = 0; i < Tree[curr].size(); i++) {
		int next = Tree[curr][i];
		if(next != Target)
			dfs(next);
	}
}

int main() {
	cin >> N;
	for (int i = 0; i < N; i++) {
		int node;
		cin >> node;
		if (node == -1) {
			Root = i;
		}
		else {	
			Tree[node].push_back(i);
		}
	}
	cin >> Target;
	if(Target != Root)
		dfs(Root);

	cout << Cnt;
}

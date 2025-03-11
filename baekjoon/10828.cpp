#include<iostream>
#include<unordered_map>
using namespace std;
int N;

class list {
    int point = 0;
    int num[10002];

    public:
        list(){}

        void push(int x) {
            num[point++] = x;
        }

        int pop() {
            if(point == 0) {
                return -1;
            }
            return num[--point];
        }

        int empty() {
            if(point == 0) {
                return 1;
            }
            return 0;
        }

        int top() {
            if(point == 0) {
                return -1;
            }
            return num[point-1];
        }

        int size() {
            return point;
        }
};

unordered_map<string, int> Cmd{
    {"push", 0}, 
    {"pop", 1}, 
    {"size", 2},
    {"empty", 3},
    {"top", 4}
};

int main() {
    string c;
    int p;
    list* l = new list();
    
    cin >> N;

    for(int i=0; i<N; i++) {
        cin >> c;
        switch(Cmd[c]) {
            case 0:
                cin >> p;
                l->push(p);
                break;
            case 1:
                cout << l->pop() << "\n";
                break;
            case 2:
                cout << l->size() << "\n";
                break;
            case 3:
                cout << l->empty() << "\n";
                break;
            case 4:
                cout << l->top() << "\n";
                break;
            
        }
    }
}

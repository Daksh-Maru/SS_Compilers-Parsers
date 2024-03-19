#include<bits/stdc++.h>
using namespace std;

set<char> nonTerminals;
set<char> terminals;

string inp;

bool isTerminal(int ptr) {
    return 'A'<= inp[ptr] && inp[ptr] <= 'Z';
}

bool func_nt(int ptr) {
    if(isTerminal(ptr)) return 1;
    
}

bool func_t(int ptr) {

}


void match(int ptr) {
    
}

int main() {
    int n; 
    cout << "Enter total number of production rules" << endl;
    cin >> n;

    vector<string> cfg (n);
    for(int i=0; i<n; ++i) {
        cin >> cfg[i];
    }
   
    /* filter out terminals and non terminals */
    for(int i=0; i<n; ++i) {
        nonTerminals.insert(cfg[i][0]);
        for(int j=3; j<cfg[i].size(); ++j) {
            if(cfg[i][j] == '|') continue;
            if(cfg[i][j] >= 'A' && cfg[i][j] <= 'Z') continue;
            terminals.insert(cfg[i][j]);
        }
    }

    cin >> inp;
    int ptr = 0;

}
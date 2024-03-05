#include<bits/stdc++.h>
using namespace std;
 
/*
    @AUTHOR :-
    DAKSH MARU
    UI22CS14
*/


set<char> terminals;
set<char> nonterminals;
char ext = 'Z';


vector<string> handle_lr(vector<string> cfg) {


    int n = cfg.size();
    vector<string> updated_cfg;


    vector<string> new_productions;
    for(int i=0; i<n; ++i) { // traversing each production.
        string update_prod = "";
        string new_prod = "";
        bool lr = false;
        for(int j=3; j<cfg[i].size(); ++j) { // traversing each production rule.
            if(j==3 || cfg[i][j-1] == '|') { // to check the start of production
                int k=j;
                if(cfg[i][j] == cfg[i][0]) {
                    lr = true;
                    k++;
                    while(cfg[i][k] != '|' && k < cfg[i].size() ) { // traversing each production
                        new_prod.push_back(cfg[i][k]);
                        k++;
                    }
                    new_prod.push_back(ext);
                    new_prod.push_back('|');
                }
                else {
                    while(cfg[i][k] != '|' && k < cfg[i].size() ) { // traversing each production
                        update_prod.push_back(cfg[i][k]);
                        k++;
                    }
                    update_prod.push_back(ext);
                    update_prod.push_back('|');
                }




            }
        }


        // if left recursion is found.
        if(lr) {
            new_prod.push_back('#');
            update_prod.pop_back();


            string temp1;
            temp1.push_back(cfg[i][0]); temp1+="->"; temp1+=update_prod;
            cfg[i] = temp1;
           
            string temp2;
            temp2.push_back(ext); temp2+="->"; temp2+=new_prod;
            new_productions.push_back(temp2);
            ext--;
        }
    }


    for(auto it : new_productions) {
        cfg.push_back(it);
    }
    updated_cfg = cfg;
    return updated_cfg;
}




vector<string> handle_lf(vector<string> cfg) {


    cfg = handle_lr(cfg);
    int n = cfg.size();


    vector<string> updated_cfg;


    for(int i=0; i<n; ++i) { // traversing every production rule.


        map<char, vector<string>> mp;
        string update_prod="";
        vector<string> new_prod;
       
        for(int j=3; j<cfg[i].size(); ++j) { // traversing a particular rule.
            if((j==3 || cfg[i][j-1] == '|') && terminals.count(cfg[i][j])) { // if first element is terminal.
               
                int k=j+1;
                string temp;
                while(cfg[i][k] != '|' && k < cfg[i].size() ) { // traversing each production
                    temp.push_back(cfg[i][k]);
                    k++;
                }
                mp[cfg[i][j]].push_back(temp);


            }
        }






        char tmp = ext;
        string temp = cfg[i].substr(0,3);
        for(auto it :mp) {
            if(it.second.size() <= 1) continue;
            string str = "";
            str.push_back(it.first);
            str.push_back(tmp); tmp--;
            str.push_back('|');
            temp += str;
        }
        temp.pop_back();
        if(temp.size() > 3) cfg[i] = temp;




        for(auto it : mp) {
            if(it.second.size() <= 1) continue;
            string temp;
            temp.push_back(ext); ext--;
            temp+="->";
            for(string prod : it.second) {
                temp+=prod;
                temp.push_back('|');
            }
            temp.pop_back();
            new_prod.push_back(temp);
        }


        for(string rules : new_prod) {
            cfg.push_back(rules);
        }
    }


    updated_cfg = cfg;
    return updated_cfg;
}




map<char,set<char>> first(vector<string> cfg) {
    cfg = handle_lf(cfg);
    int n = cfg.size();


    map<char, set<char>> mp;
    for(int i=0; i<n; ++i) { // traversing all productions.
        for(int j=3; j<cfg[i].size(); ++j)  { // traversing a production rule.
            if(j==3 || cfg[i][j-1] == '|') { // if first element.
                if(cfg[i][j] =='#' || terminals.count(cfg[i][j])) { // if first element of prod. is terminal directly it will be the first.
                    mp[cfg[i][0]].insert(cfg[i][j]);
                }
                else {
                    if(mp.count(cfg[i][j])) mp[cfg[i][0]].insert(mp[cfg[i][j]].begin(), mp[cfg[i][j]].end());
                }
            }
        }
    }
    for(int i=0; i<n; ++i) {
        for(int j=3; j<cfg[i].size(); ++j)  { // traversing a production rule.
            if(j==3 || cfg[i][j-1] == '|') { // if first element.    
                if(cfg[i][j] =='#' || terminals.count(cfg[i][j])) { // if first element of prod. is terminal directly it will be the first.
                    mp[cfg[i][0]].insert(cfg[i][j]);
                }
                else {
                    if(mp.count(cfg[i][j])) mp[cfg[i][0]].insert(mp[cfg[i][j]].begin(), mp[cfg[i][j]].end());
                }
            }
        }
    }
    return mp;
}




map<char, set<char>> follow(vector<string> cfg) {
   
    map<char, set<char>> mp = first(cfg);
    map<char, set<char>> flw;
    flw[cfg[0][0]].insert('$');
    int n = cfg.size();
    for(int k=0; k<n; ++k) { // to traverse all non terminals.
        for(int i=0; i<n; ++i) { // to traverse all produciton rules;
            for(int j=4; j<cfg[i].size(); ++j) { // to travers a particular production.
                if(cfg[i][j]!='|' && cfg[i][j-1] == cfg[k][0]) {
                    if(terminals.count(cfg[i][j])) {
                        flw[cfg[k][0]].insert(cfg[i][j]);
                    }
                    else {
                        flw[cfg[k][0]].insert(mp[cfg[i][j]].begin(), mp[cfg[i][j]].end());
                    }
                }
                else if(cfg[i][j] == '|' && cfg[i][j-1] == cfg[k][0]) {
                    if(flw.count(cfg[i][0])) flw[cfg[k][0]].insert(flw[cfg[i][0]].begin(), flw[cfg[i][0]].end());
                }
                if( j==(cfg[i].size()-1) && cfg[i][j] == cfg[k][0]) {
                    if(flw.count(cfg[i][0])) flw[cfg[k][0]].insert(flw[cfg[i][0]].begin(), flw[cfg[i][0]].end());
                }
            }
        }
    }
    for(int k=0; k<n; ++k) { // to traverse all non terminals.
        for(int i=0; i<n; ++i) { // to traverse all produciton rules;
            for(int j=4; j<cfg[i].size(); ++j) { // to travers a particular production.
                if(cfg[i][j]!='|' && cfg[i][j-1] == cfg[k][0]) {
                    if(terminals.count(cfg[i][j])) {
                        flw[cfg[k][0]].insert(cfg[i][j]);
                    }
                    else {
                        flw[cfg[k][0]].insert(mp[cfg[i][j]].begin(), mp[cfg[i][j]].end());
                    }
                }
                else if(cfg[i][j] == '|' && cfg[i][j-1] == cfg[k][0]) {
                    if(flw.count(cfg[i][0])) flw[cfg[k][0]].insert(flw[cfg[i][0]].begin(), flw[cfg[i][0]].end());
                }
                if( j==(cfg[i].size()-1) && cfg[i][j] == cfg[k][0]) {
                    if(flw.count(cfg[i][0])) flw[cfg[k][0]].insert(flw[cfg[i][0]].begin(), flw[cfg[i][0]].end());
                }
            }
        }
    }
    return flw;
}
void parsing_table(vector<string> cfg) {
    vector<string> curr_cfg;
    curr_cfg = handle_lf(cfg);


}


int main() {


    /* Taking input of production rules */
    cout << "Total number of production rules" << endl;
    int n;
    cin >> n;
    cout << endl;


    /* Taking input of cfg */
    cout << "Enter cfg one by one without space like A->c|B" << endl;


    vector<string> cfg (n);
    for(int i=0; i<n; ++i) {
        cin >> cfg[i];
    }
   
    /* filter out terminals and non terminals */
    for(int i=0; i<n; ++i) {
        nonterminals.insert(cfg[i][0]);
        for(int j=3; j<cfg[i].size(); ++j) {
            if(cfg[i][j] == '|') continue;
            if(cfg[i][j] >= 'A' && cfg[i][j] <= 'Z') continue;
            terminals.insert(cfg[i][j]);
        }
    }




    cout << endl;
    cout << "=====================================" << endl;
    cout << "MENU" << endl;
    cout << "1 --> To handle left recursion." << endl;
    cout << "2 --> To handle left factoring." << endl;
    cout << "3 --> To get firsts." << endl;
    cout << "4 --> To get follows." << endl;
    cout << "5 --> To get parsing table." << endl;
    cout << "Anything else --> To exit." << endl;
    cout << "=====================================" << endl;
    cout << endl;




    while(1) {
        int x; cin >> x;
        vector<string> curr_cfg;
        map<char, set<char>> fst;
        map<char, set<char>> folw;
        switch(x){
            case 1: {
                curr_cfg = handle_lr(cfg);
                cout << endl;
                cout << "CFG after removing left recursion" << endl;
                cout << endl;
                for(int i=0; i<curr_cfg.size(); ++i) {
                    cout << curr_cfg[i] << endl;
                }
                cout << endl;
                break;
            }
            case 2: {
                curr_cfg = handle_lf(cfg);
                cout << endl;
                cout << "CFG after removing left factoring" << endl;
                cout << endl;
                for(int i=0; i<curr_cfg.size(); ++i) {
                    cout << curr_cfg[i] << endl;
                }
                cout << endl;
                break;
            }
            case 3: {
                cout << endl;
                cout << "First()" << endl;
                fst = first(cfg);
                for(auto ele : fst) {
                    string temp;
                    for(auto val : ele.second) {
                        temp.push_back(val);
                        temp.push_back(',');
                    }
                    temp.pop_back();


                    cout << ele.first << " --> " << "{ " << temp << " }" << endl;
                }
                cout << endl;
                break;
            }
            case 4: {
                cout << endl;
                cout << "Follow()" << endl;
                folw = follow(cfg);
                for(auto ele : folw) {
                    string temp;
                    for(auto val : ele.second) {
                        temp.push_back(val);
                        temp.push_back(',');
                    }
                    temp.pop_back();


                    cout << ele.first << " --> " << "{ " << temp << " }" << endl;
                }
                cout << endl;
                break;
            }
            case 5: {
                parsing_table(cfg);
                break;
            }
            default: cout << "Exiting!!!" << endl; return 0;
        }
    }
}

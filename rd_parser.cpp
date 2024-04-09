#include<bits/stdc++.h>
using namespace std;
string lookahead;
int i = 0;
bool S();
bool E();
bool S_d();


// Rule :
// S -> S + E | E
// E -> ( S ) | id
// As it has Left Recursion we must remove it in order to get correct Answer
// S -> E S'
// S' -> + E S' | epsilon
// E -> ( S ) | id

bool S_d(){
    cout<<"current lookahead "<<lookahead[i]<<endl;
    if(lookahead[i] == '+'){
        i++;
        if(E()){
            if(S_d()){
                return true;
            }
            else{
                return false;
            }
        }
        else{
            return false;
        }
    }
    return true;
}

bool E(){
    cout<<"current lookahead "<<lookahead[i]<<endl;
    if(lookahead[i] == '('){
        i++;
        if(S()){
            if(lookahead[i] == ')'){
                i++;
                return true;
            }


        }
    }
    else if(lookahead[i] == 'i'){
        i++;
        return true;
    }
    return false;
}

bool S(){
    cout<<"current lookahead "<<lookahead[i]<<endl;
    if(E()){
        if(S_d()){
            return true;
        }
    }
    return false;
}

int main(){
    string ans;
    cout<<"Enter the string : ";
    cin>>ans;
    lookahead = ans;


    if(S() && lookahead[i] == '\0'){
        cout<<"String Accepted"<<endl;
    }else{
        cout<<"String Rejected"<<endl;
    }
}


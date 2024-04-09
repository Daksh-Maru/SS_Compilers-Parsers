#include<bits/stdc++.h>
using namespace std;

#define ce cout<<"\n"
#define x first
#define y second

inline bool isbracket(string s) {return s.find('(')!= string::npos;}
map<char,string>m;
// map<char,string>mp;
char c='A';
string s;
// a+b*c+d+e
// 012345678
void fstardivision(int x,int y){
// if(!isbracket(s)) return;
for(int i=x;i<=y;i++)
{
if(s[i]=='/'){
m[c]=s.substr(i-1,3);
s=s.substr(0,i-1)+c+s.substr(i+2);
c++;
cout<<s<<endl;
i--;
}
}
for(int i=x;i<=y;i++)
{
if(s[i]=='*' ){
m[c]=s.substr(i-1,3);
s=s.substr(0,i-1)+c+s.substr(i+2);
c++;
cout<<s<<endl;
i--;
}
}
}
void fplus(int x,int y){
for(int i=x;i<=y;i++)
{
if(s[i]=='+'){
m[c]=s.substr(i-1,3);
s=s.substr(0,i-1)+c+s.substr(i+2);
c++;
cout<<s<<endl;
//Aim: Implement a program for Intermediate Code Generation method - 3 Address Code.Code:
i--;
}
}
}
void fminus(int x,int y){
for(int i=x;i<=y;i++)
{
if(s[i]=='-'){
m[c]=s.substr(i-1,3);
s=s.substr(0,i-1)+c+s.substr(i+2);
c++;
cout<<s<<endl;
i--;
}
}
}
void func(int x,int y){
if(s[0]=='-'){
x++;
m[c]=s.substr(0,2);
s=c+s.substr(2);
cout<<s;ce;
c++;
}
if(s[0]=='+') s=s.substr(1);
fstardivision(x,y);
fplus(x,y);
fminus(x,y);
}
map<char,string>generate_map(int x)
{
int u=x;
map<char,string>mp;
for(auto i:m){
string op="["+to_string(u)+"]";
mp[i.x]=op;
u++;
}
return mp;
}
string give_s(map<char,string>mp,char c){
string h;h+=c;
if(isupper(c)) return mp[c];
return h;
}
void quadraple(){
cout<<"Sr.No. | "<<"Operator | "<<"Operand1 | "<<"Operand2 | "<<"Result";ce;
int u=0;
string space(10,' ');
for(auto i:m){
string op="["+to_string(u)+"]";
if(i.y.size()==2)
cout<<op<<"\t\t"<<(i.y[0])<<space<<i.y[1]<<"\t\t"<<""<<space<<i.x;
else 
cout<<op<<"\t\t"<<i.y[1]<<space<<i.y[0]<<"\t\t"<<i.y[2]<<space<<i.
x;
ce;
// mp[i.x]=op;
u++;
}
}
void triple(){
cout<<"Sr.No. | "<<"Operator | "<<"Operand1 | "<<"Operand2";ce;
map<char,string>mp=generate_map(0);
int u=0;
string space(10,' ');
for(auto i:m){
string op="["+to_string(u)+"]";
if(i.y.size()==2)
cout<<op<<"\t\t"<<(i.y[0])<<space<<give_s(mp,i.y[1])<<" ";
else 
cout<<op<<"\t\t"<<(i.y[1])<<space<<give_s(mp,i.y[0])<<"\t\t"<<give_s(mp,i.y[2]
);
ce;
u++;
}
}
void intriple(){
int u;
cout<<"Enter no:";cin>>u;
map<char,string>mp=generate_map(u);
cout<<"Sr.No. | "<<"Operator | "<<"Operand1 | "<<"Operand2";ce;
string space(10,' ');
for(auto i:m){
string op="["+to_string(u)+"]";
if(i.y.size()==2)
cout<<op<<"\t\t"<<(i.y[0])<<space<<i.y[1]<<"\t\t"<<"";
else 
cout<<op<<"\t\t"<<(i.y[1])<<space<<give_s(mp,i.y[0])<<"\t\t"<<give_s(mp,i.y[2]);ce;
u++;
}
}
int main() 
{
cout<<"Enter String :";
cin>>s;
cout<<"Reduction of String to 3-address Code:\n";ce;
if(isbracket(s)){
int ind =s.find('(');
int ind2 =s.find(')');
func(ind,ind2);
s.erase(s.find('('),1);
s.erase(s.find(')'),1);
}
func(0,s.size()-1);ce;
cout<<"Assigned Variables & their Respective Equations:";ce;
for(auto i:m)
cout<<i.x<<" = "<<i.y<<endl;
ce;
cout<<"Quadraple Table:";ce;
quadraple();ce;
cout<<"Direct Triples Table:";ce;
triple();ce;
cout<<"InDirect Triples Table:";ce;
intriple();ce; 
}

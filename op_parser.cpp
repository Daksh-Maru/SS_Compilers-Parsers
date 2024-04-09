#include <bits/stdc++.h>

using namespace std;
// Sample CFG =>
// E->T*T|F
// F->F+F|T
// T->(E)|id

bool opPri(string a, string b) {
    if (a >= "a" && a <= "z") {
        if (b >= "a" && b <= "z")
            return false;
        else
            return true;
    } else if (a == "/"
        or a == "*") {
        if (b >= "a" && b <= "z")
            return false;
        else if (b == "/"
            or b == "*")
            return false;
        else
            return true;
    } else if (a == "+"
        or a == "-") {
        if (b == "+"
            or b == "-"
            or(b >= "a" && b <= "z") or b == "/"
            or b == "*")
            return false;
    }
    return false;
}

vector < string > a;
void sortvect() {
    string temp;
    for (int i = 0; i < a.size(); i++) {
        for (int j = 0; j < a.size(); j++) {
            if (opPri(a[i], a[j])) {
                temp = a[i];
                a[i] = a[j];
                a[j] = temp;
            }
        }
    }
}

vector < vector < char >> prec;

void printPrecedence(vector < string > v) {
    unordered_set < char > s;
    for (int i = 0; i < v.size(); i++) {
        for (int j = 3; j < v[i].size(); j++) {
            if (v[i][j] == '*' || v[i][j] == '/' || v[i][j] == '+' || v[i][j] == '-' || islower(v[i][j]))
                s.insert(v[i][j]);
        }
    }

    std::cout << "f/g\t";
    for (auto i = s.begin(); i != s.end(); i++) {
        string str;
        str.push_back( * i);
        a.push_back(str);
    }
    a.push_back("$");
    sortvect();
    for (auto ele: a)
        std::cout << ele << "\t";
    std::cout << endl;
    for (int i = 0; i < a.size(); i++) {
        vector < char > temp;
        std::cout << a[i] << "\t";
        string match = a[i];
        for (int j = 0; j < a.size(); j++) {
            if (islower(match[0])) {
                if (islower(a[j][0])) {
                    std::cout << "-\t";
                    temp.push_back('-');
                } else {
                    std::cout << ">\t";
                    temp.push_back('>');
                }
            } else if (match == "$") {
                if (a[j] != "$") {
                    std::cout << "<\t";
                    temp.push_back('<');
                } else {
                    std::cout << "-\t";
                    temp.push_back('-');
                }
            } else {
                if (a[j] == "id") {
                    std::cout << "<\t";
                    temp.push_back('<');
                } else if (islower(a[j][0])) {
                    std::cout << "<\t";
                    temp.push_back('<');
                } else if (a[j] == "$") {
                    std::cout << ">\t";
                    temp.push_back('>');
                } else {
                    if (a[i][0] == a[j][0]) {
                        std::cout << ">\t";
                        temp.push_back('>');
                    } else {
                        if (match[0] == '+' && a[j][0] == '+') {
                            std::cout << ">\t";
                            temp.push_back('>');
                        } else if (match[0] == '+' && a[j][0] == '-') {
                            std::cout << ">\t";
                            temp.push_back('>');
                        } else if (match[0] == '+' && a[j][0] == '*') {
                            std::cout << "<\t";
                            temp.push_back('<');
                        } else if (match[0] == '+' && a[j][0] == '/') {
                            std::cout << "<\t";
                            temp.push_back('<');
                        }

                        // For '-' operator
                        if (match[0] == '-' && a[j][0] == '+') {
                            std::cout << ">\t";
                            temp.push_back('>');
                        } else if (match[0] == '-' && a[j][0] == '-') {
                            std::cout << ">\t";
                            temp.push_back('>');
                        } else if (match[0] == '-' && a[j][0] == '*') {
                            std::cout << "<\t";
                            temp.push_back('<');
                        } else if (match[0] == '-' && a[j][0] == '/') {
                            std::cout << "<\t";
                            temp.push_back('<');
                        }

                        // For '*' operator
                        if (match[0] == '*' && a[j][0] == '+') {
                            std::cout << ">\t";
                            temp.push_back('>');
                        } else if (match[0] == '*' && a[j][0] == '-') {
                            std::cout << ">\t";
                            temp.push_back('>');
                        } else if (match[0] == ' ' && a[j][0] == ' ') {
                            std::cout << ">\t";
                            temp.push_back('>');
                        } else if (match[0] == '*' && a[j][0] == '/') {
                            std::cout << ">\t";
                            temp.push_back('>');
                        }

                        // For '/' operatorstring
                        if (match[0] == '/' && a[j][0] == '+') {
                            std::cout << ">\t";
                            temp.push_back('>');
                        } else if (match[0] == '/' && a[j][0] == '-') {
                            std::cout << ">\t";
                            temp.push_back('>');
                        } else if (match[0] == '/' && a[j][0] == '*') {
                            std::cout << ">\t";
                            temp.push_back('>');
                        } else if (match[0] == '/' && a[j][0] == '/') {
                            std::cout << ">\t";
                            temp.push_back('>');
                        }
                    }
                }
            }
        }
        std::cout << endl;
        prec.push_back(temp);
        temp.clear();
    }
    return;
}

map < string, int > longPth;

void funcvalF(int charIdx) {
    int maxans = 0, temp;
    if (a[charIdx] == "$") {
        longPth["f" + a[charIdx]] = maxans;
        return;
    }
    for (int j = 0; j < prec[charIdx].size(); j++) {
        if (prec[charIdx][j] == '>') {
            temp = longPth["g" + a[j]];
            if (maxans <= temp) {
                maxans = temp + 1;
            }
        }
    }
    longPth["f" + a[charIdx]] = maxans;
}

void funcvalG(int charIdx) {
    int maxans = 0, temp;
    if (a[charIdx] == "$") {
        longPth["g" + a[charIdx]] = maxans;
        return;
    }
    for (int j = 0; j < prec[charIdx].size(); j++) {
        if (prec[j][charIdx] == '<') {
            temp = longPth["f" + a[j]];
            if (maxans <= temp) {
                maxans = temp + 1;
            }
        }
    }
    longPth["g" + a[charIdx]] = maxans;
}

void functable() {
    for (int i = a.size() - 1; i >= 0; i--) {
        funcvalG(i);
        funcvalF(i);
    }
    std::cout << "Function Table :-\n";
    std::cout << "\t";
    for (auto ele: a) {
        std::cout << ele << "\t";
    }
    std::cout << endl << "f\t";
    for (int i = 0; i < a.size(); i++) {
        std::cout << longPth["f" + a[i]] << "\t";
    }
    std::cout << endl << "g\t";
    for (int i = 0; i < a.size(); i++) {
        std::cout << longPth["g" + a[i]] << "\t";
    }
}

map < string, vector < string >> getMap(vector < string > v) {
    map < string, vector < string >> m;
    for (int i = 0; i < v.size(); i++) {
        string str;
        str.push_back(v[i][0]);
        if (v[i][1] == '\'') {
            str.push_back(v[i][1]);
        }
        int ind_first_char = v[i].find("->");
        int ind_pipe = v[i].find("|");
        int starting = ind_first_char + 2;
        vector < string > ans;
        string val;
        for (int j = starting; j < v[i].size(); j++) {
            if (v[i][j] != '|') {
                val.push_back(v[i][j]);
            } else {
                ans.push_back(val);
                val.clear();
            }
        }
        ans.push_back(val);
        // m.insert({str, ans});
        m[str] = ans;
    }
    return m;
}

map < string, vector < string >> m;

bool isterm(char c) {
    if (c >= 'A' && c <= 'Z')
        return false;
    return true;
}

int checkstring(string start) {
    if (start[0] != 'i') {
        return 0;
    }
    int point = 0;
    stack < char > st;
    string samp;
    samp.push_back('$');
    st.push('$');
    start.push_back('$');
    cout << "Stack\tAction\t\tInput\n";
    cout << st.top() << "\t" << "shift i" << "\t\t" << start << endl;
    samp.push_back(start[point]);
    st.push(start[point]);
    point++;
    while (!st.empty()) {
        if (st.top() == 'i') {
            // Reduce with E->id
            cout << samp << "\t" << "Reduce E->i" << "\t\t" << start.substr(point, start.size() - point) << endl;
            st.pop();
            st.push('E');
            samp.pop_back();
            samp.push_back('E');
        } else if (st.top() == '+' || st.top() == '-' || st.top() == '*' || st.top() == '/') {
            cout << samp << "\t" << "Shift " << st.top() << "\t\t" << start.substr(point, start.size() - point) << endl;
        }

        if (samp.size() == 4) {
            // Reduce Production if found else return 0
            bool found = false;
            cout << samp << endl;
            for (auto & i: m) {
                vector < string > temp = i.second;
                for (int i = 0; i < temp.size(); i++) {
                    for (int j = 0; j < temp[i].size(); j++) {
                        if (temp[i][j] >= 'A' && temp[i][j] <= 'Z') {
                            temp[i][j] = 'E';
                        }
                    }
                }

                auto it = find(temp.begin(), temp.end(), samp.substr(1, samp.size() - 1));
                if (it != temp.end()) {
                    cout << samp << "\t" << "Reduce E" << "->" << samp.substr(1, samp.size() - 1) << "\t\t" << start.substr(point, start.size() - point) << endl;
                    st.pop();
                    st.push('E');
                    samp.pop_back();
                    samp.pop_back();
                    samp.pop_back();
                    samp.push_back('E');

                    if (st.top() == 'E' && point == start.size() - 1) {
                        cout << samp << "\t" << "Accept" << "\t\t" << start.substr(point, start.size() - point) << endl;
                        return 1;
                    }
                    found = true;
                    break;
                }
            }
            if (!found) {
                return 0;
            }
        }

        if (point < start.size() - 1) {

            if (start[point] == 'i') {
                cout << samp << "\t" << "shift i" << "\t\t" << start.substr(point, start.size() - point) << endl;
            }

            st.push(start[point]);
            samp.push_back(start[point]);
            point++;
        }
    }
    return 1;
}

int main() {
    int n;
    std::cout << "Enter number of lines of your grammer => " << endl;
    cin >> n;
    vector < string > v;
    std::cout << "Enter your grammer line by line => " << endl;
    for (int i = 0; i < n; i++) {
        string s;
        cin >> s;
        v.push_back(s);
    }
    // v.push_back("E->T+T|Z");
    // v.push_back("T->a*b");
    // v.push_back("Z->c/d|e-f");
    printPrecedence(v);
    m = getMap(v);
    cout << endl;
    for (auto & i: m) {
        vector < string > temp = i.second;
        for (int j = 0; j < temp.size(); j++) {
            std::cout << i.first << "->";
            std::cout << temp[j] << endl;
        }
    }
    std::cout << endl;
    functable();
    std::cout << endl;
    // CheckString
    cout << endl << "Enter the string to check => ";
    string sample;
    cin >> sample;

    if (checkstring(sample)) {
        cout << "String is accepted\n";
    } else {
        cout << "String is not accepted\n";
    }
    return 0;
}
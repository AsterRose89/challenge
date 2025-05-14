#include <iostream>
#include <string>
using namespace std;

int main() {
    string input[100];
    string s, in;
    string first[100];
    string end[100];
    int n = 0;
    bool onceFlags[100] = {false};// 新增：用于记录一次性指令是否执行过

    cin >> s;

    cout << s << endl;
    while (cin >> in) {
        input[n] = in;
        n++;
    }
   
    bool hasChange = true;
    while (hasChange) {
        hasChange = false;
        for (int j = 0; j < n; j++) {
            size_t index = input[j].find('=');
            first[j] = input[j].substr(0, index);
            end[j] = input[j].substr(index + 1);
            cout << first[j] << " "  << end[j] << endl;
            // 处理一次性指令
            if (first[j].find("(once)") != string::npos) {
                if (onceFlags[j]) {
                    continue;
                }
                first[j] = first[j].substr(6);
                onceFlags[j] = true;
            }

            size_t pos = s.find(first[j]);
            if (pos != string::npos) {
                // 处理return指令
                if (end[j].find("(return)") != string::npos) {
                    s = end[j].substr(8);
                    cout << s << endl;
                    return 0;
                }
                // 处理start和end指令
                
                if (first[j].find("(start)") != string::npos) {
                  // cout << first[j].find("(start)") << " " << s.find(first[j].substr(7))<< endl;
                    if (first[j].find("(start)") == 0 && s.find(first[j].substr(7)) == 0) {
                        s = end[j] + s.substr(first[j].substr(7).length());
                        cout << s << endl;
                        hasChange = true;
                        break;
                    }
                    else if (end[j].find("(start)") == 0 && s.find(first[j].substr(7)) == s.length() - first[j].substr(5).length()) {
                        s.replace(pos, first[j].length(), end[j]);
                        s= end[j].substr(7) + s;
                        cout << s << endl;
                        hasChange = true;
                        break;
                    }
                } else if (first[j].find("(end)") != string::npos) {
                    if (first[j].find("(end)") == 0 && s.find(first[j].substr(5)) == 0) {
                        s = s.substr(0, s.length() - first[j].substr(5).length()) + end[j];
                        cout << s << endl;
                        hasChange = true;
                        break;
                    }
                    else if (end[j].find("(end)") == 0 && s.find(first[j].substr(5)) == 0) {
                        s.replace(pos, first[j].length(), end[j]);
                        s += end[j].substr(5);
                        cout << s << endl;
                        hasChange = true;
                        break;
                    }
                } else {
                    s.replace(pos, first[j].length(), end[j]);
                    cout << s << endl;
                    hasChange = true;
                    break;
                }
            }
        }
    }
    return 0;
}
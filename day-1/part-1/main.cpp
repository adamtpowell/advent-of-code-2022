#include <iostream>
#include <string>
using namespace std;

int main() {
    int count = 0;
    int max = 0;

    for (string line; getline(cin, line);) {
        if (line.compare("") == 0) {
            max = count > max ? count : max;
            count = 0;
        } else {
            count += stoi(line);
        }
    }
    max = count > max ? count : max;
    cout << max << endl;
    return 0;
}

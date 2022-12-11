#include <iostream>
#include <vector>
#include <memory>
#include <numeric>

using namespace std;

void poll(int cycles, int x, vector<int> &values) {
    if (cycles == 20 || ((cycles + 20) % 40) == 0) {
        values.emplace_back(x * cycles);
    }
}

int main() {
    // s.substr(start, end - start);

    // Read lines from stdin
    vector<string> lines;
    for (string line; getline(cin, line);) {
        lines.push_back(line);
    }

    int cycles = 0;
    int x = 1;
    vector<int> values;

    for (auto line : lines) {
        char opcode = line[0];

        if (opcode == 'a') {
            cycles += 1;
            poll(cycles, x, values);

            cycles += 1;
            poll(cycles, x, values);
            x += stoi(line.substr(5));
        } else if (opcode == 'n') {
            cycles += 1;
            poll(cycles, x, values);
        }
    }

    for (auto value : values) {
        cout << value << endl;
    }

    cout << "Sum: " << accumulate(values.begin(), values.end(), 0) << endl;

    return 0;
}

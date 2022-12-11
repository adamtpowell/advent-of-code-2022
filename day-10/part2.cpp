#include <iostream>
#include <vector>
#include <memory>
#include <numeric>

using namespace std;

string get_sprite(int x) {
    string screen = "........................................"; // The screen is 40 characters wide.

    for (int i = x - 1; i <= x + 1; i ++) {
        if (i >= 0 && i < screen.size()) {
            screen[i] = '#';
        }
    }

    return screen;
}

char get_pixel(int x, int cycle) {
    string sprite = get_sprite(x);
    return get_sprite(x)[(cycle - 1) % 40]; // Create unneeded garbage. Redo this once it works for better performance.
}

int main() {
    // Read lines from stdin
    vector<string> lines;
    for (string line; getline(cin, line);) {
        lines.push_back(line);
    }

    int cycles = 0;
    int x = 1;
    vector<char> screen;
    cout << screen.size() << endl;

    for (auto line : lines) {
        char opcode = line[0];

        if (opcode == 'a') {
            cout << "a = " << stoi(line.substr(5)) << endl;
            // The cycle starts.
            cycles += 1;

            // During the cycle, get the pixel
            screen.emplace_back(get_pixel(x, cycles));

            // The cycle starts.
            cycles += 1;

            // During the cycle, get the pixel.
            screen.emplace_back(get_pixel(x, cycles));

            // At the end of the cycle, change the x register.
            x += stoi(line.substr(5));

        } else if (opcode == 'n') {
            cout << "n" << endl;

            // The cycle starts.
            cycles += 1;

            // During the cycle, get the pixel.
            screen.emplace_back(get_pixel(x, cycles));
        }
    }

    cout << "RESULTS" << endl;

    int screen_counter = 0;
    for (auto pixel : screen) {
        cout << pixel;
        screen_counter ++;

        if (screen_counter == 40) {
            cout << endl;
            screen_counter = 0;
        }
    }

    return 0;
}

#include <string>
#include <sstream>
#include <iostream>
#include <stdio.h>
using namespace std;

int char_to_item_index(char currentitem) {
    if (currentitem < 97) { // Uppercase
        return currentitem -= 65; // Normalize A = 0
    } else {
        return currentitem -= (97 - 26); // Normalize a = 26
    }
}

char repeated_char(string line) {
    bool appears_in_first_compartment[52];

    int midpoint = line.length() / 2;

    for (int i = 0; i < midpoint; i ++) {
        int currentitem = char_to_item_index(line.at(i));
        appears_in_first_compartment[currentitem] = true;
    }

    for (int i = midpoint; i < line.length(); i ++) {
        int currentitem = char_to_item_index(line.at(i));
        if (appears_in_first_compartment[currentitem] == true) {
            return line.at(i);
        }
    }

    throw new exception(); // Mot the right way to do this but control flow should never reach here.
}

int main() {
    int sum = 0;
    for (string line; getline(cin, line);) {
        char repeated = repeated_char(line);


        if (repeated >= 'a') { // lowercse
            repeated -= 'a' - 1; // Normalize a = 1
        } else {
            repeated -= 'A' - 27; // Normalize A = 27
        }

        sum += repeated;
    }

    cout << sum << endl;
    return 0;
}

// Most of these aren't used. Cost of doing business.
#include <iostream>
#include <string>
#include <sstream>
#include <stdio.h>
#include <functional>
#include <set>
#include <stack>
#include <deque>
#include <queue>
#include <regex>

using namespace std;

void execute_instruction_9000(vector<deque<char>> &columns, int number_of_moves, int origin, int destination) {

    for (int i = 0; i < number_of_moves; i++) {
        char boxname = columns[origin - 1].front();
        columns[origin - 1].pop_front();
        cout << "Grabbed item " << boxname << endl;

        columns[destination - 1].push_front(boxname);
    }
}

void execute_instruction_9001(vector<deque<char>> &columns, int number_of_moves, int origin, int destination) {
    deque<char> grabbed_items;
    for (int i = 0; i < number_of_moves; i++) {
        char boxname = columns[origin - 1].front();
        columns[origin - 1].pop_front();

        cout << "Grabbed item " << boxname << endl;
        cout << columns[origin - 1].size() << endl;

        cout << "Adding to grabbed items" << endl;
        grabbed_items.push_front(boxname);

    }
    while (grabbed_items.size() > 0) {
        char box_to_place = grabbed_items.front();
        grabbed_items.pop_front();

        cout << "Placing " << box_to_place << endl;

        columns[destination - 1].push_front(box_to_place);
    }
}

int main() {
    vector<deque<char>> columns;

    vector<string> lines;
    for (string line; getline(cin, line);) {
        lines.emplace_back(line);
    }

    int number_of_columns = (lines[0].length() + 1) / 4;
    for (int i = 0; i < number_of_columns; i ++) {
        columns.push_back(deque<char>());
    }

    // Consume the first part of the input.
    int line_number = 0;
    int instructions_start = 0;
    for (string line : lines) {
        if (line[1] == '1') {
            instructions_start = line_number + 2;
            break; // We are on the final line.
        }

        for (int column = 0; column < number_of_columns; column++) {
            char boxname = line[(column * 4) + 1];
            if (boxname == ' ') {
                continue;
            }
            columns[column].emplace_back(boxname); // To get elements out, pop_front.
        }

        line_number++;
    }

    // Consume the second part of the input.
    cout << "Start instructions" << endl;
    for (int i = instructions_start; i < lines.size(); i ++) {
        string line = lines[i];
        regex digitfinder("move (\\d*) from (\\d*) to (\\d*)");
        smatch digits;

        regex_search(line, digits, digitfinder);

        int number_of_moves = stoi(digits[1]);
        int origin = stoi(digits[2]);
        int destination = stoi(digits[3]);

        execute_instruction_9001(columns, number_of_moves, origin, destination);
    }

    for (int i = 0; i < columns.size(); i ++) {
        cout << columns[i].front();
    }

    cout << endl;

    return 0;
}

#include <iostream>
#include <string>
#include <sstream>
#include <stdio.h>
#include <functional>
#include <set>
#include <regex>


using namespace std;

bool completely_within(int range1_start, int range1_end, int range2_start, int range2_end) {
    if ((range1_start >= range2_start && range1_end <= range2_end) ||
        (range2_start >= range1_start && range2_end <= range1_end)) {
        return true;
    }

    return false;
}

bool only_a_little_within(int range1_start, int range1_end, int range2_start, int range2_end) {
    if (range1_start > range2_end || range2_start > range1_end || range1_end < range2_start || range2_end < range1_start) {
        return false;
    }

    return true;
}

int main() {
    int total_overlaps = 0;

                           regex splitting_regex("(\\d+)-(\\d+),(\\d+)-(\\d+)");
    vector<int> numbers;
    for (string line; getline(cin, line);) {
        smatch match;
        regex_search(line, match, splitting_regex);

        vector<string> matches(begin(match) + 1, end(match));

        if (only_a_little_within(stoi(matches[0]), stoi(matches[1]), stoi(matches[2]), stoi(matches[3]))) {
            total_overlaps++;
        }
    }

    cout << total_overlaps << endl;
    return 0;
}

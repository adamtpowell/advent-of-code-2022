#include <string>
#include <sstream>
#include <iostream>
#include <stdio.h>
#include <functional>
#include <set>
using namespace std;

char getNextBadge() {

    string line1;
    getline(cin, line1);

    string line2;
    getline(cin, line2);

    string line3;
    getline(cin, line3);

    if (line1.empty() || line2.empty() || line3.empty()) {
        return '!';
    }

    set<char> counts1(begin(line1), end(line1));
    set<char> counts2(begin(line2), end(line2));
    set<char> counts3(begin(line3), end(line3));

    set<char> intermediate_counts;
    set_intersection(begin(counts1), end(counts1), begin(counts2), end(counts2), inserter(intermediate_counts, begin(intermediate_counts)));

    set<char> final_counts;
    set_intersection(begin(intermediate_counts), end(intermediate_counts), begin(counts3), end(counts3), inserter(final_counts, begin(final_counts)));

    for(auto count : final_counts) {
        return count;
    }

    return '!';
}


int getBadgeValue(char badge) {
    if (badge >= 'a') { // lowercse
        return badge - ('a' - 1); // Normalize a = 1
    } else {
        return badge - ('A' - 27); // Normalize A = 27
    }
}

int main() {
    int sum = 0;

    char badge = '!'; // ! is a sentinel

    while ((badge = getNextBadge()) != '!') {
        sum += getBadgeValue(badge);
        cout << badge << endl;
    }

    cout << sum << endl;

    return 0;
}

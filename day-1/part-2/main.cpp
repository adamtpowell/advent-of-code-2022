#include <iostream>
#include <string>
using namespace std;

// Incredibly hacky, but possible faster than using a real data structure?
// probaably not lol

void update_places(int count, int* firstplace, int* secondplace, int* thirdplace) {
    if (count > *firstplace) {
        int old_firstplace = *firstplace;
        *firstplace = count;
        update_places(old_firstplace, firstplace, secondplace, thirdplace);
    } else if (count > *secondplace) {
        int old_secondplace = *secondplace;
        *secondplace = count;
        update_places(old_secondplace, firstplace, secondplace, thirdplace);
    } else if (count > *thirdplace) {
        *thirdplace = count;
    }
}

int main() {
    int count = 0;
    int firstplace = 0;
    int secondplace = 0;
    int thirdplace = 0;

    for (string line; getline(cin, line);) {
        if (line.compare("") == 0) {
            update_places(count, &firstplace, &secondplace, &thirdplace);
            count = 0;
        } else {
            count += stoi(line);
        }
    }
    update_places(count, &firstplace, &secondplace, &thirdplace);

    cout << firstplace + secondplace + thirdplace << endl;
    return 0;
}

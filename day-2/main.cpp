#include <string>

#include <sstream>
#include <iostream>

#include <stdio.h>
using namespace std;

int gamepoints(int yourplay, int opponentplay) {
    bool youwin = yourplay == (opponentplay + 1) % 3;

    int youdraw = opponentplay == yourplay;

    int points_from_play = yourplay + 1;

    int points = (youwin ? 6 : 0) + (youdraw ? 3 : 0) + points_from_play;

    return points;
}

int main() {
    int total = 0;
    for (string line; getline(cin, line);) {
        int opponentplay = line.at(0) - 65; // Convert to 0 indexed int representation
        char strategy = line.at(2);

        int yourplay = -1;
        switch (strategy) {
            case 'X': // Lose
                yourplay = opponentplay - 1;
            break;
            case 'Y': // Draw
                yourplay = opponentplay;
            break;
            case 'Z': // Win
                yourplay = opponentplay + 1;
            break;
        }

        if (yourplay < 0) yourplay = 2;
        if (yourplay > 2) yourplay = 0;

        total += gamepoints(yourplay, opponentplay);
    }

    cout << total << endl;

    return 0;
}

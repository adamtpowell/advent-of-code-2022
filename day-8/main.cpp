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
#include <sstream>
using namespace std;

class tree {
    public:
        int height;
        bool visible;
        int score;
        tree(int height) : height(height), visible(false), score(0) { }
};

vector<vector<tree>> trees;

void check_visibility(int startx, int starty, int movex, int movey) {
    int x = startx;
    int y = starty;

    int max_height = -1;

    while (x >= 0 && x < trees[0].size() && y >= 0 && y < trees.size()) {
        if (trees[y][x].height > max_height) {
            max_height = trees[y][x].height;
            trees[y][x].visible = true;
        }
        x += movex;
        y += movey;
    }
}

// calculate the number of visible trees in a given direction
int calculate_score_in_direction(int startx, int starty, int movex, int movey) {
    int score = 0;
    const int height = trees[starty][startx].height;

    // The first spot to check is one in the direction.
    int x = startx + movex;
    int y = starty + movey;

    // If we've already moved off the map, we can't see anything, so the score is zero.
    while (x >= 0 && x < trees[0].size() && y >= 0 && y < trees.size()) {
        const int cur_height = trees[y][x].height;

        if (cur_height < height) {
            score += 1;
        } else {
            score += 1;
            break; // The height is too much. We stop here.
        }

        x += movex;
        y += movey;
    }

    return score;
}


int main() {
    // Put the input into the trees data structure
    for (string line; getline(cin, line);) {
        vector<tree> row;
        for (char c : line) {
            tree cur_tree(c - '0');
            row.emplace_back(cur_tree);
        }
        trees.emplace_back(row);
    }

    int grove_width = trees[0].size();
    int grove_height = trees.size();
    int x = 2;
    int y = 3;

    int max_score = -1;
    int max_score_x = -1;
    int max_score_y = -1;
    for (int x = 0; x < grove_width; x++) {
        for (int y = 0; y < grove_height; y++) {
            int score = 0;
            score += calculate_score_in_direction(x, y, 1, 0) *
                     calculate_score_in_direction(x, y, -1, 0) *
                     calculate_score_in_direction(x, y, 0, 1) *
                     calculate_score_in_direction(x, y, 0, -1);
            trees[y][x].score = score;

            if (score > max_score) {
                max_score = score;
                max_score_x = x;
                max_score_y = y;
            }
        }
    }

    for (auto row : trees) {
        for (auto tree : row) {
            if (tree.score == max_score) {
                cout << 'X';
            } else {
                int score_fraction = (int) (((float) tree.score / (float) max_score) * 10);
                if (score_fraction > 0) {
                    cout << score_fraction;
                } else {
                    cout << ".";
                }
            }
        }
        cout << endl;
    }

    cout << max_score << " first found at " << max_score_x << "," << max_score_y << endl;

    // PART 1:

    // // Look from the top of the grove
    // for (int x = 0; x < grove_width; x++) {
    //     check_visibility(x, 0, 0, 1);
    // }

    // // Look from the bottom of the grove
    // for (int x = 0; x < grove_width; x++) {
    //     check_visibility(x, grove_height - 1, 0, -1);
    // }

    // // Look from the left of the grove
    // for (int y = 0; y < grove_height; y++) {
    //     check_visibility(0, y, 1, 0);
    // }

    // // Look from the right of the grove.
    // for (int y = 0; y < grove_height; y++) {
    //     check_visibility(grove_width - 1, y, -1, 0);
    // }

    // // Count how many trees are visible
    // int visible_trees = 0;
    // for (auto row : trees) {
    //     for (auto tree : row) {
    //         if (tree.visible) {
    //             visible_trees++;
    //         }
    //     }
    // }

    // for (auto row : trees) {
    //     for (auto tree : row) {
    //         if (tree.visible) {
    //             cout << "X";
    //         } else {
    //             cout << ".";
    //         }
    //     }
    //     cout << endl;
    // }
    // cout << visible_trees << endl;

    return 0;
}

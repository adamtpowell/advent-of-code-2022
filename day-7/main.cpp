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
#include <sstream>

using namespace std;

const int needed_space = 8381165;

void print_indent(int level) {
    for (int i = 0; i < level; i++) {
        std::cout << "\t";
    }
}

class file {
    public:
        const string name;
        const int size;

        file(string name, int size) : name(name), size(size) { }
};

class tree {
    public:
        const string name;
        tree* parent;
        vector<tree*> child_directories;
        vector<file*> child_files;

        tree(string name, tree *parent) : name(name), parent(parent) { }

        ~tree() {
            for (auto child : child_directories) {
                delete child;
            }
            for (auto child : child_files) {
                delete child;
            }
        }

        // Disable both copy constructors.
        tree(const tree& other) = delete;
        tree operator=(const tree& other) = delete;

        void add_child_directory(tree* child) {
            child->parent = this; // Set the parent; This will be used to move up in the directory.
            this->child_directories.emplace_back(child);
        }

        void print_tree() {
            print_tree(0);
        }

        void print_tree(int indent) {
            print_indent(indent);
            std::cout << "Directory: " << name << ", " << get_size() << endl;
            for (auto child: child_files) {
                print_indent(indent + 1);
                std::cout << "File: " << child->name << ", " << child->size << endl;
            }
            for (auto child : child_directories) {
                child->print_tree(indent + 1);
            }
        }

        void add_child_file(string name, int size) {
            this->child_files.emplace_back(new file(name, size));
        }

        int get_size() {
            int size = 0;
            for (auto child : child_files) {
                size += child->size;
            }
            for (auto child : child_directories) {
                size += child->get_size();
            }
            return size;
        }

        void sum_sizes(int& size) {
            // This recursion repeats. This is very inefficient, but it works.
            int this_size = get_size();

            if (this_size <= 100000) {
                size += this_size;
            }

            // Recur, checking again.
            for (auto child : child_directories) {
                child->sum_sizes(size);
            }
        }

        void get_needed(tree*& current_choice, int& smallest_valid) {
            int size = get_size();
            if (size >= needed_space && size < smallest_valid) {
                smallest_valid = size;
                current_choice = this;
            }

            for (auto child : child_directories) {
                child->get_needed(current_choice, smallest_valid);
            }
        }
};

vector<string> stdin_to_vector() {
    vector<string> lines;
    for (string line; getline(cin, line);) {
        lines.emplace_back(line);
    }
    return lines;
}

enum state {
    COMMAND,
    LS,
};

string get_string_subset(string input, int start, int end) {
    string subset;
    for (int i = start; i < end; i++) {
        subset += input[i];
    }
    return subset;
}

int main() {
    const vector<string> lines = stdin_to_vector();

    state current_state = COMMAND;

    tree root = tree("/", nullptr);
    tree *cwd = &root;


    for (auto line : lines) {
        if (current_state == LS) { // We're looking at an LS file list.
            if (line[0] == '$') {
                current_state = COMMAND;
            } else if (line[0] == 'd') {
                string directory = get_string_subset(line, 4, line.length());
                cwd->add_child_directory(new tree(directory, cwd));
            } else {
                smatch matches;
                regex file_format("(\\d*) ([a-zA-Z0-9\\-\\_\\.]*)");

                regex_search(line, matches, file_format);

                cwd->add_child_file(matches[2], stoi(matches[1]));
            }
        }
        // We run command after; if the LS segment is over, then we want to run the line immediately.
        // Ideally, we'd only consume input when we wanted to, but this works for these purposes.
        if (current_state == COMMAND) {
            if (line[2] == 'l') { // LS
                current_state = LS;
            } else { // CD
                string directory = get_string_subset(line, 5, line.length());

                if (directory.compare("..") == 0) {
                    cwd = cwd->parent;
                } else {
                    string target_directory = get_string_subset(line, 5, line.length());
                    for (auto directory : cwd->child_directories) {
                        if (directory->name.compare(target_directory) == 0) {
                            cwd = directory;
                            break;
                        }
                    }
                }

                current_state = COMMAND;
            }
        }
    }

    root.print_tree();

    int size = 0;
    root.sum_sizes(size);

    tree* deletion_candidate = &root;
    int smallest_valid = 70000000; // Total hard disk size.

    root.get_needed(deletion_candidate, smallest_valid);

    cout << deletion_candidate->name << deletion_candidate->get_size() << endl;

    return 0;
}

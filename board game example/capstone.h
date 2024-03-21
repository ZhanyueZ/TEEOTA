#ifndef HELLO_CAPSTONE_H
#define HELLO_CAPSTONE_H

#include <vector>
#include <climits>
#include <iostream>
#include <chrono>

// DEBUG: ANSI esc codes
#define RED    "\x1b[91m"
#define GREEN  "\x1b[92m"
#define YELLOW "\x1b[93m"
#define BLUE   "\x1b[94m"
#define RESET  "\x1b[0m"
#define PLAY   "\x1b[;70H\x1b[K"
#define INFO   "\x1b[2;70H\x1b[K"

extern int SIZE;
extern int DIFFICULTY;
extern const int USER = 1;
extern const int COMP = -1;

std::vector<int> minimax(std::vector<std::vector<int>> &, int, int, int, int);
int heuristic(std::vector<int> &);
bool aligned(int, int, int, int, int);
bool win(int);

#endif //HELLO_CAPSTONE_H
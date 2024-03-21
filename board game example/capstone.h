#ifndef HELLO_CAPSTONE_H
#define HELLO_CAPSTONE_H

#pragma once

#include <vector>
#include <climits>
#include <iostream>
#include <chrono>
#include <random>

// DEBUG: ANSI esc codes
#define RED    "\x1b[91m"
#define GREEN  "\x1b[92m"
#define YELLOW "\x1b[93m"
#define BLUE   "\x1b[94m"
#define RESET  "\x1b[0m"

const int USER = 1;
const int COMP = -1;
extern int SIZE;
extern int DIFFICULTY;
extern int PLAYER;  // set first player
extern int moves;   // state recorder
extern double t;    // average response time by computer
extern std::vector<std::vector<int>> board;

std::pair<int, int> userGetter();
std::vector<int> minimax(std::vector<std::vector<int>> &, int, int, int, int);
int heuristic(std::vector<int> &);
bool win(int);

inline bool aligned(int i, int j, int di, int dj, int p) {
    for (int k = 0; k < 5; k++) {
        if (board[i + k * di][j + k * dj] != p) {
            return false;
        }
    }
    return true;
}

#endif //HELLO_CAPSTONE_H
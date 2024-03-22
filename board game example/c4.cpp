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
#define PLAY   "\x1b[16;H\x1b[K"
#define INFO   "\x1b[17;H\x1b[K"

const int COLUMN = 7;
const int HEIGHT = 6;
const int DIFFICULTY = 1;   // depth of minimax search: EXCEEDING 6 NOT RECOMMENDED
const int USER = 1;
const int COMP = -1;
int PLAYER = USER;          // set first player
int moves = 0;
double t = 0.0;             // average response time by computer
std::vector<std::vector<int>> board(HEIGHT, std::vector<int>(COLUMN));
std::vector<int> idx(COLUMN);

int userGetter();
std::vector<int> minimax(std::vector<std::vector<int>> &, int, int, int, int);
int heuristic(std::vector<int> &);
bool aligned(int, int, int, int, int);
bool win(int);

int userGetter() {
	int col;
	while (true) {  // till legal input
		std::cout << PLAY << "YOUR TURN: ";
        std::cin >> col;
		if (std::cin.peek() != '\n' || col < 1 || col > COLUMN) {   // warn & reenter on void inputs
            std::cin.clear();
            std::cin.ignore(INT_MAX, '\n');
            std::cout << INFO << RED << "INVALID INDEX" << RESET;
        } else if (idx[col - 1] >= HEIGHT) {
			std::cout << INFO << RED << "FULL STACK" << RESET;
		} else break;
	}
	return col - 1; // zero-based indexing
}

// REFERENCE: https://github.com/stratzilla/connect-four/blob/master/source.cpp
std::vector<int> minimax(std::vector<std::vector<int>> &b, int alpha, int beta, int depth, int p) { // NOLINT
	if (depth == 0 || depth >= (HEIGHT * COLUMN) - moves) {
        int scores = 0;
        std::vector<int> rowElements(COLUMN), colElements(HEIGHT);
        std::vector<int> set(4);
        for (int r = 0; r < HEIGHT; r++) {  // horizontal
            for (int c = 0; c < COLUMN; c++) {
                rowElements[c] = b[r][c];   // this is a distinct row alone
            }
            for (int c = 0; c < COLUMN - 3; c++) {
                for (int i = 0; i < 4; i++) {
                    set[i] = rowElements[c + i]; // for each possible set of 4 spots from that row
                }
                scores += heuristic(set);
            }
        }
        for (int c = 0; c < COLUMN; c++) {  // vertical
            for (int r = 0; r < HEIGHT; r++) {
                colElements[r] = b[r][c];
            }
            for (int r = 0; r < HEIGHT - 3; r++) {
                for (int i = 0; i < 4; i++) {
                    set[i] = colElements[r + i];
                }
                scores += heuristic(set);
            }
        }
        for (int r = 0; r < HEIGHT - 3; r++) {  // diagonal
            for (int c = 0; c < COLUMN; c++) {
                rowElements[c] = b[r][c];
            }
            for (int c = 0; c < COLUMN - 3; c++) {
                for (int i = 0; i < 4; i++) {
                    set[i] = b[r - i + 3][c + i];
                }
                scores += heuristic(set);
            }
        }
        for (int r = 0; r < HEIGHT - 3; r++) {  // anti-diagonal
            for (int c = 0; c < COLUMN; c++) {
                rowElements[c] = b[r][c];
            }
            for (int c = 0; c < COLUMN - 3; c++) {
                for (int i = 0; i < 4; i++) {
                    set[i] = b[r + i][c + i];
                }
                scores += heuristic(set);
            }
        }
		return std::vector<int>{scores, -1};
	}
    std::vector<int> optima = {p == COMP ? INT_MIN : INT_MAX, -1};  // maximizing computer while minimizing user
    if (win(-p)) {
        return optima;  // coerce poorest score to avoid the move
    }
    for (int j = 0; j < COLUMN; j++) {
        if (b[HEIGHT - 1][j] == 0) {    // only when column not full
            std::vector<std::vector<int>> replica(HEIGHT, std::vector<int>(COLUMN));
            for (int r = 0; r < HEIGHT; r++) {
                for (int c = 0; c < COLUMN; c++) {
                    replica[r][c] = b[r][c];
                }
            }
            std::vector<int> tmp = idx;
            replica[tmp[j]++][j] = p;
            int score = minimax(replica, alpha, beta, depth - 1, -p)[0];
            if (p == COMP) {
                if (score > optima[0]) {
                    optima = {score, j};
                }
                alpha = std::max(alpha, optima[0]);
            } else {
                if (score < optima[0]) {
                    optima = {score, j};
                }
                beta = std::min(beta, optima[0]);
            }
            if (alpha >= beta) {    // branch pruned
                break;
            }
        }
    }
    return optima;
}

/// OPTIMIZATION CORE
int heuristic(std::vector<int> &v) {
    int favour{0}, neutral{0}, hazard{0}, scores{0};
	for (int i : v) {
        neutral += (i == 0) ? 1 : 0;
		favour += (i == COMP) ? 1 : 0;
        hazard += (i == USER || i == COMP) ? 1 : 0;
	}
    hazard -= favour;
    if (favour == 4) {
        scores += 65537;
    } else if (favour == 3 && neutral == 1) {
        scores += 4096;
    } else if (favour == 2 && neutral == 2) {
        scores += 512;
    } else if (hazard == 2 && neutral == 2) {
        scores -= 513;
    } else if (hazard == 3 && neutral == 1) {
        scores -= 8192;
    } else if (hazard == 4) {
        scores -= 65536;
    }
    return scores;
}

bool aligned(int i, int j, int di, int dj, int p) {
    for (int k = 0; k < 4; k++) {
        if (board[i + k * di][j + k * dj] != p) {
            return false;
        }
    }
    return true;
}

bool win(int p) {
    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < COLUMN; j++) {
            if ((j + 3 < COLUMN && aligned(i, j, 0, 1, p)) ||                   // horizontal
                (i + 3 < HEIGHT && aligned(i, j, 1, 0, p)) ||                   // vertical
                (i + 3 < HEIGHT && j > 2 && aligned(i, j, 1, -1, p)) ||         // diagonal
                (i + 3 < HEIGHT && j + 3 < COLUMN && aligned(i, j, 1, 1, p))) { // anti-diagonal
                return true;
            }
        }
    }
    return false;
}

int main() {
    for (int i = 1; i <= COLUMN; i++) { // ui initialization
        std::cout << "  " << i << " ";
    }
    for (int i = 0; i <= HEIGHT; i++) {
        std::cout << std::endl;
        for (int j = 0; j <= COLUMN; j++) {
            std::cout << "+   ";
        }
        std::cout << std::endl;
    }
    int k;
	while (moves < HEIGHT * COLUMN) {   // game loop
        bool P = PLAYER == USER;
        if (P) {
            k = userGetter();
        } else {
            std::cout << PLAY << "COMP EVALUATING...";
            auto start = std::chrono::high_resolution_clock::now();
            k = minimax(board, INT_MIN, INT_MAX, DIFFICULTY, COMP)[1];
            t += std::chrono::duration<double, std::milli>(std::chrono::high_resolution_clock::now() - start).count();
        }
        board[idx[k]][k] = PLAYER;
        std::cout << INFO << "AVG EVAL " << t / int((++moves + P) / 2) << " ms\x1b[" << 13 - 2 * idx[k]++
                  << ";" << 4 * k + 3 << "H" << (P ? YELLOW "O" : BLUE "X") << RESET;
        if (win(PLAYER)) {
            std::cout << PLAY << GREEN << (P ? "WON" : "LOST") << RESET << std::endl;
            break;
        }
        PLAYER *= -1;
	}
	if (moves == HEIGHT * COLUMN) {
		std::cout << PLAY << GREEN << "DRAW" << RESET << std::endl;
	}
    system("pause");
    return 0;
}
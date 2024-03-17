#include <vector>
#include <climits>
#include <iostream>
#include <chrono>

// DEBUG: ANSI esc codes
#define RED    "\x1b[31m"
#define GREEN  "\x1b[32m"
#define YELLOW "\x1b[33m"
#define BLUE   "\x1b[34m"
#define RESET   "\x1b[0m"
#define FLUSH    "\x1b[K"

void drop(std::vector<std::vector<int>> &b, int c, int p);
int userGetter();
int compGetter();
std::vector<int> minimax(std::vector<std::vector<int>> &, int, int, int, int);
int heuristic(std::vector<int> &v);
bool aligned(int, int, int, int, int);
bool win(int);
std::vector<std::vector<int>> copyGrid(std::vector<std::vector<int>>);

int COLUMN = 7;
int HEIGHT = 6;
int DIFFICULTY = 1;     // depth of minimax search: EXCEEDING 7 NOT RECOMMENDED
const int PLAYER = -1;
const int COMPUTER = 1;
int P = PLAYER;         // set first player
int moves = 0;
double t = 0.0;         // average response time by computer
std::vector<std::vector<int>> board(HEIGHT, std::vector<int>(COLUMN));

// OPTIMIZATION POSSIBLE: unnecessary to start from bottom
void drop(std::vector<std::vector<int>> &b, int col, int p) {
	for (int i = 0; i < HEIGHT; i++) {
		if (b[i][col] == 0) {
			b[i][col] = p;
			break;
		}
	}
}

int userGetter() {
	int col;
	while (true) {  // till legal input
		std::cout << FLUSH << "YOUR TURN: ";
        std::cin >> col;
		if (std::cin.peek() != '\n' || col < 1 || col > COLUMN) {   // warn & reenter on void inputs
            std::cin.clear();
            std::cin.ignore(INT_MAX, '\n');
            std::cout << RED << "INVALID INDEX" << RESET << "\x1b[1A\r";
        } else if (board[HEIGHT - 1][col - 1] != 0) {
			std::cout << FLUSH << RED << "FULL STACK" << RESET << "\x1b[1A\r";
		} else break;
	}
	return col - 1; // zero-based indexing
}

int compGetter() {
	std::cout << "COMPUTER EVALUATING..." << std::endl;
	return minimax(board, INT_MIN, INT_MAX, DIFFICULTY, COMPUTER)[1];
}

// REFERENCE: https://github.com/stratzilla/connect-four/blob/master/source.cpp
std::vector<int> minimax(std::vector<std::vector<int>> &b, int alpha, int beta, int depth, int p) { // NOLINT
	if (depth == 0 || depth >= (HEIGHT * COLUMN) - moves) {
        int scores = 0;
        std::vector<int> rowElements(COLUMN), colElements(HEIGHT);
        std::vector<int> set(4);
        for (int r = 0; r < HEIGHT; r++) {  // horizontal
            for (int c = 0; c < COLUMN; c++) {
                rowElements[c] = b[r][c]; // this is a distinct row alone
            }
            for (int c = 0; c < COLUMN - 3; c++) {
                for (int i = 0; i < 4; i++) {
                    set[i] = rowElements[c + i]; // for each possible "set" of 4 spots from that row
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
    /// maximizing computer while minimizing player
    std::vector<int> optima = {p == COMPUTER ? INT_MIN : INT_MAX, -1};
    if (win(-p)) {
        return optima;  // coerce poorest score to avoid the move
    }
    for (int j = 0; j < COLUMN; j++) {
        if (b[HEIGHT - 1][j] == 0) {    // only when column not full
            std::vector<std::vector<int>> tmp = copyGrid(b);
            drop(tmp, j, p);
            int score = minimax(tmp, alpha, beta, depth - 1, -p)[0];
            if (p == COMPUTER) {
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

// OPTIMIZATION CORE
int heuristic(std::vector<int> &v) {
    int favour{0}, neutral{0}, hazard{0}, scores{0};
	for (int i : v) {
        neutral += (i == 0) ? 1 : 0;
		favour += (i == COMPUTER) ? 1 : 0;
        hazard += (i == PLAYER || i == COMPUTER) ? 1 : 0;
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

std::vector<std::vector<int>> copyGrid(std::vector<std::vector<int>> b) {
	std::vector<std::vector<int>> replica(HEIGHT, std::vector<int>(COLUMN));
	for (int i = 0; i < HEIGHT; i++) {
		for (int j = 0; j < COLUMN; j++) {
            replica[i][j] = b[i][j];
		}
	}
	return replica;
}

int main() {
	while (moves < HEIGHT * COLUMN) {
        if (P == COMPUTER) {
            auto start = std::chrono::high_resolution_clock::now();
            drop(board, compGetter(), P);
            t += std::chrono::duration<double, std::milli>(std::chrono::high_resolution_clock::now() - start).count();
        } else {
            drop(board, userGetter(), P);
        }
        system("cls");
        std::cout << t / int((++moves + (P == COMPUTER)) / 2) << " ms" << std::endl << std::endl;
        for (int i = 1; i <= COLUMN; i++) {
            std::cout << "  " << i << " ";
        }
        std::cout << std::endl << RESET;
        for (int i = 1; i <= COLUMN; i++) {
            std::cout << "+---";
        }
        std::cout << "+" << std::endl;
        for (int i = 0; i < HEIGHT; i++) {
            std::cout << "| ";
            for (int j = 0; j < COLUMN; j++) {
                switch (board[HEIGHT - i - 1][j]) {
                    case PLAYER: std::cout << YELLOW << "O"; break;
                    case COMPUTER: std::cout << BLUE << "X"; break;
                    default: std::cout << " ";
                }
                std::cout << RESET << " | ";
            }
            std::cout << std::endl;
            for (int j = 1; j <= COLUMN; j++) {
                std::cout << "+---";
            }
            std::cout << "+" << std::endl;
        }
        if (win(P)) {
            std::cout << FLUSH << GREEN << ((P == PLAYER) ? "WON" : "LOST") << RESET << std::endl;
            break;
        }
		P *= -1;
	}
	if (moves == HEIGHT * COLUMN) {
		std::cout << FLUSH << GREEN << "DRAW" << RESET << std::endl;
	}
    system("pause");
	return 0;
}
/* Author @Ghostook, 2024

 !LIMITATION: ONLY SERVES AS A DEBUGGER, NOT ROBUST ENOUGH!
 1. In case where your terminal does not display the entire grid, the input won't travel to the expected cell.
    To resolve this, you can either modify line 240 or use my previous version: refresh the window and convert
    board with a switch-case on every move. Note this can be visually annoying & slow down evaluation somehow.
 2. UseGetter(): given a valid col but invalid row, no longer possible to regret col.
 3. Rules to restrict the first player have not been implemented.
 */

#include "capstone.h"

#define PLAY "\x1b[;66H\x1b[K"
#define INFO "\x1b[2;66H\x1b[K"

int SIZE = 15;
int DIFFICULTY = 1; // depth of minimax search: EXCEEDING 6 MEANINGLESS
int PLAYER = USER;
int moves = 0;
double t = 0.0;
std::vector<std::vector<int>> board(SIZE, std::vector<int>(SIZE));

std::pair<int, int> userGetter() {
	int row, col;
    char c;
	while (true) {  // till legal input
		std::cout << PLAY << "PICK COLUMN: ";   // of course, you may as well enter column & row together
        std::cin >> c;
        col = static_cast<char>(std::toupper(c)) - 'A';
		if (!std::isalpha(c) || col < 0 || col >= SIZE) { // warn & reenter on void inputs
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << INFO << RED << "INVALID INDEX" << RESET;
        } else break;
	}
    while(true) {
        std::cout << PLAY << "PICK ROW: ";
        std::cin >> row;
        if (std::cin.peek() != '\n' || row < 1 || row > SIZE || board[row - 1][col] != 0) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << INFO << RED << "INVALID INDEX" << RESET;
        } else break;
    }
	return std::make_pair(row - 1, col);    // zero-based indexing
}

/**
 Function to verify if a move is near occupied cell(s)
 * @param b - the board to check
 * @param r, c - given move
 * @param proximity - how near is "near" (including diagonals)
 */
bool peripheral(const std::vector<std::vector<int>> &b, int r, int c, int proximity = 2) {
    for (int i = -proximity; i <= proximity; i++) {
        for (int j = -proximity; j <= proximity; j++) {
            int probe_r = r + i;
            int probe_c = c + j;
            if (probe_r >= 0 && probe_r < SIZE && probe_c >= 0 && probe_c < SIZE && b[probe_r][probe_c] != 0) {
                return true;
            }
        }
    }
    return false;
}

std::vector<int> minimax(std::vector<std::vector<int>> &b, int alpha, int beta, int depth, int p) { // NOLINT
	if (depth == 0 || depth >= SIZE * SIZE - moves) { // evaluate current grid in every direction
        int scores = 0;
        std::vector<int> elements(5);
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
                if (j < SIZE - 4) {                 // horizontal
                    for (int k = 0; k < 5; k++) {
                        elements[k] = b[i][j + k];
                    }
                    scores += heuristic(elements);
                }
                if (i < SIZE - 4) {                 // vertical
                    for (int k = 0; k < 5; k++) {
                        elements[k] = b[i + k][j];
                    }
                    scores += heuristic(elements);
                }
                if (i < SIZE - 4 && j < SIZE - 4) { // anti-diagonal
                    for (int k = 0; k < 5; k++) {
                        elements[k] = b[i + k][j + k];
                    }
                    scores += heuristic(elements);
                }
                if (i >= 4 && j < SIZE - 4) {       // diagonal
                    for (int k = 0; k < 5; k++) {
                        elements[k] = b[i - k][j + k];
                    }
                    scores += heuristic(elements);
                }
            }
        }
		return std::vector<int>{scores, -1, -1};    // -1 as placeholder
	}
    std::vector<int> optima = {p == COMP ? INT_MIN : INT_MAX, -1, -1};  // maximizing computer while minimizing user
    if (win(-p)) {  // immediate win/loss: extreme scenario, no need to search further
        return optima;
    }
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (b[i][j] == 0 && peripheral(b, i, j)) {  // only go down when cell unoccupied and near occupied
                std::vector<std::vector<int>> replica(SIZE, std::vector<int>(SIZE));
                for (int r = 0; r < SIZE; r++) {
                    for (int c = 0; c < SIZE; c++) {
                        replica[r][c] = b[r][c];
                    }
                }
                replica[i][j] = p;
                int score = minimax(replica, alpha, beta, depth - 1, -p)[0];
                if (p == COMP) {
                    if (score > optima[0]) {
                        optima = {score, i, j};
                    }
                    alpha = std::max(alpha, optima[0]);
                } else {
                    if (score < optima[0]) {
                        optima = {score, i, j};
                    }
                    beta = std::min(beta, optima[0]);
                }
                if (alpha >= beta) {    // branch pruned
                    break;
                }
            }
        }
    }
    return optima;
}

/// PLAY STYLE CORE
int heuristic(std::vector<int> &v) {
    int favour{0}, neutral{0}, hazard{0}, scores{0};
	for (int i : v) {
        neutral += (i == 0) ? 1 : 0;
		favour += (i == COMP) ? 1 : 0;
        hazard += (i == USER || i == COMP) ? 1 : 0;
	}
    hazard -= favour;
    if (favour == 5) {
        scores += 1024;
    } else if (favour == 4 && neutral == 1) {
        scores += 256;
    } else if (favour == 3 && neutral == 2) {
        scores += 64;
    } else if (favour == 2 && neutral == 3) {
        scores += 16;
    } else if (favour == 1 && neutral == 4) {
        scores += 4;
    } else if (hazard == 1 && neutral == 4) {
        scores -= 8;
    } else if (hazard == 2 && neutral == 3) {
        scores -= 32;
    } else if (hazard == 3 && neutral == 2) {
        scores -= 128;
    } else if (hazard == 4 && neutral == 1) {
        scores -= 512;
    } else if (hazard == 5) {
        scores -= 1025;
    }
    return scores;
}

bool win(int p) {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if ((j + 4 < SIZE && aligned(i, j, 0, 1, p)) ||                   // horizontal
                (i + 4 < SIZE && aligned(i, j, 1, 0, p)) ||                   // vertical
                (i + 4 < SIZE && j > 3 && aligned(i, j, 1, -1, p)) ||         // diagonal
                (i + 4 < SIZE && j + 4 < SIZE && aligned(i, j, 1, 1, p))) { // anti-diagonal
                return true;
            }
        }
    }
    return false;
}

int main() {
    for (int i = SIZE; i > 1; i--) {    // grid initialization
        std::string s = (i < 10) ? "0" + std::to_string(i) : std::to_string(i);
        std::cout << s << " ";
        for (int j = 1; j < SIZE; j++) {
            if (i == 8 && j == 8) {
                std::cout << GREEN;
            }
            std::cout << "+" << RESET << "---";
        }
        std::cout << "+" << std::endl;
        for (int j = 0; j < SIZE; j++) {
            std::cout << "   |";
        }
        std::cout << std::endl;
    }
    std::cout << "01 ";
    for (int i = 1; i < SIZE; i++) {
        std::cout << "+---";
    }
    std::cout << "+" << std::endl;
    for (int i = 0; i < SIZE; i++) {
        std::cout << "   " << char(i + 65);
    }
    std::cout << INFO << "ENSURE UTF-8 ENCODING TO PREVENT GARBLED OUTPUTS";
    int row, col;
	while (moves < SIZE * SIZE) {       // game loop
        bool P = PLAYER == USER;
        if (P) {
            std::tie(row, col) = userGetter();
        } else {
            if (moves == 0) {           // coerce standardized opening
                row = int(SIZE / 2);
                col = int(SIZE / 2);
            } else if (moves == 1) {    // early randomization around the first user move
                std::mt19937 gen(std::random_device{}());
                std::uniform_int_distribution<int> dis(-1, 1);
                int delta_r, delta_c;
                do {                    // ensure legal move
                    delta_r = dis(gen);
                    delta_c = dis(gen);
                } while (delta_r == 0 && delta_c == 0 ||
                         row + delta_r < 0 || row + delta_r >= SIZE ||
                         col + delta_c < 0 || col + delta_c >= SIZE);
                row += delta_r;
                col += delta_c;
            } else {
                std::cout << PLAY << "COMPUTER EVALUATING...";
                auto start = std::chrono::high_resolution_clock::now();
                std::vector<int> cell = minimax(board, INT_MIN, INT_MAX, DIFFICULTY, COMP);
                auto end = std::chrono::high_resolution_clock::now();
                t += std::chrono::duration<double, std::milli>(end - start).count();
                row = cell[1];
                col = cell[2];
            }
        }
        board[row][col] = PLAYER;
        std::cout << INFO << "AVG EVAL " << t / int((++moves + P) / 2) << " ms\x1b[" << 2 * (SIZE - row) - 1
                  << ";" << 4 * col + 3 << "H" << (moves % 2 == 1 ? "⚫" : "⚪");
        if (win(PLAYER)) {
            std::cout << PLAY << GREEN << (P ? "WON" : "LOST") << RESET << std::endl;
            break;
        }
        PLAYER *= -1;
	}
	if (moves == SIZE * SIZE) {
		std::cout << PLAY << GREEN << "DRAW" << RESET << std::endl;
	}
    system("pause");
    return 0;
}
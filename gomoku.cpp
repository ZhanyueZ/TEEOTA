#include "capstone.h"

int COLUMN = 15;
int HEIGHT = 15;
int DIFFICULTY = 1;     // depth of minimax search: EXCEEDING 6 NOT RECOMMENDED
int PLAYER = USER;      // set first player
int moves = 0;
double t = 0.0;         // average response time by computer
std::vector<std::vector<int>> board(HEIGHT, std::vector<int>(COLUMN));

std::pair<int, int> userGetter() {
	int row, col;
    char c;
	while (true) {  // till legal input
		std::cout << PLAY << "PICK COLUMN: ";
        std::cin >> c;
        col = static_cast<char>(std::toupper(c)) - 'A';
		if (!std::isalpha(c) || col < 0 || col >= COLUMN) {   // warn & reenter on void inputs
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << INFO << RED << "INVALID INDEX" << RESET;
        } else break;
	}
    while(true) {
        std::cout << PLAY << "PICK ROW: ";
        std::cin >> row;
        if (std::cin.peek() != '\n' || row < 1 || row > HEIGHT || board[row - 1][col] != 0) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << INFO << RED << "INVALID INDEX" << RESET;
        } else break;
    }
	return std::make_pair(row - 1, col);    // zero-based indexing
}

std::vector<int> minimax(std::vector<std::vector<int>> &b, int alpha, int beta, int depth, int p) { // NOLINT
	if (depth == 0 || depth >= (HEIGHT * COLUMN) - moves) {
        int scores = 0;
        std::vector<int> rowElements(COLUMN), colElements(HEIGHT);
        std::vector<int> set(5);
        for (int r = 0; r < HEIGHT; r++) {  // horizontal
            for (int c = 0; c < COLUMN; c++) {
                rowElements[c] = b[r][c];   // this is a distinct row alone
            }
            for (int c = 0; c < COLUMN - 4; c++) {
                for (int i = 0; i < 5; i++) {
                    set[i] = rowElements[c + i]; // for each possible set of 4 spots from that row
                }
                scores += heuristic(set);
            }
        }
        for (int c = 0; c < COLUMN; c++) {  // vertical
            for (int r = 0; r < HEIGHT; r++) {
                colElements[r] = b[r][c];
            }
            for (int r = 0; r < HEIGHT - 4; r++) {
                for (int i = 0; i < 5; i++) {
                    set[i] = colElements[r + i];
                }
                scores += heuristic(set);
            }
        }
        for (int r = 0; r < HEIGHT - 4; r++) {  // diagonal
            for (int c = 0; c < COLUMN; c++) {
                rowElements[c] = b[r][c];
            }
            for (int c = 0; c < COLUMN - 4; c++) {
                for (int i = 0; i < 5; i++) {
                    set[i] = b[r - i + 4][c + i];
                }
                scores += heuristic(set);
            }
        }
        for (int r = 0; r < HEIGHT - 4; r++) {  // anti-diagonal
            for (int c = 0; c < COLUMN; c++) {
                rowElements[c] = b[r][c];
            }
            for (int c = 0; c < COLUMN - 4; c++) {
                for (int i = 0; i < 5; i++) {
                    set[i] = b[r + i][c + i];
                }
                scores += heuristic(set);
            }
        }
		return std::vector<int>{scores, -1, -1};
	}
    std::vector<int> optima = {p == COMP ? INT_MIN : INT_MAX, -1, -1};  // maximizing computer while minimizing user
    if (win(-p)) {
        return optima;  // coerce poorest score to avoid the move
    }

    /// POSSIBLE OPTIMIZATION: ONLY CHECK PERIPHERAL <= 3

    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < COLUMN; j++) {
            if (b[i][j] == 0) {    // only when column not full
                std::vector<std::vector<int>> replica(HEIGHT, std::vector<int>(COLUMN));
                for (int r = 0; r < HEIGHT; r++) {
                    for (int c = 0; c < COLUMN; c++) {
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

int heuristic(std::vector<int> &v) {
    int favour{0}, neutral{0}, hazard{0}, scores{0};
	for (int i : v) {
        neutral += (i == 0) ? 1 : 0;
		favour += (i == COMP) ? 1 : 0;
        hazard += (i == USER || i == COMP) ? 1 : 0;
	}
    hazard -= favour;
    if (favour == 5) {
        scores += 65536;
    } else if (favour == 4 && neutral == 1) {
        scores += 16384;
    } else if (favour == 3 && neutral == 2) {
        scores += 4096;
    } else if (favour == 2 && neutral == 3) {
        scores += 1024;
    } else if (favour == 1 && neutral == 4) {
        scores += 256;
    } else if (hazard == 1 && neutral == 4) {
        scores -= 512;
    } else if (hazard == 2 && neutral == 3) {
        scores -= 2048;
    } else if (hazard == 3 && neutral == 2) {
        scores -= 8192;
    } else if (hazard == 4 && neutral == 1) {
        scores -= 32768;
    } else if (hazard == 5) {
        scores -= 65537;
    }
    return scores;
}

bool aligned(int i, int j, int di, int dj, int p) {
    for (int k = 0; k < 5; k++) {
        if (board[i + k * di][j + k * dj] != p) {
            return false;
        }
    }
    return true;
}

bool win(int p) {
    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < COLUMN; j++) {
            if ((j + 4 < COLUMN && aligned(i, j, 0, 1, p)) ||                   // horizontal
                (i + 4 < HEIGHT && aligned(i, j, 1, 0, p)) ||                   // vertical
                (i + 4 < HEIGHT && j > 3 && aligned(i, j, 1, -1, p)) ||         // diagonal
                (i + 4 < HEIGHT && j + 4 < COLUMN && aligned(i, j, 1, 1, p))) { // anti-diagonal
                return true;
            }
        }
    }
    return false;
}

int main() {
    for (int i = HEIGHT; i > 0; i--) { // ui initialization
        std::stringstream ss;
        ss << std::setw(2) << std::setfill('0') << i;
        std::string s = ss.str();
        std::cout << s << "   ";
        for (int j = 0; j < COLUMN; j++) {
            std::cout << "+   ";
        }
        std::cout << std::endl << std::endl;
    }
    std::cout << "     ";
    for (int i = 0; i < COLUMN; i++) {
        std::cout << char(i + 65) << "   ";
    }
    int row, col;
	while (moves < HEIGHT * COLUMN) {   // game loop
        bool P = PLAYER == USER;
        if (P) {
            std::tie(row, col) = userGetter();
        } else {
            std::cout << PLAY << "COMPUTER EVALUATING...";
            auto start = std::chrono::high_resolution_clock::now();
            std::vector<int> k = minimax(board, INT_MIN, INT_MAX, DIFFICULTY, COMP);
            t += std::chrono::duration<double, std::milli>(std::chrono::high_resolution_clock::now() - start).count();
            row = k[1];
            col = k[2];
        }
        board[row][col] = PLAYER;
        std::cout << INFO << "AVG EVAL " << t / int((++moves + P) / 2) << " ms\x1b[" << 2 * (HEIGHT - row) - 3
                  << ";" << 4 * col + 6 << "H" << (P ? YELLOW "O" : BLUE "X") << RESET;
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
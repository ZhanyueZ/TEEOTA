#include <gui/screen1_screen/Screen2View.hpp>
#include <touchgfx/Color.hpp>

int SIZE = 15;
int DIFFICULTY = 3; // depth of minimax search: EXCEEDING 6 NOT RECOMMENDED
int PLAYER = USER;
int moves = 0;
std::vector<std::vector<int>> board(SIZE, std::vector<int>(SIZE));

Screen2View::Screen2View():
    circleClickedCallBack(this, &Screen2View::circleClickHandler) {
}

void Screen2View::setupScreen() {
//    Screen1ViewBase::setupScreen();
//    for (int i = 0; i < SIZE * SIZE; i++) {
//        circles[i].setClickAction(circleClickedCallBack);
//    }
}

void Screen2View::tearDownScreen() {
    Screen1ViewBase::tearDownScreen();
}

bool Screen2View::peripheral(const std::vector<std::vector<int>> &b, int r, int c, int proximity = 2) {
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

std::vector<int> Screen2View::minimax(std::vector<std::vector<int>> &b, int alpha, int beta, int depth, int p) {
	if (depth == 0 || depth >= (SIZE * SIZE) - moves) { // evaluate current grid in every direction
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
    if (win(-p)) {
        return optima;  // coerce poorest score to avoid the move
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

int Screen2View::heuristic(std::vector<int> &v) {
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

bool Screen2View::win(int p) {
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

void Screen2View::circleClickHandler(const Circle &c, const ClickEvent &evt) {
//	if (turn % 2 == 0) {    // NOTE: possibly eliminating variable turn
//        for (int i = 0; i < SIZE; i++) {
//            for (int j = 0; j < SIZE; j++) {
//                if (&c == circles[i][j]) {
//                    if (releaseOrPress == 0) {
//                        if (board[j][i] != 0) {
//                            return;
//                        }
//                        if (win(USER)) {
//                            Win.setAlpha(255);
//                            Win.invalidate();
//                            return;
//                        }
//                        if (win(COMP)) {
//                            Lose.setAlpha(true);
//                            Lose.invalidate();
//                            return;
//                        }
//                        ColB[i][j] -> setVisible(true);
//                        ColB[i][j] -> invalidate();
//                        board[j][i] = 1;
//                        releaseOrPress++;
//                    } else {
//                        releaseOrPress = 0;
//                        if (win(USER)) {
//                            Win.setAlpha(255);
//                            Win.invalidate();
//                            return;
//                        }
//                        std::vector<int> k = minimax(board, DIFFICULTY, INT_MIN, INT_MAX, COMP);
//                        int col = k[1];
//                        int row = k[2];
//                        if (board[row][col] != 0) {
//                            return;
//                        }
//                        ColW[col][row] -> setVisible(true);
//                        ColW[col][row] -> invalidate();
//                        board[row][col] = -1;
//                        if (win(COMP)) {
//                            Lose.setAlpha(255);
//                            Lose.invalidate();
//                            return;
//                        }
//                    }
//                }
//            }
//        }
//	}
}
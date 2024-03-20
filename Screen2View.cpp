#include <gui/screen1_screen/Screen2View.hpp>
#include <touchgfx/Color.hpp>

Screen2View::Screen1View():
    circleClickedCallBack(this,&Screen1View::circleClickHandler) {
}

void Screen1View::setupScreen() {
    Screen1ViewBase::setupScreen();
    for (int i = 0; i < HEIGHT * COLUMN; i++) {
        circle[i].setClickAction(circleClickedCallBack);
    }
}

void Screen2View::tearDownScreen() {
    Screen1ViewBase::tearDownScreen();
}

std::vector<int> Screen2View::minimax(std::vector<std::vector<int>> &b, int alpha, int beta, int depth, int p) {
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

// OPTIMIZATION POSSIBLE
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

bool Screen2View::aligned(int i, int j, int di, int dj, int p) {
    for (int k = 0; k < 5; k++) {
        if (board[i + k * di][j + k * dj] != p) {
            return false;
        }
    }
    return true;
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
	if (turn % 2 == 0) {
        for (int i = 0; i < COLUMN; i++) {
            for (int j = 0; j < HEIGHT; j++) {
                if (&c == circles[i]) {
                    if (releaseOrPress == 0) {
                        if (board[j][i] != 0) {
                            return;
                        }
                        if (win(USER)) {
                            Win.setAlpha(255);
                            Win.invalidate();
                            return;
                        }
                        if (win(COMP)) {
                            Lose.setAlpha(true);
                            Lose.invalidate();
                            return;
                        }
                        ColB[i][j]->setVisible(true);
                        ColB[i][j]->invalidate();
                        board[j][i] = 1;
                        releaseOrPress++;
                    } else {
                        releaseOrPress = 0;
                        if (win(USER)) {
                            Win.setAlpha(255);
                            Win.invalidate();
                            return;
                        }
                        std::vector<int> k = minimax(board, DIFFICULTY, INT_MIN, INT_MAX, COMPUTER);
                        int col = k[1];
                        int row = k[2];
                        if (board[row][col] != 0) {
                            return;
                        }
                        ColW[col][row]->setVisible(true);
                        ColW[col][row]->invalidate();
                        board[row][col] = -1;
                        if (win(COMP)) {
                            Lose.setAlpha(255);
                            Lose.invalidate();
                            return;
                        }
                    }
                }
            }
        }
	}
}
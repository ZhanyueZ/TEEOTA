#include <gui/screen1_screen/Screen1View.hpp>
#include <touchgfx/Color.hpp>
#include <vector>
#include <climits>

#define min(a,b) (((a) < (b)) ? (a) : (b))
#define max(a,b) (((a) > (b)) ? (a) : (b))
#define HEIGHT 6
#define COLUMN 7
#define COMPUTER 2
#define PLAYER 1
#define DIFFICULTY 1
void drop(std::vector<std::vector<int>> &, int, int);
std::vector<std::vector<int> > copyGrid(std::vector<std::vector<int>>);
bool win(int);
int heuristic(std::vector<int>, int);
int evalGrid(std::vector<std::vector<int>>, int);
std::vector<int> minimax(std::vector<std::vector<int>> &, unsigned int, int, int, int);

Screen1View::Screen1View() :
    circleClickedCallBack(this,&Screen1View::circleClickHandler) {
}

void Screen1View::setupScreen()
{
    Screen1ViewBase::setupScreen();
    circle1.setClickAction(circleClickedCallBack);
    circle2.setClickAction(circleClickedCallBack);
    circle3.setClickAction(circleClickedCallBack);
    circle4.setClickAction(circleClickedCallBack);
    circle5.setClickAction(circleClickedCallBack);
    circle6.setClickAction(circleClickedCallBack);
    circle7.setClickAction(circleClickedCallBack);
}

void Screen1View::tearDownScreen()
{
    Screen1ViewBase::tearDownScreen();
}

int Screen1View::machine(std::vector<std::vector<int>>&board) {
	return minimax(board, DIFFICULTY, 0 - INT_MAX, INT_MAX, COMPUTER)[1];
}

void Screen1View::drop(std::vector<std::vector<int>> &b, int c, int p) {
	for (int r = 0; r < HEIGHT; r++) {
		if (b[r][c] == 0) {
			b[r][c] = p;
			break;
		}
	}
}

std::vector<std::vector<int>> Screen1View::copyGrid(std::vector<std::vector<int>> b) {
	std::vector<std::vector<int>> tmp(HEIGHT, std::vector<int>(COLUMN));
	for (int r = 0; r < HEIGHT; r++) {
		for (int c = 0; c < COLUMN; c++) {
			tmp[r][c] = b[r][c];
		}
	}
	return tmp;
}

// OPTIMIZATION POSSIBLE: use tail recursion and integrate evalGrid()
std::vector<int> Screen1View::minimax(std::vector<std::vector<int> > &b, int depth, int alpha, int beta, int p) {
	if (depth == 0) {
		return std::vector<int>{evalGrid(b, COMPUTER), -1};
	}
	if (p == COMPUTER) {
		std::vector<int> optimal = {INT_MIN, -1}; // since maximizing, we want lowest possible value
		if (win(PLAYER)) {
			return optimal; // force it to say it's worst possible score, so it knows to avoid move
		} // otherwise, business as usual
		for (int c = 0; c < COLUMN; c++) { // for each possible move
			if (b[HEIGHT - 1][c] == 0) { // only when column not full
				std::vector<std::vector<int> > tmp = copyGrid(b);
                drop(tmp, c, p);
				int score = minimax(tmp, depth - 1, alpha, beta, PLAYER)[0]; // find move based on that new board state
				if (score > optimal[0]) { // if better score, replace it, and consider that best move (for now)
					optimal = {score, (int)c};
				}
                alpha = max(alpha, optimal[0]);
				if (alpha >= beta) {
                    break;
                }
			}
		}
		return optimal;
	} else {
		std::vector<int> optimal = {INT_MAX, -1}; // PLAYER minimized, we want moves that diminish such score
		if (win(COMPUTER)) {
			return optimal;
		}
		for (int c = 0; c < COLUMN; c++) {
			if (b[HEIGHT - 1][c] == 0) {
				std::vector<std::vector<int> > tmp = copyGrid(b);
                drop(tmp, c, p);
				int score = minimax(tmp, depth - 1, alpha, beta, COMPUTER)[0];
				if (score < optimal[0]) {
					optimal = {score, (int)c};
				}
                beta = min(beta, optimal[0]);
				if (alpha >= beta) {
                    break;
                }
			}
		}
		return optimal;
	}
}

// OPTIMIZATION POSSIBLE
int Screen1View::heuristic(std::vector<int> v, int p) {
    int favour{0}, neutral{0}, hazard{0}, scores{0};
	for (int i : v) {   // just enumerate how many of each
		favour += (i == p) ? 1 : 0;
        neutral += (i == 0) ? 1 : 0;
        hazard += (i == PLAYER || i == COMPUTER) ? 1 : 0;
	}
    hazard -= favour;    // hazard was calculated as (hazard + favour), so remove favour
    if (favour == 4) {
        scores += 65536;
    } else if (favour == 3 && neutral == 1) {
        scores += 4096;
    } else if (favour == 2 && neutral == 2) {
        scores += 512;
    } else if (hazard == 2 && neutral == 2) {
        scores -= 513;
    } else if (hazard == 3 && neutral == 1) {
        scores -= 16385;
    } else if (hazard == 4) {
        scores -= 16384;
    }
    return scores;
}

// reference: https://github.com/stratzilla/connect-four/blob/master/source.cpp
int Screen1View::evalGrid(std::vector<std::vector<int>> b, int p) {
	int scores = 0;
	std::vector<int> rs(COLUMN);
	std::vector<int> cs(HEIGHT);
	std::vector<int> set(4);
	for (int r = 0; r < HEIGHT; r++) {  // horizontal
		for (int c = 0; c < COLUMN; c++) {
			rs[c] = b[r][c]; // this is a distinct row alone
		}
		for (int c = 0; c < COLUMN - 3; c++) {
			for (int i = 0; i < 4; i++) {
				set[i] = rs[c + i]; // for each possible "set" of 4 spots from that row
			}
			scores += heuristic(set, p);
		}
	}
	for (int c = 0; c < COLUMN; c++) {  // vertical
		for (int r = 0; r < HEIGHT; r++) {
			cs[r] = b[r][c];
		}
		for (int r = 0; r < HEIGHT - 3; r++) {
			for (int i = 0; i < 4; i++) {
				set[i] = cs[r + i];
			}
			scores += heuristic(set, p);
		}
	}
	for (int r = 0; r < HEIGHT - 3; r++) {  // diagonals
		for (int c = 0; c < COLUMN; c++) {
			rs[c] = b[r][c];
		}
		for (int c = 0; c < COLUMN - 3; c++) {
			for (int i = 0; i < 4; i++) {
				set[i] = b[r + i][c + i];
			}
			scores += heuristic(set, p);
		}
	}
	for (int r = 0; r < HEIGHT - 3; r++) {
		for (int c = 0; c < COLUMN; c++) {
			rs[c] = b[r][c];
		}
		for (int c = 0; c < COLUMN - 3; c++) {
			for (int i = 0; i < 4; i++) {
				set[i] = b[r + 3 - i][c + i];
			}
			scores += heuristic(set, p);
		}
	}
	return scores;
}

bool Screen1View::aligned(int player, int i, int j, int di, int dj) {
    for (int k = 0; k < 4; k++) {
        if (board[i + k * di][j + k * dj] != player)
            return false;
    }
    return true;
}

bool Screen1View::win(int p) {
    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < COLUMN; j++) {
            if ((j + 3 < COLUMN && aligned(p, i, j, 0, 1)) ||                   // horizontal
                (i + 3 < HEIGHT && aligned(p, i, j, 1, 0)) ||                   // vertical
                (i + 3 < HEIGHT && j + 3 < COLUMN && aligned(p, i, j, 1, 1)) || // diagonal
                (i + 3 < HEIGHT && j > 2 && aligned(p, i, j, 1, -1))) {         // anti-diagonal
                return true;
            }
        }
    }
    return false;
}

void Screen1View::circleClickHandler(const Circle &c, const ClickEvent &evt) {
	if (turn % 2 == 0) {
        for (int i = 0; i < COLUMN; i++) {
            if (&c == circles[i]) {
                if(releaseOrPress == 0) {
                    if(columnIndex[i] == HEIGHT) {
                        return;
                    }
                    if (win(1)) {
                    	Win.setAlpha(255);
                    	Win.invalidate();
                    	return;
                    }
                    if (win(2)) {
                     Lose.setAlpha(true);
                     Lose.invalidate();
                     return;
                    }
                    ColR[i][columnIndex[i]]->setVisible(true);
                    ColR[i][columnIndex[i]]->invalidate();
                    board[columnIndex[i]][i] = 1;
                    columnIndex[i]++;
                    releaseOrPress++;
                } else {
                    releaseOrPress = 0;

                    if (win(1)) {
                        Win.setAlpha(255);
                        Win.invalidate();
                        return;
                    }
                    int col = machine(board);
                    if(columnIndex[col] == HEIGHT) {
                         return;
                    }
                    ColB[col][columnIndex[col]]->setVisible(true);
                    ColB[col][columnIndex[col]]->invalidate();
                    board[columnIndex[col]][col] = 2;
                    if (win(2)) {
                        Lose.setAlpha(255);
                        Lose.invalidate();
                        return;
                    }
                    columnIndex[col]++;
                }
            }
        }
	}
}

#include <gui/screen2_screen/Screen2View.hpp>
#include <cmath>
#include <touchgfx/Color.hpp>
#include <climits>

#define  SIZE 11
#define  PLAYER 1
#define  DIFFICULTY 1
#define  moves 0
#define COMP -1
#define USER 1
#define HEIGHT 11
#define COLUMN 11
uint16_t Bitmap_cache[57600]; // 240*240

Screen2View::Screen2View():
		boxClickedCallback(this,&Screen2View::boxClickHandler) {}

void Screen2View::setupScreen()
{
    Screen2ViewBase::setupScreen();
    box1.setClickAction(boxClickedCallback);
    Bitmap::setCache(Bitmap_cache,sizeof(Bitmap_cache),1);
    Bitmap::cacheAll();
    bm = Bitmap::dynamicBitmapCreate(240,240,Bitmap::RGB888);
    snapshot_image.setBitmap(bm);
    snapshot_image.setVisible(true);
    snap.setPosition(box1);
}

void Screen2View::tearDownScreen()
{
    Screen2ViewBase::tearDownScreen();
    Bitmap::removeCache();
}

void Screen2View::boxClickHandler(const Box& b,const ClickEvent& e){
   if(firstPress){
	lastX = e.getX();
	lastY = e.getY();
	lastX = correctX(lastX);
	lastY = correctY(lastY);
	if(win(COMP)) {
		circle1.invalidate();
		circle2.invalidate();
		return;
	}
    int value = board[11-(lastY/20)][(lastX)/20-1];
	if(value == 1 || value == -1) {
		   snapshot_image.invalidate();
		   circle1.invalidate();             // why we need these two lines?????????
		   circle2.invalidate();
		   firstPress = false;
           return;
	 }
	board[11-(lastY/20)][(lastX)/20-1] = 1;
	circle1.setPosition(lastX-10, lastY-10, 20, 20);
	circle1.setVisible(true);
	circle1.invalidate();
	if(win(USER)){
//		WonText.setAlpha(255);
//		WonText.invalidate();
		snapshot_image.invalidate();
		circle1.invalidate();             // why we need these two lines?????????
	    circle2.invalidate();
		return;
	}
    std::vector<int> machine = minimax(board,INT_MIN,INT_MAX,DIFFICULTY,-1);
//	std::vector<int> machine{0, 10};
    int machineX = machine[2]*20 + 10;
    int machineY = 210 - machine[1]*20;
    board[machine[1]][machine[2]] = -1;
    circle2.setPosition(machineX,machineY,20,20);
    circle2.setVisible(true);
    circle2.invalidate();

    snap.makeSnapshot(bm);
    snapshot_image.invalidate();
    firstPress = false;
   } else {
	   firstPress = true;
	   snapshot_image.invalidate();
	   circle1.invalidate();             // why we need these two lines?????????
	   circle2.invalidate();
   }
}


int Screen2View::correctX(int x) {
	int gap = 1000;
	int resultX = -1;
    for(int i=20;i<240;i=i+20){
    	if(abs(x-i) < gap) {
    		gap = abs(x-i);
    		resultX = i;
    	}
    }
    return resultX;
}

int Screen2View::correctY(int y) {
	int gap = 1000;
		int resultY = -1;
	    for(int i=20;i<240;i=i+20){
	    	if(abs(y-i) < gap) {
	    		gap = abs(y-i);
	    		resultY = i;
	    	}
	    }
	    return resultY;
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
bool Screen2View::aligned(int i, int j, int di, int dj, int p) {
    for (int k = 0; k < 5; k++) {
        if (board[i + k * di][j + k * dj] != p) {
            return false;
        }
    }
    return true;
}



#ifndef SCREEN2VIEW_HPP
#define SCREEN2VIEW_HPP

#pragma once

#include <gui_generated/screen1_screen/Screen1ViewBase.hpp>
#include <gui_generated/beginner_screen_screen/Beginner_ScreenViewBase.hpp>
#include <gui/screen1_screen/Screen1Presenter.hpp>
#include <vector>
#include <climits>
#include <random>
#include <gui/common/FrontendApplication.hpp>

class Screen2View : public Screen1ViewBase {
public:
    Screen2View();
    //declaring callback handler for Circle
    void circleClickHandler(const Circle &c, const ClickEvent& e);
    virtual ~Screen2View() {}
    virtual void setupScreen();
    virtual void tearDownScreen();
    
    const int USER = 1;
    const int COMP = -1;
    extern int SIZE;
    extern int DIFFICULTY;
    extern int PLAYER;  // set first player
    extern int moves;   // state recorder
    extern std::vector<std::vector<int>> board;
    extern int turn = 0;
    extern int releaseOrPress = 0;

//    touchgfx::Circle* ColB[HEIGHT][COLUMN] = {{&w_c00,&w_c01,&w_c02,&w_c03,&w_c04,&w_c05, &w_c06},
//                                              {&w_c10,&w_c11,&w_c12,&w_c13,&w_c14,&w_c15, &w_c16},
//                                              {&w_c20,&w_c21,&w_c22,&w_c23,&w_c24,&w_c25, &w_c26},
//                                              {&w_c30,&w_c31,&w_c32,&w_c33,&w_c34,&w_c35, &w_c36},
//                                              {&w_c40,&w_c41,&w_c42,&w_c43,&w_c44,&w_c45, &w_c46},
//                                              {&w_c50,&w_c51,&w_c52,&w_c53,&w_c54,&w_c55, &w_c56},
//                                              {&w_c60,&w_c61,&w_c62,&w_c63,&w_c64,&w_c65, &w_c66}};
//    touchgfx::Circle* ColW[HEIGHT][COLUMN] = {{&w_c00,&w_c01,&w_c02,&w_c03,&w_c04,&w_c05, &w_c06},
//                                              {&w_c10,&w_c11,&w_c12,&w_c13,&w_c14,&w_c15, &w_c16},
//                                              {&w_c20,&w_c21,&w_c22,&w_c23,&w_c24,&w_c25, &w_c26},
//                                              {&w_c30,&w_c31,&w_c32,&w_c33,&w_c34,&w_c35, &w_c36},
//                                              {&w_c40,&w_c41,&w_c42,&w_c43,&w_c44,&w_c45, &w_c46},
//                                              {&w_c50,&w_c51,&w_c52,&w_c53,&w_c54,&w_c55, &w_c56},
//                                              {&w_c60,&w_c61,&w_c62,&w_c63,&w_c64,&w_c65, &w_c66}};
//    touchgfx::Circle* circles[HEIGHT][COLUMN] =
//            {{&circle1, &circle2, &circle3, &circle4, &circle5, &circle6, &circle7},
//             {&circle8, &circle9, &circle10, &circle11, &circle12, &circle13, &circle14},
//             {&circle15, &circle16, &circle17, &circle18, &circle19, &circle20, &circle21},
//             {&circle22, &circle23, &circle24, &circle25, &circle26, &circle27, &circle28},
//             {&circle29, &circle30, &circle31, &circle32, &circle33, &circle34, &circle35},
//             {&circle36, &circle37, &circle38, &circle39, &circle40, &circle41, &circle42},
//             {&circle43, &circle44, &circle45, &circle46, &circle47, &circle48, &circle49}}

    bool peripheral(const std::vector<std::vector<int>> &, int, int, int);
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
    
protected:
    Callback<Screen2View, const Circle&, const ClickEvent&> circleClickedCallBack;
};

#endif // SCREEN2VIEW_HPP
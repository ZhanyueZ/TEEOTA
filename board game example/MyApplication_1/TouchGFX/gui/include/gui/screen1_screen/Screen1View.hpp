#ifndef SCREEN1VIEW_HPP
#define SCREEN1VIEW_HPP
#include <gui_generated/screen1_screen/Screen1ViewBase.hpp>
#include <gui_generated/beginner_screen_screen/Beginner_ScreenViewBase.hpp>
#include <gui/screen1_screen/Screen1Presenter.hpp>
#include <vector>
#include <climits>
#include <gui/common/FrontendApplication.hpp>

class Screen1View : public Screen1ViewBase
{
public:
    Screen1View();
    //Declaring callback handler for Circle
    void circleClickHandler(const Circle &c, const ClickEvent& e);
    virtual ~Screen1View() {}
    virtual void setupScreen();
    virtual void tearDownScreen();
    int machine(std::vector<std::vector<int>> &board);
    int COLUMN = 7;
    int HEIGHT = 6;
    touchgfx::Circle* ColR[7][6] = {{&r_c00,&r_c01,&r_c02,&r_c03,&r_c04,&r_c05},
                                   {&r_c10,&r_c11,&r_c12,&r_c13,&r_c14,&r_c15},
                                   {&r_c20,&r_c21,&r_c22,&r_c23,&r_c24,&r_c25},
                                   {&r_c30,&r_c31,&r_c32,&r_c33,&r_c34,&r_c35},
                                   {&r_c40,&r_c41,&r_c42,&r_c43,&r_c44,&r_c45},
                                   {&r_c50,&r_c51,&r_c52,&r_c53,&r_c54,&r_c55},
                                   {&r_c60,&r_c61,&r_c62,&r_c63,&r_c64,&r_c65}};
    touchgfx::Circle* ColB[7][6] = {{&b_c00,&b_c01,&b_c02,&b_c03,&b_c04,&b_c05},
                                   {&b_c10,&b_c11,&b_c12,&b_c13,&b_c14,&b_c15},
                                   {&b_c20,&b_c21,&b_c22,&b_c23,&b_c24,&b_c25},
                                   {&b_c30,&b_c31,&b_c32,&b_c33,&b_c34,&b_c35},
                                   {&b_c40,&b_c41,&b_c42,&b_c43,&b_c44,&b_c45},
                                   {&b_c50,&b_c51,&b_c52,&b_c53,&b_c54,&b_c55},
                                   {&b_c60,&b_c61,&b_c62,&b_c63,&b_c64,&b_c65}};

    touchgfx::Circle* circles[7] = {&circle1,&circle2,&circle3,&circle4,&circle5,&circle6,&circle7};

    int turn = 0;
    int releaseOrPress = 0;
    int columnIndex[7] = {0};
    std::vector<std::vector<int>> board {6, std::vector<int>(7)};
    // method for machine intelligence
    void drop(std::vector<std::vector<int> >&, int, int);
    std::vector<std::vector<int> > copyGrid(std::vector<std::vector<int>>);
    bool win(int);
    int heuristic(std::vector<int>, int);
    int evalGrid(std::vector<std::vector<int>>, int);
    std::vector<int> minimax(std::vector<std::vector<int>> &, int, int, int, int);
    bool aligned(int player, int i, int j, int di, int dj);

    unsigned int DIFFICULTY = 1;    // depth of minimax search
    unsigned int moves = 0;
    int PLAYER = 1;
    int COMPUTER = 2;
    int P = PLAYER;                 // set first player

protected:
    Callback<Screen1View, const Circle&, const ClickEvent&> circleClickedCallBack;
};

#endif // SCREEN1VIEW_HPP

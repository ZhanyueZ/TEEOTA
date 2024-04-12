#ifndef SCREEN2VIEW_HPP
#define SCREEN2VIEW_HPP

#include <gui_generated/screen2_screen/Screen2ViewBase.hpp>
#include <gui/screen2_screen/Screen2Presenter.hpp>
#include <touchgfx/widgets/SnapshotWidget.hpp>
#include <vector>

class Screen2View : public Screen2ViewBase
{
public:
    Screen2View();
    virtual ~Screen2View() {}
    virtual void setupScreen();
    virtual void tearDownScreen();

    void boxClickHandler(const Box& b, const ClickEvent& e);
    int  correctX(int x);
    int  correctY(int y);
protected:
    SnapshotWidget snap;
    Bitmap bm;
	int16_t lastX, lastY,pressX,pressY;
	std::vector<std::vector<int>> board {11, std::vector<int>(11)};
	Callback<Screen2View, const Box&,const ClickEvent&> boxClickedCallback;
	bool peripheral(const std::vector<std::vector<int>> &, int, int, int);
	std::vector<int> minimax(std::vector<std::vector<int>> &, int, int, int, int);
	int heuristic(std::vector<int> &);
	bool win(int);
	bool aligned(int i, int j, int di, int dj, int p);
	bool firstPress = true;
};

#endif // SCREEN2VIEW_HPP

#ifndef BEGINNER_SCREENVIEW_HPP
#define BEGINNER_SCREENVIEW_HPP

#include <gui_generated/beginner_screen_screen/Beginner_ScreenViewBase.hpp>
#include <gui/beginner_screen_screen/Beginner_ScreenPresenter.hpp>

class Beginner_ScreenView : public Beginner_ScreenViewBase
{
public:
    Beginner_ScreenView();
    virtual ~Beginner_ScreenView() {}
    virtual void setupScreen();
    virtual void tearDownScreen();
protected:
};

#endif // BEGINNER_SCREENVIEW_HPP

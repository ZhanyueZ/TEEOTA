#ifndef BEGINNER_SCREENPRESENTER_HPP
#define BEGINNER_SCREENPRESENTER_HPP

#include <gui/model/ModelListener.hpp>
#include <mvp/Presenter.hpp>

using namespace touchgfx;

class Beginner_ScreenView;

class Beginner_ScreenPresenter : public touchgfx::Presenter, public ModelListener
{
public:
    Beginner_ScreenPresenter(Beginner_ScreenView& v);

    /**
     * The activate function is called automatically when this screen is "switched in"
     * (ie. made active). Initialization logic can be placed here.
     */
    virtual void activate();

    /**
     * The deactivate function is called automatically when this screen is "switched out"
     * (ie. made inactive). Teardown functionality can be placed here.
     */
    virtual void deactivate();

    virtual ~Beginner_ScreenPresenter() {}

private:
    Beginner_ScreenPresenter();

    Beginner_ScreenView& view;
};

#endif // BEGINNER_SCREENPRESENTER_HPP

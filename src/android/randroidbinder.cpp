
#include "randroidbinder.h"
#include "rview.h"
#include "randroidlogdevice.h"

namespace chikkooos
{

RAndroidBinder::RAndroidBinder()
 : mInitialized(false)
{}

RBinder & RBinder::instance()
{
	static RAndroidBinder _instance;
    return _instance;
}

int RAndroidBinder::exec()
{
    return 1;
}

bool RAndroidBinder::initialize(int argc, char **argv)
{
    return init();
}

bool RAndroidBinder::initialize()
{
    return init();
}

void RAndroidBinder::flush()
{
    glFinish();
}

void RAndroidBinder::destroy()
{}

void RAndroidBinder::reshape(int w, int h)
{
    RAndroidBinder::instance().renderer()->onReshape(w, h);
    ((RAndroidBinder &)RAndroidBinder::instance()).setSize(w, h);
}

void RAndroidBinder::display()
{
    ((RAndroidBinder &)RAndroidBinder::instance()).draw();
}

void RAndroidBinder::mouse(int button, int state, int x, int y)
{
    RAndroidBinder::instance().renderer()->onMouseEvent(button, state, x, y);
}

void RAndroidBinder::menu(int id)
{
    RAndroidBinder::instance().renderer()->onMenuItemClicked(id);
}

void RAndroidBinder::timer(int)
{
    ((RAndroidBinder &)RAndroidBinder::instance()).update();
}

void RAndroidBinder::addTimer(unsigned int delay)
{
}

void RAndroidBinder::redraw()
{}

void RAndroidBinder::draw()
{
    RBinder::draw();
}

void RAndroidBinder::update()
{
    RBinder::update();
}

bool RAndroidBinder::init()
{
    if (!mInitialized) {
        rLog().setOutDevice(new RAndroidLogDevice());

        if (!renderer()->onInit()) {
    	    rLogE() << "initialization failed" << std::endl;
    	    return false;
        }
    }

    return true;
}

}


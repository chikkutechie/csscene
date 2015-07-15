
#ifndef RANDROIDBINDER_H
#define RANDROIDBINDER_H

#include "rcommon.h"
#include "rbinder.h"

#include <string>
#include <iostream>

namespace chikkooos
{

class RAndroidBinder: public RBinder
{
public:
    RAndroidBinder();

    int exec();

    bool initialize();
    bool initialize(int argc, char **argv);

    void destroy();

    void addTimer(unsigned int delay = chikkooos::TimerDelay);

    void redraw();
    void flush();

    int getWidth() {
        return mWidth;
    }

    int getHeight() {
        return mHeight;
    }

    static void reshape(int w, int h);

    static void display();

    static void mouse(int button, int state, int x, int y);

    static void menu(int id);

    static void timer(int);

private:
    void setSize(int w, int h)
    {
        mWidth = w;
        mHeight = h;
    }

protected:
    virtual bool init();
    virtual void draw();
    virtual void update();

protected:
    bool mInitialized;
};

}

#endif

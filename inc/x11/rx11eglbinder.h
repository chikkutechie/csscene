
#ifndef RX11EGLBINDER_H
#define RX11EGLBINDER_H

#include "rcommon.h"
#include "rbinder.h"
#include "rtime.h"

#include <string>
#include <iostream>
#include <vector>

#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/keysym.h>
#include <EGL/egl.h>

namespace chikkooos
{

class RX11EGLBinder: public RBinder
{
public:
    RX11EGLBinder();

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

private:
    static void reshape(int w, int h);

    static void display();

    static void mouse(int button, int state, int x, int y);

    static void menu(int id);

    static void timer(int);

    static void keyboard(unsigned char, int, int);

    bool createWindow();

    void setSize(int w, int h)
    {
        mWidth = w;
        mHeight = h;
    }

protected:
    bool init();
    void draw();
    void update();

    void checkTimers();

    bool initializeEGL();
    void destroyEGL();

    bool createEGLContext();
    void destroyEGLContext();

    bool bindEGL();
    void unbindEGL();

protected:
    class TimerEntry
    {
    public:
        unsigned int mDelay;
        RTime mTime;
    };

    typedef std::vector<TimerEntry> TimerSet;
    typedef TimerSet::iterator TimerSetIter;

protected:
    int mX;
    int mY;
    std::string mTitle;

    bool mInitialized;
    bool mDirty;

    Display *mX11Display;
    Window mX11Window;

    EGLDisplay mEGLDisplay;
    EGLContext mEGLContext;
    EGLSurface mEGLSurface;
    EGLConfig mEGLConfig;
    EGLint mNumberOfEGLConfig;
    EGLint mVisualId;

    TimerSet mTimers;
};

}

#endif

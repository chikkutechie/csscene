

#include "rcommon.h"
#include "rview.h"
#include "rx11eglbinder.h"
#include "rlog.h"

#include <cstdlib>
#include <string>
#include <iostream>

namespace chikkooos
{

RX11EGLBinder::RX11EGLBinder()
 : mInitialized(false),
   mDirty(true),
   mX11Display(0),
   mEGLDisplay(EGL_NO_DISPLAY),
   mEGLContext(EGL_NO_CONTEXT),
   mEGLSurface(EGL_NO_SURFACE)
{}

RBinder & RBinder::instance()
{
	static RX11EGLBinder _instance;
    return _instance;
}

bool RX11EGLBinder::initialize()
{
    if (mInitialized) {
        return mInitialized;
    }

    mX11Display = XOpenDisplay(0);
    if (!mX11Display) {
        rLogE() << "couldn't open display " << std::getenv("DISPLAY") << std::endl;
        return false;
    }

    if (!initializeEGL()) {
        return false;
    }

    if (!createWindow()) {
        return false;
    }

    if (!createEGLContext()) {
        rLogE() << "EGL context creation failed" << std::endl;
        return false;
    }

    XMapWindow(mX11Display, mX11Window);

    if (!bindEGL()) {
        return false;
    }

    mInitialized = true;

    reshape(WindowWidth, WindowHeight);

    return init();
}

bool RX11EGLBinder::bindEGL()
{
    if (mEGLDisplay == EGL_NO_DISPLAY ||
        mEGLContext == EGL_NO_CONTEXT ||
        mEGLSurface == EGL_NO_SURFACE) {
        rLogE() << "cannot make null display, context and surface as current" << std::endl;
        return false;
    }

    if (eglMakeCurrent(mEGLDisplay, mEGLSurface, mEGLSurface, mEGLContext) == EGL_FALSE) {
        rLogE() << "eglMakeCurrent failed : " << eglGetError() << std::endl;
        return false;
    }
    return true;
}

void RX11EGLBinder::unbindEGL()
{
    if (mEGLDisplay != EGL_NO_DISPLAY) {
        eglMakeCurrent(mEGLDisplay, EGL_NO_SURFACE, EGL_NO_SURFACE, EGL_NO_CONTEXT);
    }
}

bool RX11EGLBinder::createWindow()
{
    int scrnum;
    XSetWindowAttributes attr;
    unsigned long mask;
    Window root;
    Window win;
    XVisualInfo *visInfo, visTemplate;
    int num_visuals;

    scrnum = DefaultScreen(mX11Display);
    root = RootWindow(mX11Display, scrnum);

    visTemplate.visualid = mVisualId;
    visInfo = XGetVisualInfo(mX11Display, VisualIDMask, &visTemplate, &num_visuals);
    if (!visInfo) {
        rLogE() << "couldn't get X visual" << std::endl;
        return false;
    }

    attr.background_pixel = 0;
    attr.border_pixel = 0;
    attr.colormap = XCreateColormap(mX11Display, root, visInfo->visual, AllocNone);
    attr.event_mask = StructureNotifyMask | ExposureMask | KeyPressMask;
    attr.override_redirect = 0;
    mask = CWBackPixel | CWBorderPixel | CWColormap | CWEventMask | CWOverrideRedirect;

    win = XCreateWindow(mX11Display, root, 0, 0, WindowWidth, WindowHeight,
                0, visInfo->depth, InputOutput,
                visInfo->visual, mask, &attr);

    {
        XSizeHints sizehints;
        sizehints.x = WindowPositionX;
        sizehints.y = WindowPositionY;
        sizehints.width  = WindowWidth;
        sizehints.height = WindowHeight;
        sizehints.flags = USSize | USPosition;
        XSetNormalHints(mX11Display, win, &sizehints);
        XSetStandardProperties(mX11Display, win, mTitle.c_str(), mTitle.c_str(),
                               None, (char **)0, 0, &sizehints);
    }

    XFree(visInfo);

    mX11Window = win;

    return true;
}

bool RX11EGLBinder::initialize(int, char **)
{
    return initialize();
}

void RX11EGLBinder::destroy()
{
    if (mInitialized) {
        destroyEGL();

        //XDestroyWindow(mX11Display, mX11Window);
        XCloseDisplay(mX11Display);

        mInitialized = false;
    }
}

bool RX11EGLBinder::initializeEGL()
{
    if (mEGLDisplay != EGL_NO_DISPLAY) {
        return true;
    }

    if (!mX11Display) {
        rLogE() << "x11 display not created" << std::endl;
        return false;
    }

    mEGLDisplay = eglGetDisplay(mX11Display);
    if (mEGLDisplay == EGL_NO_DISPLAY) {
        rLogE() << "eglGetDisplay failed : " << eglGetError() << std::endl;
        return false;
    }

    EGLint egl_major, egl_minor;
    if (eglInitialize(mEGLDisplay, &egl_major, &egl_minor) == EGL_FALSE) {
        rLogE() << "eglInitialize failed : " << eglGetError() << std::endl;
	    eglTerminate(mEGLDisplay);
	    mEGLDisplay = EGL_NO_DISPLAY;
        return false;
    }

    eglBindAPI(EGL_OPENGL_ES_API);

    const char *s = eglQueryString(mEGLDisplay, EGL_VERSION);
    rLogI() << "EGL_VERSION = " << s << std::endl;

    static const EGLint attribs[] = {
        EGL_RED_SIZE, 8,
        EGL_GREEN_SIZE, 8,
        EGL_BLUE_SIZE, 8,
        EGL_ALPHA_SIZE, 8,
        EGL_DEPTH_SIZE, 8,
        EGL_STENCIL_SIZE, 8,
#if defined(R_ES2)
        EGL_RENDERABLE_TYPE, EGL_OPENGL_ES2_BIT,
#endif
        EGL_NONE
    };

    if ((eglChooseConfig(mEGLDisplay, attribs, &mEGLConfig, 1, &mNumberOfEGLConfig)  == EGL_FALSE) ||
        !mNumberOfEGLConfig) {
        rLogE() << "couldn't get an EGL config : " << eglGetError() << std::endl;
        return false;
    }

    if (eglGetConfigAttrib(mEGLDisplay, mEGLConfig, EGL_NATIVE_VISUAL_ID, &mVisualId) == EGL_FALSE) {
        rLogE() << "eglGetConfigAttrib failed : " << eglGetError() << std::endl;
        return false;
    }

    return true;
}

bool RX11EGLBinder::createEGLContext()
{
    if (!initializeEGL()) {
        return false;
    }

    if (mEGLContext == EGL_NO_CONTEXT) {

#if defined(R_ES2)
    EGLint contextAttribs[] = {EGL_CONTEXT_CLIENT_VERSION, 2,
                               EGL_NONE, EGL_NONE };
#else
    EGLint * contextAttribs = 0;
#endif

        mEGLContext = eglCreateContext(mEGLDisplay, mEGLConfig, EGL_NO_CONTEXT, contextAttribs);
        if (mEGLContext == EGL_NO_CONTEXT) {
            rLogE() << "eglCreateContext failed : " << eglGetError() << std::endl;
            return false;
        }
    }

    if (mEGLSurface == EGL_NO_SURFACE) {
        mEGLSurface = eglCreateWindowSurface(mEGLDisplay, mEGLConfig, mX11Window, 0);
        if (mEGLSurface == EGL_NO_SURFACE) {
            rLogE() << "eglCreateWindowSurface failed : " << eglGetError() << std::endl;
            return false;
        }
    }

    return true;
}

void RX11EGLBinder::destroyEGLContext()
{
    if (mEGLDisplay != EGL_NO_DISPLAY) {

        unbindEGL();

        if (mEGLSurface != EGL_NO_SURFACE) {
            eglDestroySurface(mEGLDisplay, mEGLSurface);
            mEGLSurface = EGL_NO_SURFACE;
        }

        if (mEGLContext != EGL_NO_CONTEXT) {
            eglDestroyContext(mEGLDisplay, mEGLContext);
            mEGLContext = EGL_NO_CONTEXT;
        }
    }
}

void RX11EGLBinder::destroyEGL()
{
    if (mEGLDisplay != EGL_NO_DISPLAY) {

        unbindEGL();

        if (mEGLSurface != EGL_NO_SURFACE) {
            eglDestroySurface(mEGLDisplay, mEGLSurface);
            mEGLSurface = EGL_NO_SURFACE;
        }

        if (mEGLContext != EGL_NO_CONTEXT) {
            eglDestroyContext(mEGLDisplay, mEGLContext);
            mEGLContext = EGL_NO_CONTEXT;
        }

        eglTerminate(mEGLDisplay);
        mEGLDisplay = EGL_NO_DISPLAY;
    }
}

void RX11EGLBinder::addTimer(unsigned int delay)
{
    TimerEntry entry;
    entry.mTime.start();
    entry.mDelay = delay;
    mTimers.push_back(entry);
}

void RX11EGLBinder::checkTimers()
{
    if (mTimers.empty()) {
        return;
    }

    TimerSet expiredTimers;

    for (unsigned int i = 0; i < mTimers.size();) {
        TimerEntry &te = mTimers[i];
        if (te.mTime.elapsed() > te.mDelay) {
            expiredTimers.push_back(te);
            mTimers.erase(mTimers.begin() + i);
        } else {
            ++i;
        }
    }

    int expiredTimersCount = expiredTimers.size();
    for (int i = 0; i < expiredTimersCount; ++i) {
        RX11EGLBinder::timer(0);
    }
}

void RX11EGLBinder::draw()
{
    RBinder::draw();
}

void RX11EGLBinder::update()
{
    RBinder::update();
}

void RX11EGLBinder::redraw()
{
    mDirty = true;
}

void RX11EGLBinder::reshape(int w, int h)
{
    RX11EGLBinder::instance().renderer()->onReshape(w, h);
    ((RX11EGLBinder &)RX11EGLBinder::instance()).setSize(w, h);
}

void RX11EGLBinder::display()
{
    ((RX11EGLBinder &)RX11EGLBinder::instance()).draw();
}

void RX11EGLBinder::mouse(int button, int state, int x, int y)
{
    RX11EGLBinder::instance().renderer()->onMouseEvent(button, state, x, y);
}

void RX11EGLBinder::menu(int id)
{
    RX11EGLBinder::instance().renderer()->onMenuItemClicked(id);
}

void RX11EGLBinder::timer(int)
{
    ((RX11EGLBinder &)RX11EGLBinder::instance()).update();
    ((RX11EGLBinder &)RX11EGLBinder::instance()).redraw();
}

void RX11EGLBinder::keyboard(unsigned char key, int x, int y)
{
    RX11EGLBinder::instance().renderer()->onKeyEvent(key, x, y);
}

bool RX11EGLBinder::init()
{
    rLogI() << "init" << std::endl;
    if (!renderer()->onInit()) {
    	rLogE() << "initialization failed" << std::endl;
    	return false;
    }
    return true;
}

int RX11EGLBinder::exec()
{
    rLogI() << "exec" << std::endl;

    Atom wmDeleteMessage = XInternAtom(mX11Display, "WM_DELETE_WINDOW", False);

    bool finished = false;

    while (!finished) {
        int redraw = 1;

        if (XPending(mX11Display) > 0) {
            XEvent event;
            XNextEvent(mX11Display, &event);

            switch (event.type) {

            case ClientMessage:
                if ((Atom)event.xclient.data.l[0] == wmDeleteMessage) {
                    XDestroyWindow(mX11Display, event.xclient.window);
                }
                finished = true;
                break;

            case Expose:
                redraw = 1;
                break;

            case ConfigureNotify:
                reshape(event.xconfigure.width, event.xconfigure.height);
                break;

            case KeyPress: {
                char buffer[10];
                int code;
                code = XLookupKeysym(&event.xkey, 0);
                if (code == XK_Left) {
                } else if (code == XK_Right) {
                } else if (code == XK_Up) {
                } else if (code == XK_Down) {
                } else if (code == XK_b) {
                } else {
                    XLookupString(&event.xkey, buffer, sizeof(buffer), 0, 0);
                    rLogI() << "key : " << int(buffer[0]) << std::endl;
                    RX11EGLBinder::keyboard(buffer[0], 0, 0);
                }
                }
                redraw = 1;
                break;
            default:
                break;
            }
        }

        if (redraw || mDirty) {
            display();
            eglSwapBuffers(mEGLDisplay, mEGLSurface);
            mDirty = false;
        }

        checkTimers();

        usleep(1000 * 1);
    }

    return 0;
}

}




#ifndef RGLUTBINDER_H
#define RGLUTBINDER_H

#include <string>
#include <iostream>

#include "rcommon.h"
#include "rbinder.h"

namespace chikkooos
{

class RGlutBinder: public RBinder
{
public:
    RGlutBinder();

    int exec();

    bool initialize();
    bool initialize(int argc, char **argv);

    void destroy();

    void redraw();

    int getWidth()
    {
        return mWidth;
    }

    int getHeight()
    {
        return mHeight;
    }

private:
    static void reshape(int w, int h);

    static void display();

    static void mouse(int button, int state, int x, int y);
    static void mouseMove(int x, int y);

    static void menu(int id);

    static void timer(int);

    static void keyboard(unsigned char, int, int);

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
    int mWidth;
    int mHeight;
    int mX;
    int mY;
    std::string mTitle;
    int mMenu;
};

}

#endif

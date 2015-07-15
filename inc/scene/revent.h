
#ifndef REVENT_H
#define REVENT_H

namespace chikkooos
{

class RItem;

class REvent
{
public:
    /* mouse button */
    static const int MouseLeftButton   = 0x0000;
    static const int MouseMiddleButton = 0x0001;
    static const int MouseRightButton  = 0x0002;

    /* mouse state */
    static const int MouseDown = 0x0000;
    static const int MouseUp   =  0x0001;
    static const int MouseLeft    = 0x0000;
    static const int MouseEntered = 0x0000;


    /* touch state */
    static const int TouchDown = 0x0000;
    static const int TouchUp   =  0x0001;

    /* Key code */
    static const int KeyCodeEscape = 0x1B;
    static const int KeyCodeBack   = 0x00000004;

public:
    int mButton;
    int mState;
    int mKey;
    int mX;
    int mY;
    RItem * mSource;

public:
    REvent(RItem *source = 0)
     : mSource(source)
    {}

    REvent(int x, int y, int state, int button, RItem *source = 0)
     : mButton(button),
       mState(state),
       mX(x),
       mY(y),
       mSource(source)
    {}

    REvent(int x, int y, int key, RItem *source = 0)
     : mKey(key),
       mX(x),
       mY(y),
       mSource(source)
    {}
};

class REventListner
{
public:
    virtual ~REventListner()
    {}

    virtual void handle(REvent const & event) = 0;
};

class RCPShapeItem;

class RCollisionEvent
{
public:
    RCollisionEvent(RCPShapeItem *a = 0, RCPShapeItem *b = 0)
     : mItemA(a),
       mItemB(b)
    {}

    RCPShapeItem * mItemA;
    RCPShapeItem * mItemB;
};

class RCollisionEventListner
{
public:
    virtual ~RCollisionEventListner()
    {}

    virtual void handle(RCollisionEvent const & event) = 0;
};

}

#endif


#ifndef SMARTPOINTER_H
#define SMARTPOINTER_H

#include "rsharedobject.h"

namespace chikkooos
{

template <typename A, typename D>
class RSmartPointerBase: public RSharedObject<A>
{
public:
    RSmartPointerBase(D * p)
    {
        this->data_p().mPtr = p;
        this->data_p().mOwn = true;
    }

    bool isNull() const
    {
        return data() == 0;
    }

    D * data()
    {
        return this->data_p().mPtr;
    }

    const D * data() const
    {
        return this->data_p().mPtr;
    }

    D * take()
    {
        this->data_p().mOwn = false;
        return this->data_p().mPtr;
    }

    D * operator->()
    {
        return data();
    }

    const D * operator->() const
    {
        return data();
    }

    D & operator*()
    {
        return *(data());
    }

    const D * operator*() const
    {
        return *(data());
    }
};


template <typename D>
class RSmartPointerData
{
public:
    RSmartPointerData()
     : mOwn(true),
       mPtr(0)
    {}

    ~RSmartPointerData()
    {
        if (mOwn) {
            delete mPtr;
        }
    }

private:
    RSmartPointerData(RSmartPointerData const &);
    RSmartPointerData & operator=(RSmartPointerData const &);

public:
    bool mOwn;
    D * mPtr;
};


template <typename D>
class RSmartArrayPointerData
{
public:
    RSmartArrayPointerData()
     : mOwn(true),
       mPtr(0)
    {}

    ~RSmartArrayPointerData()
    {
        if (mOwn) {
            delete [] mPtr;
        }
    }

private:
    RSmartArrayPointerData(RSmartArrayPointerData const &);
    RSmartArrayPointerData & operator=(RSmartArrayPointerData const &);

public:
    bool mOwn;
    D * mPtr;
};

template <typename D>
class RSmartArrayPointer: public RSmartPointerBase<RSmartArrayPointerData<D>, D>
{
public:
    RSmartArrayPointer(D * p=0)
     : RSmartPointerBase<RSmartArrayPointerData<D>, D>(p)
    {}

    operator D*()
    {
        return this->data();
    }

    operator const D*() const
    {
        return this->data();
    }
};

template <typename D>
class RSmartPointer: public RSmartPointerBase<RSmartPointerData<D>, D>
{
public:
    RSmartPointer(D * p=0)
     : RSmartPointerBase<RSmartPointerData<D>, D>(p)
    {}

    operator D*()
    {
        return this->data();
    }

    operator const D*() const
    {
        return this->data();
    }
};

}

#endif


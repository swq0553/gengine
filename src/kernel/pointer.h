#pragma once

#include "primitives.h"

namespace gengine
{

template<typename T>
class Pointer
{
public:
    Pointer()
        :
        value(nullptr)
    {
    }

    Pointer(T * _value)
        :
        value(_value)
    {
    }

    T * operator->() const
    {
        return value;
    }

    T & operator*() const
    {
        return * value;
    }

    operator T*()
    {
        return value;
    }

    bool isNull() const { return value == nullptr; }

protected:
    T
        * value;
};

}

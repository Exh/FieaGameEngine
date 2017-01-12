#include "pch.h"

namespace FieaGameEngine
{
    SList::SList() :
        mData(0)
    {

    }

    SList::SList(std::int32_t data) :
        mData(data)
    {

    }

    int FieaGameEngine::SList::Data() const
    {
        return mData;
    }
}

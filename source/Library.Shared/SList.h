#pragma once

#include <cstdint>

namespace FieaGameEngine
{
    class SList
    {
    public:

        /************************************************************************/
        /** Initializes mData to 0 and that is it.                              */
        /************************************************************************/
        SList();

        /************************************************************************/
        /** Constructor that initializes mData with a specific value            */
        /** @param value integer value to initialize mData with                 */
        /************************************************************************/
        SList(std::int32_t value);

        /************************************************************************/
        /** Gets the data variable                                              */
        /** @return Value of mData                                              */
        /************************************************************************/
        int Data() const;

    private:
        int mData;
    };
}

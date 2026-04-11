#ifndef __PH_BASESUP_HPP__
#define __PH_BASESUP_HPP__

#include <basetsd.h>
#include <winnt.h>

struct PhStringRef {
    /** The length, in bytes, of the string. */
    SIZE_T length;
    /** The buffer containing the contents of the string. */
    PWCH buffer;
};
using PphStringRef = PhStringRef*;

typedef const PhStringRef* PcphStringRef;

struct PhString {
    union {
        PhStringRef stringRef;

        struct {
            SIZE_T length;
            PWCH buffer;
        };
    };

    union {
        WCHAR data[1]{};

        struct {
            ULONG32 allocationFlags;
            PVOID allocation;
        };
    };
};
using PphString = PhString*;

struct PhList {
    ULONG32 count;
    ULONG32 allocatedCount;
    PVOID* items;
};
using PphList = PhList*;

#endif

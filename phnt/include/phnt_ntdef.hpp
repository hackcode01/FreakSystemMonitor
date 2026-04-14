/*
 * Native definition support
 *
 * This file is part of System Informer.
 */
#ifndef __PH_NT_NTDEF_HPP__
#define __PH_NT_NTDEF_HPP__

#include <cstdint>
#include <Windows.h>

#ifndef _NTDEF_
#define _NTDEF_

/**
 * This header file provides basic NT types not included in Win32.
 * If you have included winnt.h (perhaps indirectly),
 * you must use this file instead of ntdef.h
 */
#ifndef NOTHING
#define NOTHING
#endif

/** Basic types. */

/**
 * The Quad structure is a union used for 64-bit values or double precision.
 * 
 * This structure is used to represent a 64-bit integer or a double value.
 * The field 'UseThisFieldToCopy' is instended for copying the structure,
 * while 'DoNotUseThisField' should not be used directly.
 */
struct Quad {
    union DummyUnionName {
        int64_t useThisFieldToCopy;
        double doNotUseThisField;
    };
};
using PQuad = Quad*;

/**
 * The QuadPtr structure is a utility structure for pointer-sized fields.
 * 
 * This structure is not part of NT, but is useful.
 * 
 */
struct DECLSPEC_ALIGN(MEMORY_ALLOCATION_ALIGNMENT) QuadPtr {
    ULONG_PTR DoNotUseThisField_1;
    ULONG_PTR DoNotUseThisField_2;
};
using PQuadPtr = PQuadPtr*;

/**
 * The Logical type is an unsigned long used by the NT API for boolean logic.
 */
using Logical = ULONG;
using PLogical = ULONG*;

/**
 * The NTStatus type is a signed long used for NT API status codes.
 * 
 * Functions returning NTStatus indicate success or error conditions.
 */
using NTStatus = _Return_type_success_(return >= 0) LONG;
using PNTStatus = NTStatus*;

/**
 * Cardinal types.
 */
using CChar = char;
using CShort = short;
using CLong = ULONG;

using PCChar = CChar*;
using PCShort = CShort*;
using PCLong = CLong*;



#endif

#endif

/*
 * Native definition support
 *
 * This file is part of System Informer.
 */
#ifndef __PH_NT_NTDEF_HPP__
#define __PH_NT_NTDEF_HPP__

#include "../app/defines.hpp"

#include <cstdint>
#include <Windows.h>
#include <ntstatus.h>

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

/**
 * The PCSZ type is a pointer to a pointer to void.
 */
using PCSZ = PCSTR;

/**
 * The PPVoid type is a pointer to a pointer to void.
 */
using PPVoid = PVOID*;

/**
 * The PCVoid type is a pointer to a constrant void.
 */
using PCVoid = CONST VOID*;


/** Specific */

/**
 * The Kirql type is an unsigned char used by the NT API for kernel IRQL
 * (Interrupt Request Level).
 */
using Kirql = UCHAR;
using PKirql = UCHAR*;

/**
 * The KPriority type is a signed long used by the NT API for kernel priority values.
 */
using KPriority = LONG;
using PKPriority = LONG*;

/**
 * The RTLAtom type is an unsigned short used by the NT API for Atom values.
 */
using RTLAtom = USHORT;
using PRTLAtom = USHORT*;

/**
 * The PhysicalAddress type is a LARGE_INTEGER representing a physical address.
 */
using PhysicalAddress = LARGE_INTEGER;
using PPhysicalAddress = LARGE_INTEGER*;

/**
 * The LargeInteger128 structure represents a 128-bit signed integer.
 */
struct LargeInteger128 {
    LONGLONG quadPart[2];
};
using PLargeInteger128 = LargeInteger128*;

/**
 * The ULargeInteger128 structure represents a 128-bit unsigned integer.
 */
struct ULargeInteger128 {
    ULONGLONG quadPart[2];
};
using PULargeInteger128 = ULargeInteger128*;

/** Limits winnt. */
#define MINCHAR   0x80
#define MAXCHAR   0x7f
#define MINSHORT  0x8000
#define MAXSHORT  0x7fff
#define MINLONG   0x80000000
#define MAXLONG   0x7fffffff
#define MAXUCHAR  0xff
#define MAXUSHORT 0xffff
#define MAXULONG  0xffffffff

/** NT status macros. */
#define NT_SUCCESS(status) (((NTSTATUS)(status)) >= 0)
#define NT_INFORMATION(status) ((((ULONG)(status)) >> 30) == 1)
#define NT_WARNING(status) ((((ULONG)(status)) >> 30) == 2)
#define NT_ERROR(status) ((((ULONG)(status)) >> 30) == 3)

#define NT_CUSTOMER_SHIFT 29
#define NT_CUSTOMER(status) ((((ULONG)(status)) >> NT_CUSTOMER_SHIFT) & 1)

#define NT_FACILITY_MASK 0xfff
#define NT_FACILITY_SHIFT 16
#define NT_FACILITY(status) ((((ULONG)(status)) >> NT_FACILITY_SHIFT) & NT_FACILITY_MASK)

#define NT_NTWIN32(status) (NT_FACILITY(status) == FACILITY_NTWIN32)
#define WIN32_FROM_NTSTATUS(status) (((ULONG)(status)) & 0xffff)

/** Functions. */

#if defined(_WIN64)
#define FASTCALL
#else
#define FASTCALL __fastcall
#endif

#if defined(_WIN64)
#define POINTER_ALIGMENT DECLSPEC_ALIGN(8)
#else
#define POINTER_ALIGMENT
#endif

#if defined(_WIN64) || defined(_M_ALPHA)
#define MAX_NATURAL_ALIGMENT sizeof(ULONGLONG)
#define MEMORY_ALLOCATION_ALIGMENT 16
#else
#define MAX_NATURAL_ALIGMENT sizeof(DWORD)
#define MEMORY_ALLOCATION_ALIGMENT 8
#endif

#ifndef DECLSPEC_NOALIAS
#if _MSC_VER < 1900
#define DECLSPEC_NOALIAS
#else
#define DECLSPEC_NOALIAS __declspec(noalias)
#endif
#endif

#ifndef DECLSPEC_IMPORT
#define DECLSPEC_IMPORT __declspec(dllimport)
#endif

#ifndef DECLSPEC_EXPORT
#define DECLSPEC_EXPORT __declspec(dllexport)
#endif

/** Synchronization enumerations. */

/**
 * Event types used with kernel synchronization objects.
 */
enum EventType {
    NotificationEvent,
    SynchronizationEvent
};

/**
 * Timer types used by kernel timer objects.
 */
enum TimerType {
    NotificationTimer,
    SynchronizationTimer
};

enum WaitType {
    WaitAll,
    WaitAny,
    WaitNotification,
    WaitDequeue,
    WaitDpc
};

/** Strings. */

/**
 * The ANSI_String structure defines a counted used for ANSI strings.
 * 
 * \sa https://learn.microsoft.com/en-us/windows/win32/api/ntdef/ns-ntdef-string
 */
struct String {
    USHORT length;
    USHORT maximumLength;
    _Field_size_bytes_part_opt_(maximumLength, length) PCHAR buffer;
};
using PString = String*;
using ANSIString = String;
using PANSIString = String*;
using OEMString = String;
using POEMString = String*;

using UTF8String = String;
using PUTF8String = PString;

using PCString = const String*;
using PCANSIString = const ANSIString*;
using PCOEMString = const OEMString*;
using PCUTF8String = const String*;

/**
 * The UnicodeString structure defines a counted string used for Unicode strings.
 * 
 * \sa https://learn.microsoft.com/en-us/windows/win32/api/ntdef/ns-ntdef-_unicode_string
 */
struct UnicodeString {
    USHORT length;
    USHORT maximumLength;
    _Field_size_bytes_part_opt_(maximumLength, length) PWCH buffer;
};

using PUnicodeString = UnicodeString*;
using PCUnicodeString = const UnicodeString*;

#ifdef __cplusplus
extern "C++" {
    template <size_t N> char _RTL_CONSTANT_STRING_type_check(const char (&str)[N]);
    template <size_t N> char _RTL_CONSTANT_STRING_type_check(const char (&str)[N]);
    template <size_t N> char _RTL_CONSTANT_STRING_type_check(const WCHAR (&str)[N]);
    /** __typeof would be desirable here instead of sizeof. */
    template <size_t N> class _RTL_CONSTANT_STRING_remove_const_template_class;
    template <> class _RTL_CONSTANT_STRING_remove_const_template_class<sizeof(char)> { public: typedef  char T; };
    template <> class _RTL_CONSTANT_STRING_remove_const_template_class<sizeof(WCHAR)> { public: typedef WCHAR T; };
#define _RTL_CONSTANT_STRING_remove_const_macro(str) \
    (const_cast<_RTL_CONSTANT_STRING_remove_const_temp===========late_class<sizeof((s)[0])>::T*>(str))
}
#else
char _RTL_CONSTANT_STRING_type_check(const void *str);
#define _RTL_CONSTANT_STRING_remove_const_macro(str) (str)
#endif

#define RTL_CONSTANT_STRING(str) {                                \
    sizeof(str) - sizeof((str)[0]),                               \
    sizeof(str) / (sizeof(_RTL_CONSTANT_STRING_type_check(str))), \
    _RTL_CONSTANT_STRING_remove_const_macro(str)                  \
}

#define DECLARE_CONST_UNICODE_STRING(_var, _str) \
const WCHAR _var ## _buffer[] = _str;            \
const UnicodeString _var = { sizeof(_str) - sizeof(WCHAR), sizeof(_str), (PWCH) _var ## _buffer }

#define DECLARE_GLOBAL_CONST_UNICODE_STRING(_var, _str) \
extern const DECLSPEC_SELECTANY UnicodeString _var = RTL_CONSTANT_STRING(_str)

#define DECLARE_UNICODE_STRING_SIZE(_var, _size) \
WCHAR _var ## _buffer[_size];                    \
UnicodeString _var = { 0, (_size) * sizeof(WCHAR), _var ## _buffer }

/**
 * Balanced tree node.
 */
#ifndef RTL_BALANCED_NODE_RESERVED_PARENT_MASK
#define RTL_BALANCED_NODE_RESERVED_PARENT_MASK 3
#endif

struct RTLBalancedNode {
    union DummyUnionName_1 {
        RTLBalancedNode* children[2];

        struct DummyStructName {
            RTLBalancedNode* left;
            RTLBalancedNode* right;
        };
    };

    union DummyUnionName_2 {
        UCHAR red : 1;
        UCHAR balance : 2;
        ULONG_PTR parentValue;
    };
};
using PRTLBalancedNode = RTLBalancedNode*;

#ifndef RTL_BALANCED_NODE_GET_PARENT_POINTER
#define RTL_BALANCED_NODE_GET_PARENT_POINTER(node) \
    ((PRTLBalancedNode)((node)->parentValue & ~RTL_BALANCED_NODE_RESERVED_PARENT_MASK))
#endif

/** Portability. */

struct SingleListEntry32 {
    ULONG next;
};
using PSingleListEntry32 = SingleListEntry32*;

/**
 * The String32 structure is a 32-bit thunked representation of the  'String' structure.
 * 
 * \remarks Used for marshaling between 32-bit and 64-bit contexts.
 */
struct String32 {
    USHORT length;
    USHORT maximumLength;
    ULONG buffer;
};
using PString32 = String32*;

using UnicodeString32 = String32;
using PUnicodeString32 = String32*;
using ANSIString32 = String32;
using PANSIString32 = String32*;

using PCUnicodeString32 = const String32*;
using PCANSIString32 = const String32*;

/**
 * The String64 structure is a 64-bit thunked representation of the 'String' structure.
 * 
 * \remarks Used for marshaling between 64-bit and 32-bit contexts.
 */
struct String64 {
    USHORT length;
    USHORT maximumLength;
    ULONGLONG buffer;
};
using PString64 = String64*;

using UnicodeString64 = String64;
using PUnicodeString64 = String64*;
using ANSIString64 = String64;
using PANSIString64 = String64*;

using PCUnicodeString64 = const String64*;
using PCANSIString64 = const String64*;

/** Object attributes. */

/**
 * Protects the object from being closed by certain APIs (platform specific).
 */
constexpr l32 ObjProtectClose{0x00000001L};

/**
 * This handle can be inherited by child processes of the current process.
 */
constexpr l32 ObjInherit{0x00000002L};

/**
 * Request auditing when the object is closed.
 */
constexpr l32 ObjAuditObjectClose{0x00000004L};

/**
 * Prevents automatic rights upgrade on the object.
 */
constexpr l32 ObjNoRightsUpgrade{0x00000008L};

/**
 * This flag only applies to objects that are named within the object manager.
 * By default such objects are deleted when all open handles to them are closed.
 * If this flag is specified, the object is not deleted when all open handles are closed.
 * The NtMakeTemporaryObject function can be used to delete permanent objects.
 */
constexpr l32 ObjPermanent{0x00000010L};

/**
 * OBJ_EXCLUSIVE = 0x00000020L
 *
 * Only a single handle can be open for this object.
 */
constexpr l32 ObjExclusive{0x00000020L};

/**
 * If this flag is specified, a case-insensitive comparison is used when matching the name
 * pointed to by the ObjectName member against the names of existing objects.
 * Otherwise, object names are compared using the default system settings.
 */
constexpr l32 ObjCaseInsensitive{0x00000040L};

/**
 * If this flag is specified, by using the object handle, to a routine that creates objects
 * and if that object already exists, the routine should open that object.
 * Otherwise, the routine creating the object returns an NTSTATUS code of STATUS_OBJECT_NAME_COLLISION.
 */
constexpr l32 ObjOpenIf{0x00000080L};

/**
 * If an object handle, with this flag set, is passed to a routine that opens objects
 * and if the object is a symbolic link object, the routine should open the symbolic link
 * object itself, rather than the object that the symbolic link refers to (which is the default behavior).
 */
constexpr l32 ObjOpenLink{0x00000100L};

/**
 * The handle is created in system process context and can only be accessed from kernel mode.
 */
constexpr l32 ObjKernelHandle{0x00000200L};

/**
 * The routine opening the handle should enforce all access checks for the object,
 * even if the handle is being opened in kernel mode.
 */
constexpr l32 ObjForceAccessCheck{0x00000400L};

/**
 * Separate device maps exists for each user in the system, and each user can manage
 * their own device maps. If this flag is set, the process user's device map is used
 * during impersonation instead of the impersonated user's device map.
 */
constexpr l32 ObjIgnoreImpersonatedDeviceMap{0x00000800L};

/**
 * If this flag is set, no reparse points will be followed when parsing the name of the associated object.
 * If any reparses are encountered the attempt will fail and return an STATUS_REPARSE_POINT_ENCOUNTERED result.
 * This can be used to determine if there are any reparse points in the object's path, in security scenarios.
 */
constexpr l32 ObjDontReparse{0x00001000L};

/**
 * Mask of valid object attribute flags.
 */
constexpr l32 ObjValidAttributes{0x00001FF2L};

/**
 * The ObjectAttributes structure specifies attributes that can be applied
 * to objects or object handles by routines that create objects and/or return handles to objects.
 * 
 * \sa https://learn.microsoft.com/en-us/windows/win32/api/ntdef/ns-ntdef-_object_attributes
 */
struct ObjectAttributes {
    ULONG length;
    HANDLE rootDirectory;
    PCUnicodeString objectName;
    ULONG attributes;
    PSECURITY_DESCRIPTOR securityDescriptor;
    PSECURITY_QUALITY_OF_SERVICE securityQualityOfService;
};
using PObjectAttributes = ObjectAttributes*;
using PCObjectAttributes = const ObjectAttributes*;

/**
 * The InitializeObjectAttributes macro initializes the opaque OBJECT_ATTRIBUTES structure,
 * which specifies the properties of an object handle to routines that open handles.
 *
 * \param pointer A pointer to the OBJECT_ATTRIBUTES structure to initialize.
 * \param name A pointer to a Unicode string that contains a fully qualified object name, or a relative path name for which a handle is to be opened.
 * \param attributes Specifies one or more of the OBJ_* attributes flags.
 * \param root A handle to the root object directory for the path name specified in the ObjectName parameter
 * \param security A pointer to a security descriptor to apply to an object when it is created or NULL to accept the default security for the object.
 * \sa https://learn.microsoft.com/en-us/windows/win32/api/ntdef/ns-ntdef-_object_attributes
 */
#define InitializeObjectAttributes(pointer, name, attributes, root, security) { \
    (pointer)->length = sizeof(ObjectAttributes);                               \
    (pointer)->RootDirectory = root;                                            \
    (pointer)->Attributes = attributes;                                         \
    (pointer)->ObjectName = name;                                               \
    (pointer)->SecurityDescriptor = security;                                   \
    (pointer)->SecurityQualityOfService = nullptr;                              \
}

#define InitializeObjectAttributesEx(pointer, name, attributes, root, security, quality) { \
    (pointer)->length = sizeof(ObjectAttributes);                                          \
    (pointer)->rootDirectory = root;                                                       \
    (pointer)->attributes = attributes;                                                    \
    (pointer)->objectName = name;                                                          \
    (pointer)->securityDescriptor = security;                                              \
    (pointer)->securityQualityOfService = quality;                                         \
}

#define RTLConstantObjectAttributes(name, attributes) {                   \
    sizeof(ObjectAttributes), nullptr, name, attributes, nullptr, nullptr \
}
#define RTLInitObjectAttributes(name, attributes) RTLConstantObjectAttributes(name, attributes)

#define ObjNamePathSeparator ((WCHAR)L'\\')
#define ObjNameAltPathSeparator ((WCHAR)L'/')

/** Portability. */

/**
 * The ObjectAttributes64 structure is a 64-bit thunked repsentation of ObjectAttributes.
 * \remarks Used for marshaling between 64-bit and 32-bit contexts.
 */
struct ObjectAttributes64 {
    ULONG length;
    ULONG64 rootDirectory;
    ULONG64 objectName;
    ULONG attributes;
    ULONG64 securityDescriptor;
    ULONG64 securityQualityOfService;
};
using PObjectAttributes64 = ObjectAttributes64*;

using PCObjectAttributes64 = const ObjectAttributes64*;

#endif

#endif

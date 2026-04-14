#ifndef __PH_NT_HPP__
#define __PH_NT_HPP__

#include <winnt.h>

#define PH_NT_MODE_KERNEL 0
#define PH_NT_MODE_USER 1

#define PH_NT_WINDOWS_ANCIENT 0
#define PH_NT_WINDOWS_XP 51 /** August, 2001 */
#define PH_NT_WINDOWS_SERVER_2003 52 /** April, 2003 */
#define PH_NT_WINDOWS_VISTA 60 /** November, 2006 */
#define PH_NT_WINDOWS_7 61 /** July, 2009 */
#define PH_NT_WINDOWS_8 62 /** August, 2012 */
#define PH_NT_WINDOWS_8_1 63 /** August, 2013 */
#define PH_NT_WINDOWS_10 100 /** July, 2015 Version 1507, Build 10240 */
#define PH_NT_WINDOWS_10_TH2 101 /** November, 2015 Version 1511, Build 10586 */
#define PH_NT_WINDOWS_10_RS1 102 /** August, 2016 Version 1607, Build 14393 */
#define PH_NT_WINDOWS_10_RS2 103 /** April, 2017 Version 1703, Build 15063 */
#define PH_NT_WINDOWS_10_RS3 104 /** October, 2017 Version 1709, Build 16299 */
#define PH_NT_WINDOWS_10_RS4 105 /** April, 2018 Version 1803, Build 17134 */
#define PH_NT_WINDOWS_10_RS5 106 /** November, 2018 Version 1809, Build 17763 */
#define PH_NT_WINDOWS_10_19H1 107 /** May, 2019 Version 1903, Build 18362 */
#define PH_NT_WINDOWS_10_19H2 108 /** November, 2019 Version 1909, Build 18363 */
#define PH_NT_WINDOWS_10_20H1 109 /** May, 2020 Version 2004, Build 19041 */
#define PH_NT_WINDOWS_10_20H2 110 /** October, 2020 Build 19042 */
#define PH_NT_WINDOWS_10_21H1 111 /** May, 2021 Build 19043 */
#define PH_NT_WINDOWS_10_21H2 112 /** November, 2021 Build 19044 */
#define PH_NT_WINDOWS_10_22H2 113 /** October, 2022 Build 19045 */
#define PH_NT_WINDOWS_11 114 /** October, 2021 Build 22000 */
#define PH_NT_WINDOWS_11_22H2 115 /** September, 2022 Build 22621 */
#define PH_NT_WINDOWS_11_23H2 116 /** October, 2023 Build 22631 */
#define PH_NT_WINDOWS_11_24H2 117 /** October, 2024 Build 26100 */
#define PH_NT_WINDOWS_11_25H2 117 /** October, 2025 Build 26200 */
#define PH_NT_WINDOWS_NEW ULONG_MAX

#ifndef PH_NT_MODE
#if defined(_NTDDK_) || defined(_NTIFS_) || defined(_NTDRIVER_)
#define PH_NT_MODE PH_NT_MODE_KERNEL
#else
#define PH_NT_MODE PH_NT_MODE_USER
#endif
#endif

#ifndef PH_NT_VERSION
#define PH_NT_VERSION PH_NT_WINDOWS_NEW
#endif

#if (PH_NT_MODE != PH_NT_MODE_KERNEL)
#ifndef PH_NT_INLINE_TYPEDEFS
#define PH_NT_INLINE_TYPEDEFS
#endif
#endif

EXTERN_C_START

#if (PH_NT_MODE != PH_NT_MODE_KERNEL)
#include "phnt/include/phnt_ntdef.hpp"
#endif

EXTERN_C_END

#endif

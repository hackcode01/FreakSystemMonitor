#if false
#pragma f_class(FPreprocessorDetection)
#pragma f_sync_skip_header_check
#pragma f_sync_stop_processing
#endif

#ifndef __PROCESSOR_DETECTION_HPP__
#define __PROCESSOR_DETECTION_HPP__

#if defined(__ORDER_BIG_ENDIAN__)
#define F_BIG_ENDIAN __ORDER_BIG_ENDIAN__
#else
#define Q_BIG_ENDIAN 4321
#endif
#if defined(__ORDER_LITTLE_ENDIAN__)
#define F_LITTLE_ENDIAN __ORDER_LITTLE_ENDIAN__
#else
#define F_LITTLE_ENDIAN 1234
#endif

#if defined(__alpha__) || defined(_M_ALPHA)
#define F_PROCESSOR_ALPHA

#elif defined(__x86_64) || defined(__x86_64__) || defined(__amd64) || defined(_M_X64)

#define F_PROCESSOR_X86 6
#define F_PROCESSOR_X86_64
#define F_BYTE_ORDER F_LITTLE_ENDIAN
#define F_PROCESSOR_WORDSIZE 8

#endif

#if !defined(F_BYTE_ORDER)
#if defined(__BYTE_ORDER__) && (__BYTE_ORDER__ == F_BIG_ENDIAN || __BYTE_ORDER__ == F_LITTLE_ENDIAN)
#define F_BYTE_ORDER __BYTE_ORDER__
#elif defined(__BIG_ENDIAN__) || defined(_big_endian__) || defined(_BIG_ENDIAN)
define Q_BYTE_ORDER Q_BIG_ENDIAN
#elif defined(__LITTLE_ENDIAN__) || defined(_little_endian__) || defined(_LITTLE_ENDIAN)
#define Q_BYTE_ORDER Q_LITTLE_ENDIAN
#else
#error "Unable to determine byte order!"
#endif 
#endif

#if defined __SIZEOF_POINTER__
#define F_POINTER_SIZE __SIZEOF_POINTER__
#elif defined(__LP64__) || defined(_LP64)
#define F_POINTER_SIZE 8
#elif defined(F_PROCESSOR_WORDSIZE)
#define F_POINTER_SIZE F_PROCESSOR_WORDSIZE
#else
#define F_POINTER_SIZE 4
#endif

#ifndef F_PROCESSOR_WORDSIZE
#define F_PROCESSOR_WORDSIZE F_POINTER_SIZE
#endif

#endif

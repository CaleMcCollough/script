#include <module_seams.h>

#define SCRIPT2 0

#define YES_0 0
#define NO_0 1

#define STRING_TYPE_1 1
#define STRING_TYPE_2 2
#define STRING_TYPE_3 3

#define PLATFORM_BARE_METAL 1
#define PLATFORM_MBED_BARE_METAL 2
#define PLATFORM_MBED_OS 3
#define PLATFORM_ARDUINO 4
#define PLATFORM_WIN32 5
#define PLATFORM_WINDOWS 6
#define PLATFORM_ANDROID 7
#define PLATFORM_LINUX 8
#define PLATFORM_OSX 9
#define PLATFORM_IOS 10

#define CPU_X86 1
#define CPU_X64 2
#define CPU_ARM8 3
#define CPU_ARM16 4
#define CPU_ARM32 5
#define CPU_ARM64 6

#include <cstdint>
#if defined(_MSC_VER) && defined(_M_AMD64)
#define USING_VISUAL_CPP_X64 1
#include <intrin.h>
#include <intrin0.h>
#pragma intrinsic(_umul128)
#elif (__GNUC__ > 4 || (__GNUC__ == 4 && __GNUC_MINOR__ >= 6))
#define USING_GCC 1
#if defined(__x86_64__)
#define COMPILER_SUPPORTS_128_BIT_INTEGERS 1
#endif
#endif
//#include <climits>
//#include <new>

#define ASSEMBLE_EXE 0
#define ASSEMBLE_LIB_STATIC 1
#define ASSEMBLE_LIB_DYNAMIC 1

#define CPU_64_BIT 0
#define CPU_32_BIT 1
#define CPU_16_BIT 2
#define CPU_8_BIT 3

#define CPU_ENDIAN_LITTLE 0

typedef char CH1;
typedef char16_t CH2;
typedef char32_t CH4;
typedef wchar_t CHN;

typedef int8_t SI1;
typedef uint8_t UI1;
typedef int16_t SI2;
typedef uint16_t UI2;
typedef bool BOL;
typedef int32_t SI4;
typedef uint32_t UI4;
typedef int32_t TM4;
typedef int64_t TM8;
typedef int64_t SI8;
typedef uint64_t UI8;

typedef UI2 FP2;
typedef float FP4;
typedef double FP8;

typedef uintptr_t UIW;
typedef intptr_t SIW;

typedef int SIN;
typedef unsigned int UIN;

typedef SI4 TM4;  //< A 32-bit seconds since epoch timestamp.
typedef SI8 TM8;  //< A 64-bit seconds since epoch timestamp.

typedef UI2 UI2;  //< Using unsigned 16-bit hash type.
typedef UI4 UI4;  //< Using unsigned 32-bit hash type.
typedef UI8 UI8;  //< Using unsigned 64-bit hash type.

typedef void* PTR;
typedef const void* PTC;

typedef UIW DTW;  //< Word-sized Ascii Data TYpe.
typedef UI1 DT1;  //< 8-bit Ascii Data TYpe.
typedef UI2 DT2;  //< 16-bit Ascii Data TYpe.
typedef UI4 DT4;  //< 32-bit Ascii Data TYpe.
typedef UI8 DT8;  //< 64-bit Ascii Data TYpe.

typedef DT2 DTP;  //< A 16-bit ASCII Data Type.

/* ASCII C0 Control codes. */
enum {
  kNUL = 0,    //< ASCII C0 NUL 0
  kSOH,        //< ASCII C0 NUL 1
  kSTX,        //< ASCII C0 STX 2
  kETX,        //< ASCII C0 ETX 3
  kEOT,        //< ASCII C0 EOT 4
  kENQ,        //< ASCII C0 ENQ 5
  kACK,        //< ASCII C0 ACK 6
  kBEL,        //< ASCII C0 BEL 7
  kBS,         //< ASCII C0 BS 8
  kTAB,        //< ASCII C0 TAB 9
  kLF,         //< ASCII C0 LF 10
  kVT,         //< ASCII C0 VT 11
  kFF,         //< ASCII C0 FF 12
  kCR,         //< ASCII C0 CR 13
  kSO,         //< ASCII C0 SO 14
  kSI,         //< ASCII C0 SI 15
  kDLE,        //< ASCII C0 DLE 16
  kDC1,        //< ASCII C0 DC1 17
  kDC2,        //< ASCII C0 DC2 18
  kDC3,        //< ASCII C0 DC3 19
  kDC4,        //< ASCII C0 DC4 20
  kNAK,        //< ASCII C0 NAK 21
  kSYN,        //< ASCII C0 SYN 22
  kETB,        //< ASCII C0 ETB 23
  kCAN,        //< ASCII C0 CAN 24
  kEM,         //< ASCII C0 EM 25
  kSUB,        //< ASCII C0 SUB 26
  kESC,        //< ASCII C0 ESC 27
  kFS,         //< ASCII C0 FS 28
  kGS,         //< ASCII C0 GS 29
  kRS,         //< ASCII C0 RS 30
  kUS,         //< ASCII C0 US 31
  kDEL = 127,  //< ASCII C0 DEL 127
  NIL = 0,
};

enum {
  kATypeBitCount = 6,  //< Number of bits required to represent the Core types.
  kWordBitCount = (sizeof(void*) == 2)
                      ? 1
                      : (sizeof(void*) == 4) ? 2 : (sizeof(void*) == 8) ? 3 : 0,
  kWordLSbMask = sizeof(void*) - 1,
  kNaNInt = sizeof(SI4) == 4 ? static_cast<SI4>(0xFFFFFFFF)
                             : sizeof(SI4) == 2 ? static_cast<SI4>(0xFFFF) : 0,
};

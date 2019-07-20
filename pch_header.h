#include <module_seams.h>

#define SCRIPT2 0

#define YES_0 0   //< Logical yes.
#define NZF_NO 1  //< Logical no.

#define STRING_TYPE_1 1
#define STRING_TYPE_2 2
#define STRING_TYPE_3 3

#if SCRIPT2_PLATFORM == OS_WINDOWS
#define APP_EXIT_SUCCESS 0
#define APP_EXIT_FAILURE 1
#else
#define APP_EXIT_SUCCESS 0
#define APP_EXIT_FAILURE 1
#endif

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

#define USING_VISUAL_CPP 1

#define CPU_64_BIT 0
#define CPU_32_BIT 1
#define CPU_16_BIT 2
#define CPU_8_BIT 3

#define CPU_ENDIAN_LITTLE 0

/* Script^2 @version 0.x
@link    https://github.com/kabuki-starship/script2.git
@file    /script2/global_config.inl
@author  Cale McCollough <cale@astartup.net>
@license Copyright (C) 2014-2019 Cale McCollough <calemccollough.github.io>;
All right reserved (R). Licensed under the Apache License, Version 2.0 (the
"License"); you may not use this file except in compliance with the License.
You may obtain a copy of the License at www.apache.org/licenses/LICENSE-2.0.
Unless required by applicable law or agreed to in writing, software distributed
under the License is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
CONDITIONS OF ANY KIND, either express or implied. See the License for the
specific language governing permissions and limitations under the License. */

#pragma once
#ifndef SCRIPT2_GLOBAL_INL
#define SCRIPT2_GLOBAL_INL 1

#include <global_seams.inl>

#define ALU_SIZE 64

#define SDK

#include <climits>
#include <cstdarg>
#include <cstdint>
#include <new>

#define UTF8 1
#define UTF16 2
#define UTF32 4

typedef char CH1;
typedef char16_t CH2;
typedef char32_t CH4;
typedef wchar_t CHW;

typedef int8_t SI1;
typedef uint8_t UI1;
typedef int16_t SI2;
typedef uint16_t UI2;
typedef UI2 FP2;
typedef FP2 FP2;
typedef bool BOL;
typedef int32_t SI4;
typedef uint32_t UI4;
typedef float FP4;
typedef FP4 FP4;
typedef int32_t TM4;
typedef int64_t TM8;
typedef int64_t SI8;
typedef uint64_t UI8;
typedef double FP8;
typedef FP8 FP8;

typedef uintptr_t UIW;
typedef intptr_t SIW;

typedef SI4 SIN;
typedef UI4 UIN;

typedef SI4 TM4;  //< A 32-bit seconds since epoch timestamp.
typedef SI8 TM8;  //< A 64-bit seconds since epoch timestamp.

typedef CH1 CHT;  //< Default Char type.

enum {
  NIL = 0,
  kWordBitCount = (sizeof(void*) == 2)
                      ? 1
                      : (sizeof(void*) == 4) ? 2 : (sizeof(void*) == 8) ? 3 : 0,
  kWordLSbMask = sizeof(void*) - 1,
  kAlignMask = 0x7,
};

#define STRANDFACTORY TStrandFactoryStack
#define STACKFACTORY TStrandFactoryStack
#define ARRAYFACTORY TStrandFactoryStack
#define MAPFACTORY TStrandFactoryStack
#define BOOKFACTORY TStrandFactoryStack
#define DICFACTORY TStrandFactoryStack

#if PLATFORM == WINDOWS
#define APP_EXIT_SUCCESS 0
#define APP_EXIT_FAILURE 1
#else
#define APP_EXIT_SUCCESS 0
#define APP_EXIT_FAILURE 1
#endif

#define ASSERT_FREEZE 0  //< Flag to trigger a crash upon failed DASSERT.
#define ASSERT_LOG \
  0  //< Flag for if to log the failed DASSERT but do not crash.
#define ASSERT_DNC 1  //< Flag for Do Not Care (DNC) upon failed DASSERT.

#define BARE_METAL 1       //< Bare metal (i.e. No OS) OS type macro.
#define BARE_METAL_MBED 2  //< mbed bare-metal OS type macro.
#define MBED_OS 3          //< Arduino bare-metal OS type macro.
#define ARDUINO 4          //< mbed OS type macro.
#define MINGW32 5          //< Win32 OS type macro.
#define WINDOWS 6          //< Slots Universal OS type macro.
#define ANDROID 7          //< Android OS type macro.
#define LINUX 8            //< Linux OS type macro.
#define OSX 9              //< OSX OS type macro.
#define IOS 10             //< iOS OS type macro.

#define X86 1    //< 32-bit x86 processor family macro.
#define X64 2    //< 64-bit x86 processor family macro.
#define ARM8 3   //< ARM8 processor family macro.
#define ARM16 4  //< ARM16 processor family macro.
#define ARM32 5  //< ARM32 processor family macro.
#define ARM64 6  //< ARM64 processor family macro.

#define VISUAL_CPP 1  //< Flag for Visual-C++ compiler.

// Endian nonsense.

#define IS_NOT_STUPID 1
#define IS_STUPID 2  //< Don't ask me what they where thinking.

#define YES 0  //< Logical yes.
#define NO 1   //< Logical no.

// Executable assembly type macro.
#define EXECECUTABLE 1
// Statically linked library assembly type macro.
#define STATICALLY_LINKED_LIBRARY 2
// Dynamically linked library assembly type macro.
#define DYNAMICALLY_LINKED_LIBRARY 3
// Dynamically linked library assembly type macro.
#define SINGLE_DLL 4

// Executable assembly type macro.
#define EXECECUTABLE 1

// Statically linked library assembly type macro.
#define STATICALLY_LINKED_LIBRARY 2

// Dynamically linked library assembly type macro.
#define DYNAMICALLY_LINKED_LIBRARY 3

// Dynamically linked library assembly type macro.
#define SINGLE_DLL 4

#define LARGEST_INT 2147483647  //< Use this for 32-bit CPUs

#endif  //< #ifndef SCRIPT2_GLOBAL_INL

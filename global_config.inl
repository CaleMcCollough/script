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

#ifndef SCRIPT2_GLOBAL_CONFIG_INL
#define SCRIPT2_GLOBAL_CONFIG_INL 1

#if SEAM < SCRIPT2_4
#undef USING_FP4
#undef USING_FP8
#define USING_FP4 NO
#define USING_FP8 NO
#endif

#if USING_UTF == 1
typedef CH1 CHR;
#elif USING_UTF == 2
typedef CH2 CHR;
#elif USING_UTF == 4
typedef CH4 CHR;
#endif

#if SCRIPT2_MAX_PARAMS < 0
#error MAX_ERRORS must be greater than 0
#endif

#if SCRIPT2_TEXT_SIZE_DEFAULT < 0
#error MAX_ERRORS must be greater than 0
#endif

#if COM_TIMEOUT_TICKS < 0
#error MAX_ERRORS must be greater than 0
#endif

#ifndef SCRIPT2_MAX_WALLS
#define SCRIPT2_MAX_WALLS 65535
#endif
#ifndef SCRIPT2_MAX_ERRORS
#define SCRIPT2_MAX_ERRORS 65535
#endif
#ifndef SCRIPT2_MAX_PARAMS
#define SCRIPT2_MAX_PARAMS 65535
#endif
#ifndef COM_TIMEOUT_TICKS
#define COM_TIMEOUT_TICKS 65535
#endif
#ifndef SCRIPT2_MAX_ADDRESS_LENGTH
#define SCRIPT2_MAX_ADDRESS_LENGTH 65535
#endif
#ifndef SCRIPT2_OP_MAX_NAME_LENGTH
#define SCRIPT2_OP_MAX_NAME_LENGTH 65535
#endif
#ifndef SCRIPT2_OP_MAX_DECRABSION_LENGTH
#define SCRIPT2_OP_MAX_DECRABSION_LENGTH 65535
#endif
#ifndef SCRIPT2_TEXT_LENGTH
#define SCRIPT2_TEXT_LENGTH 65535
#endif
#ifndef SCRIPT2_BUFFER_SIZE_RX
#define SCRIPT2_BUFFER_SIZE_RX 65535
#endif
#ifndef SCRIPT2_BUFFER_SIZE_TX
#define SCRIPT2_BUFFER_SIZE_TX 65535
#endif

#ifndef SCRIPT2_WINDOW_SIZE_MIN
#define SCRIPT2_WINDOW_SIZE_MIN 512
#endif
#ifndef SCRIPT2_BUFFER_SIZE_DEFAULT
#define SCRIPT2_BUFFER_SIZE_DEFAULT 64 * 1024
#endif
#ifndef SCRIPT2_STACK_COuNT_MAX_DEFAULT
#define SCRIPT2_STACK_COuNT_MAX_DEFAULT 32
#endif
#ifndef SCRIPT2_FLOOR_SIZE
#define SCRIPT2_FLOOR_SIZE 1024
#endif
#ifndef SCRIPT2_STACK_COUNT_MAX_DEFAULT
#define SCRIPT2_STACK_COUNT_MAX_DEFAULT 16
#endif
#ifndef SCRIPT2_OBJ_SIZE_DEFAULT
#define SCRIPT2_OBJ_SIZE_DEFAULT 256
#endif
#ifndef SCRIPT2_TokenCount
#define SCRIPT2_TokenCount 32
#endif

namespace _ {
enum {
  kMaxFloorsCount = SCRIPT2_MAX_WALLS,  //< Size of the Room Floor (socket).
  kMaxErrors = SCRIPT2_MAX_ERRORS,      //< Max errors before blowing up.
  kParamsMax = SCRIPT2_MAX_PARAMS,      //< Max number_ of parameters.
  kTimeoutMicroseconds = COM_TIMEOUT_TICKS,  //< Timeout time in microseconds.
  kAddressLengthMax =
      SCRIPT2_MAX_ADDRESS_LENGTH,  //< Max address (kADR) length.
  kOpNameLengthMax = SCRIPT2_OP_MAX_NAME_LENGTH,
  // Max length of a Op description .
  kOpDescriptionLengthMax = SCRIPT2_OP_MAX_DECRABSION_LENGTH,
  // Max length of a Text.
  kCharCount = SCRIPT2_TEXT_LENGTH,

  // Size of the Display Print Slot.
  kSlotBufferSizeRx = SCRIPT2_BUFFER_SIZE_RX,

  // Size of the KeyboardInBuffer.
  kSlotBufferSizeTx = SCRIPT2_BUFFER_SIZE_TX,

  kWindowSizeMin = SCRIPT2_WINDOW_SIZE_MIN,

  kBufferSizeDefault = SCRIPT2_BUFFER_SIZE_DEFAULT,
  kFloorSize = SCRIPT2_FLOOR_SIZE,  //< Size, or initial size, of the Floor.
  kStackCountMaxDefault = SCRIPT2_STACK_COUNT_MAX_DEFAULT,
  kObjSizeDefault = SCRIPT2_OBJ_SIZE_DEFAULT,
  kNo = 0,   //< Script no/false value.
  kYes = 1,  //< Script yes/true value.

  // Extra reserved memory at the stop of BOut.
  kBOutOverflowSize = 32,

  kWordAddressMask = kWordLSbMask,  //< For masking the word address.
  kAlignMask = 0x7,
  kPrintC0Offset = 176,  //< Value add to values 0-32 when printing.
  kTokenCount = 32,      //< Max length of a token plus one.
  kMinStackSize = 1,     //< Min CCrabs stack size.
  kBufferSizeDefaultWords =
      kBufferSizeDefault / sizeof(SIW) + kBufferSizeDefault % sizeof(SIW) ? 1
                                                                          : 0,
};

}  // namespace _

#undef MAX_ERRORS
#undef MAX_NUM_PARAMS
#undef MAX_STRING_LENGTH
#undef COM_TIMEOUT_TICKS
#undef SCRIPT2_LOG_SIZE
#undef OPERATION_MAX_NAME_LENGTH
#undef OPERATION_MAX_DECRABSION_LENGTH
#undef SCRIPT2_TEXT_LENGTH
#undef SCRIPT2_BUFFER_SIZE_RX
#undef SCRIPT2_BUFFER_SIZE_TX
#undef SCRIPT2_WINDOW_SIZE_MIN
#undef SCRIPT2_BUFFER_SIZE_DEFAULT
#undef SCRIPT2_STACK_COuNT_MAX_DEFAULT
#undef SCRIPT2_FLOOR_SIZE
#undef SCRIPT2_STACK_COUNT_MAX_DEFAULT
#undef SCRIPT2_OBJ_SIZE_DEFAULT
#undef SCRIPT2_TokenCount

// Pre-compiled headers: comment out those you're not using.

#if ALU_SIZE == 32
typedef FP4 FPW;
#elif ALU_SIZE == 64
typedef FP8 FPW;
#endif

/* This isn't right anymore.
#if MAX_NUM_SLOTS <= 255
typedef UI1 SI4;
enum { kMaxNumSlots = 0xff };
#elif MAX_NUM_SLOTS <= 65535
typedef UI2 SI4;
enum { kMaxNumSlots = 0xffff };
#else
typedef UI4 SI4;
enum { kMaxNumSlots = 0xffffffff };
#endif#if ALU_SIZE == 32
typedef FP4 FPW;
#elif ALU_SIZE == 64
typedef FP8 FPW;
#endif
*/

/* Below are representations of not-a-numbers.
With signed integers, there is one additional negative number_ than positive
numbers due to  the 0. In the CRABS Protocol, this number_ is used to mark
invalid or corrupted data. If you are not using them and require the ROM
space, it will not harm anything to comment them out.

@code
#include <iostream>
#define NaN_int 0xFFFFFFF
void BlowUp () { PRINTF ("The sky is falling!");
if (-1 == NaN_int)
    BlowUp ();
@endcode
*/

// SI4-sized not-a-number_.
enum {
  NaNInt = sizeof(SI4) == 4 ? static_cast<SI4>(0xFFFFFFFF)
                            : sizeof(SI4) == 2 ? static_cast<SI4>(0xFFFF) : 0,
};

typedef UI2 hash16_t;  //< Using unsigned 16-bit hash type.
typedef UI4 hash32_t;  //< Using unsigned 32-bit hash type.
typedef UI8 hash64_t;  //< Using unsigned 64-bit hash type.

enum {
  kLargest16BitPrime = 0xFFE1,      //< Largest 16-bit prime: 65521.
  kLargest32BitPrime = 0xFFFFFFFB,  //< Largest 32-bit prime: 4294967291.
};

static const UI8 kLargest64BitPrime = 0xFFFFFFFFFFFFFFC5;
//< Largest 64-bit prime: 18446744073709551557;

//< A CH1 with a single newline CH1.

/* The level will more code creating a larger binary. Use one
    underscore to use more memory, and two underscores to use even more.
#if SCRIPT2_MEMORY_PROFILE == 1
typedef SI1 int_t;     //< Buffer signed index type.
typedef UI1 SI4;       //< Buffer unsigned index type.
typedef SI2 dint_t;    //< Buffer FP8-wide signed index type.
typedef UI2 duint_t;   //< Buffer FP8-wide unsigned index type.
typedef UI1 index_t;   //< Largest bit-depth TIndex this system supports.
typedef UI2 header_t;  //< Largest bit-depth THeader this system supports.
typedef UI2 data_t;    //< Largest bit-depth TData this system supports.

#elif (SCRIPT2_MEMORY_PROFILE == 2) || (SCRIPT2_MEMORY_PROFILE == 3)
typedef SI2 int_t;     //< Buffer signed index type.
typedef UI2 SI4;       //< Buffer unsigned signed index type.
typedef SI4 dint_t;    //< Buffer FP8-wide signed index type.
typedef UI4 duint_t;   //< Buffer FP8-wide unsigned index type.
typedef SI2 index_t;   //< Default TIndex size.
typedef UI2 header_t;  //< Default TKey size.
typedef UI4 data_t;    //< Default TData size.

#else  // SCRIPT2_MEMORY_PROFILE == 5
typedef UI4 SI4;       //< Buffer unsigned signed index type.
typedef SI2 dint_t;    //< Buffer FP8-wide signed index type.
typedef UI8 duint_t;   //< Buffer FP8-wide unsigned index type.
typedef UI2 index_t;   //< Default TIndex size.
typedef UI4 header_t;  //< Default TKey size.
typedef UI8 data_t;    //< Default TData size.
#endif

#if SCRIPT2_MEMORY_PROFILE >= 3 || DEBUG
#define USING_SCRIPT2_TEXT 3
#endif  //< SCRIPT2_MEMORY_PROFILE >= 3
 */

#endif

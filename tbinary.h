/* Script^2 @version 0.x
@link    https://github.com/kabuki-starship/script2.git
@file    /tbinary.h
@author  Cale McCollough <cale.mccollough@gmail.com>
@license Copyright (C) 2014-2017 Cale McCollough <calemccollough.github.io>;
All right reserved (R). Licensed under the Apache License, Version 2.0 (the
"License"); you may not use this file except in compliance with the License.
You may obtain a copy of the License at www.apache.org/licenses/LICENSE-2.0.
Unless required by applicable law or agreed to in writing, software distributed
under the License is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
CONDITIONS OF ANY KIND, either express or implied. See the License for the
specific language governing permissions and limitations under the License. */

#pragma once
#include <pch.h>

#ifndef INCLUDED_SCRIPTTBINARY
#define INCLUDED_SCRIPTTBINARY 1

#if defined(_MSC_VER) && defined(_M_AMD64)
#include <intrin.h>
#endif

#include "cbinary.h"
#include "csio.h"
#include "csocket.h"

#if SEAM >= _0_0_0__00
#if SEAM == _0_0_0__00
#include "test_debug.inl"
#else
#include "test_release.inl"
#endif
namespace _ {
template <typename Char>
void TPrintString(const Char* string) {
  if (!string) return;
  Char c = *string;
  while (c) {
    Print(c);
    c = *(++string);
  }
}

/* Compares the two strings up to the given delimiter.
@return int 0 if the strings are equal or a non-zero delta upon failure.
@param  string_a String A.
@param  string_b String B.
@param  delimiter The delimiter.*/
template <typename Char = char>
int TStringCompare(const Char* string_a, const Char* string_b,
                   Char delimiter = 0) {
  int a, b, result;
  if (!string_a) {
    if (!string_b) return 0;
    return *string_a;
  }
  if (!string_b) return 0 - *string_a;

  PRINTF("\nComparing \"%s\" to \"%s\"", string_a, string_b);
  a = *string_a;
  b = *string_b;
  if (!a) {
    if (!b) return 0;
    return b;
  }
  if (!b) {
    if (!a) return 0;  //< I like !t code rather than !c code. :-)
    return 0 - a;
  }
  // string_b SHOULD be a nil-terminated string without whitespace.
  while (b) {
    result = b - a;
    if (result) {
      PRINTF(" is not a hit.");
      return result;
    }
    if (a <= (int)delimiter) {
      PRINTF(" is a partial match but a reached a delimiter first.");
      return result;
    }
    ++string_a;
    ++string_b;
    a = *string_a;
    b = *string_b;
  }
  if (a > (int)delimiter) {
    PRINTF(" is only a partial match but b reached a delimiter first.");
    return b - a;
  }
  return 0;
}
}  // namespace _

#endif

#if SEAM >= _0_0_0__01
#if SEAM == _0_0_0__01
#include "test_debug.inl"
#define BEGIN_ITOS_ALGORITHM                                          \
  static const char* ui_format = sizeof(UI) == 8 ? FORMAT_UI8 : "%u"; \
  TPuffItoSBegin<Char>(cursor);                                       \
  for (SI4 i = 0; i < 10; ++i) *(cursor + i) = 'x';                   \
  *(cursor + 21) = 0;                                                 \
  enum { kSize = 256 };                                               \
  char buffer[kSize];                                                 \
  sprintf_s(buffer, kSize, ui_format, value);                         \
  Printf(" Expecting %s:%i ", buffer, TStringLength<Char>(buffer))
#define PRINT_PRINTED TPrintPrinted<Char>(TPuffItoSBegin<Char>())
#else
#include "test_release.inl"
#define BEGIN_ITOS_ALGORITHM
#define PRINT_PRINTED
#endif

namespace _ {

template <typename Char>
SIW TPrintAndCount(const Char* string) {
  if (!string) return 0;
  int print_count = 0;
  Char c = *string;
  while (c) {
    Print(c);
    ++print_count;
    c = *(++string);
  }
  return print_count;
}

template <typename Char>
Char* TPuffItoSBegin(Char* cursor = nullptr) {
  static Char* buffer_begin = 0;
  if (cursor) {
    buffer_begin = cursor;
    return cursor;
  }
  return buffer_begin;
}

template <typename Char>
void TPrintPrinted(Char* cursor) {
  Print("\n    Printed \"");
  SIW print_count = TPrintAndCount<Char>(TPuffItoSBegin<Char>());
  Print('\"', ':');
  Print(print_count);
}

template <typename UI>
inline UI TNaNUnsigned() {
  return ~0;
}

template <typename SI, typename UI>
inline SI TNaNSigned() {
  return (SI)(((UI)1) << (sizeof(SI) * 8 - 1));
}

/* Scrolls over to the next DBL quote mark.
@warning This function is only safe to use on ROM strings with a nil-term
char. */
template <typename Char = char>
inline const Char* TStringEnd(const Char* cursor, Char delimiter = 0) {
  ASSERT(cursor);
  while (*cursor++ != delimiter)
    ;
  return cursor - 1;
}

/* Gets the length of the given char.
@return  Returns -1 if the text char is nil.
@warning This function is only safe to use on ROM strings with a nil-term
char. */
template <typename Char, typename I = int>
I TStringLength(const Char* cursor) {
  ASSERT(cursor);
  return (I)(TStringEnd<Char>(cursor) - cursor);
}

/* Prints a Unicode string to the given buffer.
 @return Nil upon failure or a pointer to the nil-term Char upon success.
 @param  cursor    The beginning of the buffer.
 @param  end       The last UI1 in the buffer.
 @param  string    The string to print.
 @param  delimiter The delimiter to print (usually nil).
 @desc   This algorithm is designed to fail if the buffer is not a valid buffer
 with one or more bytes in it, or if string is nil. */
template <typename Char = char>
Char* TPrint(Char* cursor, Char* end, const Char* string, Char delimiter = 0) {
  ASSERT(cursor);
  ASSERT(string);

  if (cursor >= end) return nullptr;

  char c = *string++;
  while (c) {
    *cursor++ = c;
    if (cursor >= end) return nullptr;
    c = *string++;
  }
  *cursor = delimiter;
  return cursor;
}

/* Prints a Unicode string to the given buffer.
@return Nil upon failure or a pointer to the nil-term Char upon success.
@param  cursor    The beginning of the buffer.
@param  size      The size of the buffer in Char(s).
@param  string    The string to print.
@param  delimiter The delimiter to print (usually nil).
@desc   This algorithm is designed to fail if the buffer is not a valid buffer
with one or more bytes in it, or if string is nil. */
template <typename Char = char>
Char* TPrint(Char* cursor, SIW size, const Char* string, Char delimiter = 0) {
  return TPrint<Char>(cursor, cursor + size - 1, string, delimiter);
}

/* Prints a Unicode Char to the given buffer.
@return Nil upon failure or a pointer to the nil-term Char upon success.
@param  cursor    The beginning of the buffer.
@param  end       The last UI1 in the buffer.
@param  character The Char to print.
@desc   This algorithm is designed to fail if the buffer is not a valid buffer
with one or more bytes in it. */
template <typename Char = char>
Char* TPrint(Char* cursor, Char* end, Char character) {
  ASSERT(cursor);
  ASSERT(cursor < end);

  if (cursor + 1 >= end) return nullptr;

  *cursor++ = character;
  *cursor = 0;
  return cursor;
}

/* Prints a Unicode Char to the given buffer.
@return Nil upon failure or a pointer to the nil-term Char upon success.
@param  cursor    The beginning of the buffer.
@param  size      The size of the buffer in Char(s).
@param  string    The string to print.
@desc   This algorithm is designed to fail if the buffer is not a valid buffer
with one or more bytes in it. */
template <typename Char = char>
Char* TPrint(Char* cursor, SIW size, Char character) {
  return TPrint<Char>(cursor, cursor + size, character);
}

/* Prints a Unicode Char to the given buffer.
@return Nil upon failure or a pointer to the nil-term Char upon success.
@param  cursor    The beginning of the buffer.
@param  size      The size of the buffer in Char(s).
@param  character The Char to print.
@desc   This algorithm is designed to fail if the buffer is not a valid buffer
with one or more bytes in it. */
template <typename Char = char>
Char* TPrintChar(Char* cursor, SIW size, Char character) {
  return TPrintChar<Char>(cursor, cursor + size, character);
}

/* Prints a hex value to the Console. */
template <typename Char, typename UI>
Char* TPrintHex(Char* cursor, Char* end, UI value) {
  enum { kHexStringLengthSizeMax = sizeof(UI) * 2 + 3 };

  ASSERT(cursor);
  if (cursor + kHexStringLengthSizeMax >= end) return nullptr;

  *cursor++ = '0';
  *cursor++ = 'x';
  for (int num_bits_shift = sizeof(UI) * 8 - 4; num_bits_shift >= 0;
       num_bits_shift -= 4) {
    *cursor++ = HexNibbleToUpperCase((UI1)(value >> num_bits_shift));
  }
  *cursor = 0;
  return cursor;
}

/* Prints the given value to Binary. */
template <typename Char, typename T>
Char* TPrintBinary(Char* cursor, Char* end, T value) {
  if (cursor + sizeof(UI8) * 8 >= end) {
    return nullptr;
  }

  for (int i = 0; i < sizeof(T) * 8; ++i) {
    *cursor++ = (char)('0' + (value >> (sizeof(T) * 8 - 1)));
    value = value << 1;
  }
  *cursor = 0;
  return cursor;
}

/* Checks if the given character is whitespace. */
template <typename Char = char>
inline BOL TIsWhitespace(Char character) {
  return character <= ' ';
}

/* Prints a single decimal to the buffer.
@warning This function DOES NOT do any error checking and if the SEAM ==
_0_0_0 (1), then this function will print debug data. */
template <typename Char = char>
inline Char* TPrintDecimal(Char* buffer, Char value) {
  *reinterpret_cast<Char*>(buffer) = '0' + value;
  PRINT_PRINTED;
  return buffer;
}

/* Prints a single decimal to the buffer.
If the SEAM == _0_0_0 (1), then this function will print debug data.
@warning This function DOES NOT do any error checking! */
template <typename Char = char>
inline Char* TPrintChar(Char* buffer, Char value) {
  *buffer++ = value;
  PRINT_PRINTED;
  return buffer;
}

/* Prints a single decimal to the buffer.
If the SEAM == _0_0_0 (1), then this function will print debug data.
@warning This function DOES NOT do any error checking! */
template <typename Char = char>
inline Char* TPrintChar(Char* buffer, Char* end, Char value) {
  if (!buffer || buffer >= end) return nullptr;
  *buffer++ = value;
  PRINT_PRINTED;
  return buffer;
}

inline char* PrintChar(char* cursor, char c) {
  return TPrintChar<char>(cursor, c);
}

inline char16_t* PrintChar(char16_t* cursor, char16_t c) {
  TPrintChar<char16_t>(cursor, c);
}

inline char32_t* PrintChar(char32_t* cursor, char32_t c) {
  TPrintChar<char32_t>(cursor, c);
}

/* Checks if the given char is a digit of a number.
@return True if it is a digit. */
template <typename Char = char>
BOL TIsDigit(Char c) {
  return (c >= '0') && (c <= '9');
}

/* Scans the given buffer for an unsigned integer (UI).
@return Nil if there is no UI to scan.
@param buffer The beginning of the buffer.
@param result The UI to write the scanned UI. */
template <typename UI, typename Char = char>
const Char* TScanUnsigned(const Char* buffer, UI& result) {
  ASSERT(buffer);
  PRINTF("\nScanning unsigned value:%s", buffer);
  const Char* cursor = buffer;
  Char c = *cursor++;
  if (!TIsDigit<Char>(c)) return nullptr;

  // Find length:
  c = *cursor++;
  while (TIsDigit<Char>(c)) c = *cursor++;
  const Char* end = cursor;  // Store end to return.
  cursor -= 2;
  PRINTF("\nPointed at \'%c\' and found length:%i", *cursor,
         (SI4)(cursor - buffer));

  c = *cursor--;
  UI value = (UI)(c - '0');
  UI pow_10_ui2 = 1;

  while (cursor >= buffer) {
    c = *cursor--;
    pow_10_ui2 *= 10;
    UI new_value = value + pow_10_ui2 * (c - '0');
    if (new_value < value) return nullptr;
    value = new_value;
    PRINTF("\nvalue:%u", (uint)value);
  }
  PRINTF("\nvalue:%u", (uint)value);
  result = value;
  return end;
}

/* Prints two chars to the console.
@warning This function DOES NOT do any error checking! */
template <typename Char = char>
inline Char* TPrintNil(Char* cursor) {
  *cursor = 0;
  return cursor;
}

/* Prints a two decimals to the buffer.
If the SEAM == _0_0_0 (1), then this function will print debug data.
@warning This function DOES NOT do any error checking! */
template <typename Char = char>
inline Char* TPrint2Decimals(Char* buffer, UI2 decimal_pair) {
  enum { kSizeBits = sizeof(Char) * 8 };
  buffer[0] = (Char)(decimal_pair >> 8);
  char c = (char)decimal_pair;
  buffer[1] = (Char)(c);
  PRINT_PRINTED;
  return buffer;
}

inline char* PrintCharPair(char* buffer, UI2 value) {
#if ALIGN_MEMORY
  buffer[0] = (char)(value >> 8);
  buffer[1] = (char)(value);
#else
  *((UI2*)buffer) = value;
#endif
  using Char = char;
  PRINT_PRINTED;
  return buffer;
}

inline char16_t* PrintCharPair(char16_t* cursor, UI2 decimal_pair) {
  return TPrint2Decimals<char16_t>(cursor, decimal_pair);
}

inline char32_t* PrintCharPair(char32_t* cursor, UI2 decimal_pair) {
  return TPrint2Decimals<char32_t>(cursor, decimal_pair);
}

/* Prints 8 decimals to the given buffer with given LUT.*/
template <typename Char = char>
Char* TPrint8Decimals(Char* cursor, UI4 value, const UI2* lut) {
  PRINT("\n    Printing 8 decimals:");
  PRINT(value);
  UI2 pow_10_ui2 = 10000, digits6and5 = (UI2)(value / pow_10_ui2),
      digits2and1 = value - pow_10_ui2 * digits6and5;
  pow_10_ui2 = 100;
  UI2 digits8and7 = digits6and5 / pow_10_ui2,
      digits4and3 = digits2and1 / pow_10_ui2;
  digits6and5 -= pow_10_ui2 * digits8and7;
  digits2and1 -= pow_10_ui2 * digits4and3;
  PrintCharPair(cursor, lut[digits8and7]);
  PrintCharPair(cursor + 2, lut[digits6and5]);
  PrintCharPair(cursor + 4, lut[digits4and3]);
  PrintCharPair(cursor + 6, lut[digits2and1]);
  PRINT_PRINTED;
  return cursor + 8;
}

template <typename Char = char>
inline void TPrint8or16Decimals(Char* cursor, UI4 lsd, const UI2* lut,
                                UI4 middle_sd, UI4 delta) {
  if (delta == 8) {
    PRINTF("\n    Printing less than 17 decimals:");
    TPrint8Decimals<Char>(cursor, lsd, lut);
  } else {
    PRINTF("\n    Printing more than 16 decimals:");
    TPrint8Decimals<Char>(cursor, middle_sd, lut);
    TPrint8Decimals<Char>(cursor + 8, lsd, lut);
  }
}

inline UI4 ValueUI4(UI4 value) { return value; }
inline UI4 ValueUI4(UI8 value) { return (UI4)value; }

/* Prints the give value to the given buffer as a Unicode string.
@return Nil upon buffer overflow and a pointer to the nil-term Char upon
success.
@param  cursor The beginning of the buffer.
@param  end    The end address of the buffer. */
template <typename UI = UI8, typename Char = char>
Char* TPrintUnsigned(Char* cursor, Char* end, UI value) {
  BEGIN_ITOS_ALGORITHM;

  if (!cursor || cursor >= end) return nullptr;

  Char* nil_ptr;
  UI2 pow_10_ui2, delta = 0;
  UI4 pow_10_ui4;
  const UI2* lut = BinaryLUTDecimals();

  // The best way to understand how the numbers are getting converted is that
  // numbers get broken up into up to 8 pairs of 100, in each pair of 10000
  // there will be a Most Significant Decimal (MSD) pair and a Least
  // Significant Decimal (LSD) pair. The digits2and1 and digits6and5 will
  // always be the LSD and digits4and3 and digits8and7 will always be the MSD.

  if (value < 10) {
    PRINT("\n    Range:[0, 9] length:1 ");
  Print1:
    nil_ptr = cursor + delta + 1;
    if (nil_ptr >= end) return nullptr;
    TPrintDecimal<Char>(cursor, (Char)value);
    return TPrintNil<Char>(cursor + delta + 1);
  } else if (value < 100) {
  Print2:
    PRINT("\n    Range:[10, 99] length:2 ");
    nil_ptr = cursor + delta + 2;
    if (cursor + delta + 2 >= end) return nullptr;
    PrintCharPair(cursor, lut[value]);
    return TPrintNil<Char>(cursor + delta + 2);
  } else {
    if ((value >> 10) == 0) {
      pow_10_ui2 = 1000;
      if (value >= pow_10_ui2) {
      Print4A:
        PRINT("\n    Range:[1000, 1023] length:4");
        nil_ptr = cursor + delta + 4;
        if (nil_ptr >= end) return nullptr;
        UI2 digits2and1 = (UI2)(value - pow_10_ui2);
#if CPU_ENDIAN == LITTLE_ENDIAN
        cursor[0] = '1';
        cursor[1] = '0';
#else
        cursor[0] = '0';
        cursor[1] = '1';
#endif
        PrintCharPair(cursor + 2, lut[digits2and1]);
        return TPrintNil<Char>(nil_ptr);
      }
    Print3:
      PRINT("\n    Range:[100, 999] length:3");
      nil_ptr = cursor + delta + 3;
      if (nil_ptr >= end) return nullptr;
      UI2 digits2and1 = (UI2)value, pow_10_ui2 = 100;
      Char digit = (Char)(digits2and1 / pow_10_ui2);
      digits2and1 -= digit * pow_10_ui2;
      TPrintDecimal<Char>(cursor, digit);
      PrintCharPair(cursor + 1, lut[digits2and1]);
      return TPrintNil<Char>(nil_ptr);
    } else if ((value >> 14) == 0) {
      pow_10_ui2 = 10000;
      if (value >= pow_10_ui2) {
      Print5A:
        PRINT("\n    Range:[10000, 16383] length:5");
        nil_ptr = cursor + delta + 5;
        if (nil_ptr >= end) return nullptr;
        cursor = TPrintChar<Char>(cursor, '1');
        value -= pow_10_ui2;
      } else {
      Print4:
        PRINT("\n    Range:[1024, 9999] length:4");
        nil_ptr = cursor + delta + 4;
        if (nil_ptr >= end) return nullptr;
        TPrintNil<Char>(nil_ptr);
      }
      pow_10_ui2 = 100;
      UI2 digits2and1 = (UI2)value, digits4and3 = digits2and1 / pow_10_ui2;
      digits2and1 -= digits4and3 * pow_10_ui2;
      PrintCharPair(cursor, lut[digits4and3]);
      PrintCharPair(cursor + 2, lut[digits2and1]);
      return TPrintNil<Char>(nil_ptr);
    } else if ((value >> 17) == 0) {
      if (value >= 100000) {
      Print6A:
        PRINT("\n    Range:[65536, 131071] length:6");
        goto Print6;
      }
    Print5:
      PRINT("\n    Range:[10000, 65535] length:5");
      nil_ptr = cursor + delta + 5;
      if (nil_ptr >= end) return nullptr;
      UI4 value_ui4 = ValueUI4(value);
      pow_10_ui2 = 10000;
      Char digit6 = (UI1)(value_ui4 / pow_10_ui2);
      value_ui4 -= pow_10_ui2 * digit6;
      cursor = TPrintChar<Char>(cursor, '0' + digit6);
      pow_10_ui2 = 100;
      UI2 digits4and3 = ((UI2)value_ui4) / pow_10_ui2,
          digits2and1 = (UI2)(value_ui4 - digits4and3 * pow_10_ui2);
      PrintCharPair(cursor, lut[digits4and3]);
      PrintCharPair(cursor + 2, lut[digits2and1]);
      return TPrintNil<Char>(nil_ptr);
    } else if ((value >> 20) == 0) {
      pow_10_ui4 = 1000000;
      if (value >= pow_10_ui4) {
      Print7A:
        PRINT("\n    Range:[100000, 1048575] length:7");
        nil_ptr = cursor + delta + 7;
        if (nil_ptr >= end) return nullptr;
        cursor = PrintChar(cursor, '1');
        value -= pow_10_ui4;
      } else {
      Print6:
        PRINT("\n    Range:[131072, 999999] length:6");
        nil_ptr = cursor + delta + 6;
        if (nil_ptr >= end) return nullptr;
        TPrintNil<Char>(nil_ptr);
      }
      UI4 value_ui4 = (UI4)value;
      pow_10_ui2 = 10000;
      UI2 digits6and5 = (UI2)(value_ui4 / pow_10_ui2),
          digits2and1 = value_ui4 - pow_10_ui2 * digits6and5;
      pow_10_ui2 = 100;
      UI2 digits8and7 = digits6and5 / pow_10_ui2,
          digits4and3 = digits2and1 / pow_10_ui2;
      digits6and5 -= pow_10_ui2 * digits8and7;
      digits2and1 -= pow_10_ui2 * digits4and3;
      PrintCharPair(cursor, lut[digits6and5]);
      PrintCharPair(cursor + 2, lut[digits4and3]);
      PrintCharPair(cursor + 4, lut[digits2and1]);
      return nil_ptr;
    } else if ((value >> 24) == 0) {
      pow_10_ui4 = 10000000;  //< 10^7
      if (value >= pow_10_ui4) {
        PRINT("\n    Range:[10000000, 16777216] length:8");
        return TPrint8Decimals<Char>(cursor, ValueUI4(value), lut);
      }
    Print7:
      PRINT("\n    Range:[1048576, 9999999] length:7");
      nil_ptr = cursor + delta + 7;
      if (nil_ptr >= end) return nullptr;
      UI2 pow_10_ui2 = 10000;
      UI4 value_ui4 = ValueUI4(value);
      UI2 digits6and5 = value_ui4 / pow_10_ui2,
          digits2and1 = value_ui4 - pow_10_ui2 * digits6and5;
      pow_10_ui2 = 100;
      UI2 digit7 = digits6and5 / pow_10_ui2,
          digits4and3 = digits2and1 / pow_10_ui2;
      digits6and5 -= pow_10_ui2 * digit7;
      digits2and1 -= pow_10_ui2 * digits4and3;
      TPrintDecimal(cursor, (Char)(digit7));
      PrintCharPair(cursor + 1, lut[digits6and5]);
      PrintCharPair(cursor + 3, lut[digits4and3]);
      PrintCharPair(cursor + 5, lut[digits2and1]);
      return TPrintNil<Char>(nil_ptr);
    } else {
      UI4 comparator = 100000000;  // 10^8
      UI msd = (value >= (~(UI4)0)) ? value / comparator
                                    : ValueUI4(value) / comparator;
      UI4 lsd = (UI4)(value - comparator * msd), middle_sd;
      if (msd >= comparator) {
        delta = 16;
        value = msd / comparator;
        middle_sd = ValueUI4(msd - value * comparator);
        PRINT(value);
        PRINT('_');
        PRINT(middle_sd);
        PRINT('_');
        PRINT(lsd);
      } else {
        value = msd;
        middle_sd = 0;
        delta = 8;
        PRINT(value);
        PRINT('_');
        PRINT(lsd);
      }
      if (value < 10) {
        TPrint8or16Decimals<Char>(cursor + 1, lsd, lut, middle_sd, delta);
        goto Print1;
      } else if (value < 100) {
        TPrint8or16Decimals<Char>(cursor + 2, lsd, lut, middle_sd, delta);
        goto Print2;
      }
      if ((value >> 10) == 0) {
        pow_10_ui2 = 1000;
        if (value >= pow_10_ui2) {
          TPrint8or16Decimals<Char>(cursor + 4, lsd, lut, middle_sd, delta);
          goto Print4A;
        }
        TPrint8or16Decimals<Char>(cursor + 3, lsd, lut, middle_sd, delta);
        goto Print3;
      } else if ((value >> 13) == 0) {
        pow_10_ui2 = 10000;
        if (value >= pow_10_ui2) {
          TPrint8or16Decimals<Char>(cursor + 5, lsd, lut, middle_sd, delta);
          goto Print5A;
        }
        TPrint8or16Decimals<Char>(cursor + 4, lsd, lut, middle_sd, delta);
        goto Print4;
      } else if ((value >> 17) == 0) {
        pow_10_ui4 = 100000;
        if (value >= pow_10_ui4) {
          TPrint8or16Decimals<Char>(cursor + 6, lsd, lut, middle_sd, delta);
          goto Print6A;
        }
        TPrint8or16Decimals<Char>(cursor + 5, lsd, lut, middle_sd, delta);
        goto Print5;
      } else if ((value >> 20) == 0) {
        pow_10_ui4 = 1000000;
        if (value >= pow_10_ui4) {
          TPrint8or16Decimals<Char>(cursor + 7, lsd, lut, middle_sd, delta);
          goto Print7A;
        }
        TPrint8or16Decimals<Char>(cursor + 6, lsd, lut, middle_sd, delta);
        goto Print6;
      } else {
        comparator = 10000000;
        if (value >= comparator) {
          TPrint8Decimals<Char>(cursor, ValueUI4(value), lut);
          TPrint8Decimals<Char>(cursor + 8, lsd, lut);
          return TPrintNil<Char>(cursor + 16);
        }
        TPrint8or16Decimals<Char>(cursor + 7, lsd, lut, middle_sd, delta);
        goto Print7;
      }
    }
  }
  return nullptr;  //< Unreachable.
}

template <typename UI = UI8, typename Char = char>
inline Char* TPrintUnsigned(Char* buffer, int size, UI value) {
  return TPrintUnsigned<UI, Char>(buffer, buffer + size - 1, value);
}

/* Writes the give value to the given buffer as an ASCII string.
@return Nil upon buffer overflow and a pointer to the nil-term Char upon
success.
@param  print The text formatter to print to.
@param value The value to write. */
template <typename SI = SI8, typename UI = UI8, typename Char = char>
inline Char* TPrintSigned(Char* buffer, Char* end, SI value) {
  if (value >= 0) {
    return TPrintUnsigned<UI, Char>(buffer, end, (UI)value);
  }
  *buffer++ = '-';
  return TPrintUnsigned<UI, Char>(buffer, end, (UI)(-(SI)value));
}

/* Writes the give value to the given buffer as an ASCII string.
@return Nil upon buffer overflow and a pointer to the nil-term Char upon
success.
@param  print The text formatter to print to.
@param value The value to write. */
template <typename SI = SI8, typename UI = UI8, typename Char = char>
inline Char* TPrintSigned(Char* buffer, int size, SI value) {
  return TPrintSigned<SI, UI, Char>(buffer, buffer + size - 1, value);
}

/* Scans the given buffer for an Signed Integer (SI).
@return Nil if there is no UI to scan.
@param buffer The beginning of the buffer.
@param result The SI to write the scanned SI. */
template <typename SI = SIW, typename UI = UIW, typename Char>
const Char* TScanSigned(const Char* buffer, SI& result) {
  ASSERT(buffer);
  SI sign;
  const Char* cursor = buffer;
  Char c = *cursor++;
  if (c == '-') {
    PRINTF("\nScanning negative backwards:\"");
    c = *buffer++;
    sign = -1;
  } else {
    PRINTF("\nScanning positive backwards:\"");
    sign = 1;
  }
  if (!TIsDigit<Char>(c)) return nullptr;

  // Find length:
  c = *cursor++;
  while (TIsDigit<Char>(c)) c = *cursor++;
  const Char* end = cursor;  // Store end to return.
  cursor -= 2;
  PRINTF("\nPointed at \'%c\' and found length:%i", *cursor,
         (SI4)(cursor - buffer));

  c = *cursor--;
  UI value = (UI)(c - '0');
  UI pow_10_ui2 = 1;

  while (cursor >= buffer) {
    c = *cursor--;
    pow_10_ui2 *= 10;
    UI new_value = value + pow_10_ui2 * (c - '0');
    if (new_value < value) return nullptr;
    value = new_value;
    PRINTF("\nvalue:%u", (uint)value);
  }
  result = sign * value;
  return end;
}

}  // namespace _
#endif  //< #if SEAM >= _0_0_0__01

#if SEAM >= _0_0_0__03
#if SEAM == _0_0_0__03
#include "test_debug.inl"
#define PRINT_FLOAT_BINARY(integer, decimals, decimal_count) \
  Print("\nBinary:\"");                                      \
  TPrintBinary(value);                                       \
  Print('\n')
#else
#include "test_release.inl"
#define PRINT_FLOAT_BINARY(integer, decimals, decimal_count)
#endif
namespace _ {

template <typename Char = const char>
const Char* TStringDecimalEnd(const Char* cursor) {
  if (!cursor) return cursor;
  Char c = *cursor++;
  if (c == '-') c = *cursor++;
  if (c < '0' || c > '9') return nullptr;
  c = *cursor++;
  while (TIsDigit<Char>(c)) {
    c = *cursor++;
    if (c <= 0) return cursor - 1;
  }
  return cursor - 1;
}

template <typename Char = const char>
Char* TStringDecimalEnd(Char* cursor) {
  return const_cast<Char*>(
      TStringDecimalEnd<Char>(reinterpret_cast<const Char*>(cursor)));
}

/* Searches for the highest MSb asserted.
@return -1 */
template <typename UI>
int TMSbAssertedReverse(UI value) {
  for (int i = sizeof(UI) * 8 - 1; i > 0; --i)
    if ((value >> i) != 0) return i;
  return -1;
}

template <typename Char>
Char* TPrint3(Char* buffer, Char* end, Char a, Char b, Char c) {
  if (!buffer || buffer + 3 >= end) return nullptr;
  *buffer++ = a;
  *buffer++ = b;
  *buffer++ = c;
}

/* A decimal number in floating-point format. */
template <typename Float = DBL, typename UI = UI8>
class TBinary {
 public:
  static int Foo() { return 1; }

  enum {
    kSize = sizeof(Float),
    kSizeBits = kSize * 8,
    kMSbIndex = kSizeBits - 1,
    kStringLengthMax = 24,
    kExponentSizeBits =
        (sizeof(Float) == 2)
            ? 5
            : (sizeof(Float) == 4) ? 8 : (sizeof(Float) == 8) ? 11 : 15,
    kCoefficientSize = kSizeBits - kExponentSizeBits - 1,
    kMantissaSize = kSizeBits - kExponentSizeBits - 2,
    kExponentMaskUnshifted = (~((UI)0)) >> (kSizeBits - kExponentSizeBits),
    kExponentBias = kExponentMaskUnshifted + kCoefficientSize,
    kExponentMin = -kExponentBias,
  };

  // Constructs an uninitialized floating-point number.
  TBinary() {}

  inline static UI Coefficient(UI decimal) {
    return (decimal << (kExponentSizeBits + 1)) >> (kExponentSizeBits + 1);
  }

  // Converts a Float to a TBinary
  TBinary(Float binary) {
    UI ui = *reinterpret_cast<UI*>(&binary);
    UI4 biased_e = (UI4)(ui << 1);  //< Get rid of sign bit.
    // Get rid of the integral portion.
    biased_e = biased_e >> (kSizeBits - kExponentSizeBits);
    // Get rid of the sign and exponent.
    UI8 coefficient = Coefficient(binary);
    if (biased_e != 0) {
      f = coefficient + (((UI)1) << kExponentSizeBits);
      e = biased_e - kExponentBias;
    } else {
      f = coefficient;
      e = kExponentMin + 1;
    }
  }

  TBinary(UI f, SI4 e) : f(f), e(e) {}

  TBinary(const TBinary a, const TBinary b) {}

  inline static UI Exponent(UI decimal) {
    return (decimal << (kExponentSizeBits + 1)) >> (kExponentSizeBits + 1);
  }

  template <typename Char = char>
  static Char* Print(Char* buffer, Char* end, Float value) {
    // Not handling NaN and inf
    if (IsNaN(value)) {
      if (end - buffer < 4) return nullptr;
      buffer[0] = 'N';
      buffer[1] = 'a';
      buffer[2] = 'N';
      buffer[3] = 0;
      return buffer + 4;
    }
    if (IsInfinite(value)) {
      if (end - buffer < 4) return nullptr;
      UI f = *reinterpret_cast<UI*>(&value);
      buffer[0] = (f >> (sizeof(UI) * 8 - 1)) ? '-' : '+';
      buffer[1] = 'i';
      buffer[2] = 'n';
      buffer[3] = 'f';
      buffer[4] = 0;
      return buffer + 5;
    }

    if (value == 0) {
      return TPrint3<Char>(buffer, end, (Char)'0', (Char)'.', (Char)'0');
    }
    if (value < 0) {
      *buffer++ = '-';
      value = -value;
    }
    SI4 k;
    Char* cursor = TPrint<Char>(buffer, end, value, k);
    if (!cursor) return cursor;
    return Standardize<Char>(buffer, end, cursor - buffer, k);
  }

  template <typename UI = UIW>
  static inline UI NaNUnsigned() {
    UI nan = 0;
    return ~nan;
  }

  template <typename SI, typename UI>
  static inline SI TNaNSigned() {
    UI nan = 1;
    return (SI)(nan << (sizeof(UI) * 8 - 1));
  }

  static TBinary IEEE754Pow10(SI4 e, SI4& k) {
    // SI4 k = static_cast<SI4>(ceil((-61 - e) *
    // 0.30102999566398114))

    // + 374; dk must be positive to perform ceiling function on positive
    // values.
    Float dk = (-61 - e) * 0.30102999566398114 + 347;
    k = static_cast<SI4>(dk);
    if (k != dk) ++k;

    UI4 index = static_cast<UI4>((k >> 3) + 1);

    k = -(-348 + static_cast<SI4>(index << 3));
    // decimal exponent no need lookup table.

    ASSERT(index < 87);

    // Save exponents pointer and offset to avoid creating base pointer again.
    return TBinary(BinaryLUTF()[index], BinaryLUTE()[index]);
  }

 private:
  UI f;
  SI4 e;

  static inline void Multiply(TBinary& result, TBinary& a, TBinary& b) {}

  template <typename Char>
  static Char* Print(Char* buffer, Char* end, Float value, SI4& k) {
    TBinary v(value);
    TBinary lower_estimate, upper_estimate;
    v.NormalizedBoundaries(lower_estimate, upper_estimate);

    TBinary c_mk = IEEE754Pow10(upper_estimate.e, k);

    TBinary W(v.NormalizeBoundary(), c_mk);
    TBinary w_plus(upper_estimate, c_mk), w_minus(lower_estimate, c_mk);
    w_minus.f++;
    w_plus.f--;
    return DigitGen<Char>(buffer, end, W, w_plus, w_plus.f - w_minus.f, k);
  }

  TBinary NormalizeBoundary() const {
    // int msba = MSbAsserted(0);
#if defined(_MSC_VER) && defined(_M_AMD64)
    unsigned long index;  //< This is Microsoft's fault.
    _BitScanReverse64(&index, f);
    return TBinary(f << (kMSbIndex - index), e - (kMSbIndex - index));
#else
    TBinary res = *this;
    UI kDpHiddenBit = ((UI)1) << kMantissaSize;  // 0x0010000000000000;
    while (!(res.f & (kDpHiddenBit << 1))) {
      res.f <<= 1;
      --res.e;
    }
    res.f <<= (kDiySignificandSize - kCoefficientSize - 2);
    res.e = res.e - (kDiySignificandSize - kCoefficientSize - 2);
    return res;
#endif
  }

  // static const UI8  kDpExponentMask = 0x7FF0000000000000,
  //   kDpSignificandMask = 0x000FFFFFFFFFFFFF,

  // Normalizes the boundaries.
  void NormalizedBoundaries(TBinary& m_minus, TBinary& m_plus) const {
    UI l_f,   //< Local copy of f.
        l_e;  //< Local copy of e.
    TBinary pl = TBinary((l_f << 1) + 1, ((SI4)l_e) - 1).NormalizeBoundary();
    const UI8 kHiddenBit = ((UI8)1) << kMantissaSize;  //< 0x0010000000000000
    TBinary mi = (f == kHiddenBit) ? TBinary((l_f << 2) - 1, e - 2)
                                   : TBinary((l_f << 1) - 1, e - 1);
    mi.f <<= mi.e - pl.e;
    mi.e = pl.e;
    m_plus = pl;
    m_minus = mi;
  }

  // Rounds the Grisu estimation closer to the inside of the squeeze.
  template <typename Char>
  static void Round(Char& lsd, UI delta, UI rest, UI ten_kappa, UI wp_w) {
    while (rest < wp_w && (delta - rest) >= ten_kappa &&
           (rest + ten_kappa < wp_w ||  /// closer
            (wp_w - rest) > (rest + ten_kappa - wp_w))) {
      --lsd;
      rest += ten_kappa;
    }
  }

  // Prints the integer portion of the floating-point number.
  //@return Nil upon failure or a pointer to the nil-term Char upon success.
  template <typename Char>
  static Char* DigitGen(Char* cursor, Char* end, const TBinary& w,
                        const TBinary& m_plus, UI8 delta, SI4& k) {
    TBinary one(((UI8)1) << -m_plus.e, m_plus.e), wp_w = m_plus - w;
    UI4 d, pow_10, p_1 = static_cast<UI4>(m_plus.f >> -one.e);
    UI8 p_2 = m_plus.f & (one.f - 1);
    int kappa;
    if (p_1 < (pow_10 = 10)) {
      kappa = 1;
    } else if (p_1 < (pow_10 = 100)) {
      kappa = 2;
    } else {
      if ((p_1 >> 10) == 0) {
        kappa = 3;
        pow_10 = 1000;
      } else if (!(p_1 >> 13)) {
        kappa = 4;
        pow_10 = 10000;
      } else if (!(p_1 >> 17)) {
        kappa = 5;
        pow_10 = 100000;
      } else if (!(p_1 >> 20)) {
        kappa = 6;
        pow_10 = 1000000;
      } else if (!(p_1 >> 24)) {
        kappa = 7;
        pow_10 = 10000000;
      } else if (!(p_1 >> 27)) {
        kappa = 8;
        pow_10 = 100000000;
      } else if (!(p_1 >> 30)) {
        kappa = 9;
        pow_10 = 1000000000;
      } else {
        kappa = 10;
        pow_10 = 10000000000;
      }
      if (p_1 >= pow_10) {
        ++kappa;
        pow_10 *= 10;
      }
    }
    while (kappa > 0) {
      UI4 d;
      d = p_1 / pow_10;
      p_1 -= d * pow_10;

      if (cursor >= end) return nullptr;

      if (d) cursor = TPrintDecimal<Char>(cursor, d);

      --kappa;
      UI tmp = (static_cast<UI8>(p_1) << -one.e) + p_2;

      if (tmp <= delta) {
        k += kappa;
        Round(delta, tmp, IEEE754Pow10(kappa) << -one.e, wp_w.f);
        return;
      }
    }

    for (;;) {  // kappa = 0
      p_2 *= 10;
      delta *= 10;
      char d = static_cast<char>(p_2 >> -one.e);
      if (cursor >= end) return nullptr;
      if (d) *cursor++ = '0' + d;
      p_2 &= one.f - 1;
      --kappa;
      if (p_2 < delta) {
        k += kappa;
        Round(delta, p_2, one.f, wp_w.f * IEEE754Pow10(-kappa));
        return;
      }
    }

    // Load integer pow_10 from the i-cache.
    switch (kappa) {
      case 1:
        d = p_1;
        p_1 = 0;
        break;
      case 2:
        pow_10 = 10;
        break;
      case 3:
        pow_10 = 100;
        break;
      case 4:
        pow_10 = 1000;
        break;
      case 5:
        pow_10 = 10000;
        break;
      case 6:
        pow_10 = 100000;
        break;
      case 7:
        pow_10 = 1000000;
        break;
      case 8:
        pow_10 = 10000000;
        break;
      case 9:
        pow_10 = 100000000;
        break;
      case 10:
        pow_10 = 1000000000;
        break;
    }
  }

  template <typename Char = char>
  static Char* Standardize(Char* buffer, Char* end, SIW length, SI4 k) {
    const SIW kk = length + k;  // 10^(kk-1) <= v < 10^kk
    Char* nil_term_char;
    if (length <= kk && kk <= 21) {  // 1234e7 -> 12340000000
      for (SIW i = length; i < kk; i++) buffer[i] = '0';
      buffer[kk] = '.';
      buffer[kk + 1] = '0';
      nil_term_char = &buffer[kk + 2];
      *nil_term_char = '\0';
      return nil_term_char;
    } else if (0 < kk && kk <= 21) {  // 1234e-2 -> 12.34
      SocketShiftUp(&buffer[kk + 1], LastByte(&buffer[kk]), length - kk);
      buffer[kk] = '.';
      nil_term_char = &buffer[length + 1];
      *nil_term_char = '\0';
      return nil_term_char;
    } else if (-6 < kk && kk <= 0) {  // 1234e-6 -> 0.001234
      const SIW offset = 2 - kk;
      SocketShiftUp(&buffer[offset], LastByte(&buffer[0]), length);
      buffer[0] = '0';
      buffer[1] = '.';
      for (SIW i = 2; i < offset; i++) buffer[i] = '0';
      nil_term_char = &buffer[length + offset];
      *nil_term_char = 0;
      return nil_term_char;
    } else if (length == 1) {
      // 1e30
      buffer[1] = 'e';
      return TPrintSigned<SIW, Char>(buffer + 2, end, kk - 1);
    }
    // else 1234e30 -> 1.234e33
    SocketShiftUp(&buffer[2], LastByte(&buffer[1]), length - 1);

    *(++buffer)++ = '.';
    *buffer++ = 'e';
    return TPrintSigned<SIW, Char>(buffer + length + 2, end, kk - 1);
  }
};

using Binary32 = TBinary<FLT, UI4>;
using Binary64 = TBinary<DBL, UI8>;

}  // namespace _
#undef PRINT_FLOAT_BINARY

#endif  //< #if SEAM >= _0_0_0__03

#endif  //< #if INCLUDED_SCRIPTTBINARY

/*
  // Non-working algorithm DOES NOT converts a string-to-FLT.
  //@return nil if there is no number to scan or pointer to the next char after
  // the end of the scanned number upon success.
  //@brief Algorithm uses a 32-bit unsigned value to scan the floating-point
  // number, which can only have 10 digits max, so the maximum floating-point
  // number digit count we can scan is 9 digits long.
  template <typename Char = char>
  const Char* Scan(const Char* buffer, Float& result) {
    ASSERT(buffer);
    PRINTF("\n\nScanning FLT:%s", buffer);

    enum {
      kCharCountMax = 9,  // < (1 + [p*log_10(2)], where p = 32
    };

    UI4 integer,  //< Integer portion in TBinary.
        sign,          //< Sign in Binary32 format.
        ui_value,      //< Unsigned value.
        pow_10_ui2;    //< Power of 10 for converting integers.

    // Scan sign of number:

    if (*buffer == '-') {
      sign = TNaNSigned<UI4, UI4>();
      ++buffer;
    } else {
      sign = 0;
    }

    PRINTF("\nScanning integer portion:%i", static_cast<SI4>(result));

    const Char* cursor = buffer;
    Char c = *cursor++;
    if (!TIsDigit<Char>(c)) return nullptr;

    // Find length:
    c = *cursor++;
    while (TIsDigit<Char>(c)) c = *cursor++;
    const Char* end = cursor;  // Store end to return.
    cursor -= 2;
    PRINTF("\nPointed at \'%c\' and found length:%i", *cursor,
           (SI4)(cursor - buffer));

    c = *cursor--;
    ui_value = (UI4)(c - '0');
    pow_10_ui2 = 1;

    while (cursor >= buffer) {
      c = *cursor--;
      pow_10_ui2 *= 10;
      UI4 new_value = ui_value + pow_10_ui2 * (c - '0');
      if (new_value < ui_value) return nullptr;
      ui_value = new_value;
      PRINTF("\nvalue:%u", (uint)ui_value);
    }

    // integer = unsigned_integer;

    PRINTF("\nfound %i and pointed at \'%c\'", integer, *end);

    // Numbers may start with a dot like .1, .2, ...
    if (*buffer == '.') goto ScanDecimals;

    if (*end != '.') {
      result = static_cast<FLT>(integer);
      PRINTF("\nFound value:%f", result);
      return end;
    }
    ++buffer;
  ScanDecimals:
    // We have to inline the ScanUnsigned here in order to detect if there
    // are too many decimals
    cursor = end;
    Char c = *cursor++;
    if (!TIsDigit<Char>(c)) {
      PRINTF("Found a period.");
      return nullptr;
    }
    PRINTF("\nConverting decimals:\"%s\" with max length %i", buffer,
           kCharCountMax);

    // Find length
    c = *cursor++;
    while (TIsDigit<Char>(c)) c = *cursor++;

    end = cursor;  // Store end to return.
    cursor -= 2;

    SIW length = cursor - buffer;
    PRINTF("\nPointed at \'%c\' and found length:%i", *cursor, (SI4)length);

    if (length > kCharCountMax) {
      cursor = buffer + kCharCountMax;
      length = kCharCountMax;
    }

    // Manually load the first char.
    c = *cursor--;
    ui_value = (UI4)(c - '0'), pow_10_ui2 = 1;

    // Then iterate through the rest in a loop.
    while (cursor >= buffer) {
      c = *cursor--;
      pow_10_ui2 *= 10;
      UI4 new_value = ui_value + pow_10_ui2 * (c - '0');
      if (new_value < ui_value) {
        PRINTF("\nUnsigned wrap-around!");
        return nullptr;
      }
      ui_value = new_value;
      PRINTF("\nFound integer_value:%u", (uint)ui_value);
    }
    PRINTF("\nFound integer_value:%u", (uint)ui_value);

    PRINTF("\nConverting bit_pattern backwards:");

    // Convert decimals to base 2 by multiply in a loop the integer value is
    // greater than one then subtract the equivalent of one until the value
    // is zero.

    UI4 one = IEEE754Pow10E()[length - 1], bit_pattern = 0;
    PRINT('\n');
    SI4 bit_shift_count = 0;
    while ((ui_value != 0) && (++bit_shift_count < 24)) {
      ui_value = ui_value << 1;  //< << 1 to * 2
      if (ui_value >= one) {
        bit_pattern = (bit_pattern << 1) | 1;
        ui_value -= one;
        PRINT('1');
      } else {
        bit_pattern = bit_pattern << 1;
        PRINT('0');
      }
    }
    PRINTF("'b0");
    PRINT_FLOAT_BINARY(integer, ui_value, length);
    // Now check for the exponent.

    ui_value |= integer << length;

    PRINTF("\nNormalizing bits...");

    if (c != 'e' && c != 'E') {
      PRINTF("\nNo \'e\' or \'E\' found.");
      // ui_value = sign | FloatNormalize<FLT, UI4>(integer);
      // result = *reinterpret_cast<Float*>(&ui_value);
      return end;
    }

    // @todo This is no doubt optimization, not sure how much it would help
    // though.
    SI4 signed_value;
    buffer = TScanSigned<SI4, UI4, Char>(end, signed_value);
    if (!buffer) {
      PRINTF("\nNo exponent found.");
      // result = reinterpret_cast(sign |);
      return end;
    }

    if (signed_value < -128 || signed_value > 127) {
      PRINTF("\nExponent out of range!");
      // result = result_flt;
      return end;
    }

    // We're finally done so store the result.
    // result = result_flt;

    return end;
  } */

/* Script^2 @version 0.x
@link    https://github.com/kabuki-starship/script2.git
@file    /casciidata.h
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

#if SEAM >= _0_0_0__12
#ifndef INCLUDED_SCRIPT_CASCIIDATA
#define INCLUDED_SCRIPT_CASCIIDATA

#include "csocket.h"
#include "tutf.h"

namespace _ {
/* A type-value tuple. */
struct API TypeValue {
  type_t type;        //< ASCII Type.
  const void* value;  //< Pointer to the value data.

  /* Stores the type and value. */
  TypeValue(type_t type, const void* value = nullptr);
};

/* List of the 32 ASCII Data Types.
    Types are organized with types that are allowed in text B-Sequences first,
    followed by objects which get created in text using Script Operations. */
typedef enum AsciiTypes {
  kNIL = 0,  //< 0.  kNIL/nil/void type.
  kSI1,      //< 1.  8-bit signed integer.
  kUI1,      //< 2.  8-bit unsigned integer.
  kSI2,      //< 3.  16-bit signed integer.
  kUI2,      //< 4.  16-bit unsigned integer.
  kHLF,      //< 5.  16-bit floating-point number.
  kBOL,      //< 6.  32-bit non-zero true boolean as signed integer.
  kSI4,      //< 7.  32-bit signed integer.
  kUI4,      //< 8.  32-bit unsigned integer.
  kFLT,      //< 9.  32-bit floating-point number.
  kTMS,      //< 10. 32-bit second since epoch timestamp.
  kTSS,      //< 11. 64-bit sub-second timestamp with kTMS and an kUI4 tick.
  kTME,      //< 12. 64-bit second since epoch timestamp.
  kSI8,      //< 13. 64-bit signed integer.
  kUI8,      //< 14. 64-bit unsigned integer.
  kDBL,      //< 15. 64-bit floating-point number.
  kSIH,      //< 16. 128-bit (Hexadeca-UI1) signed integer.
  kUIH,      //< 17. 128-bit (Hexadeca-UI1) unsigned integer.
  kDEC,      //< 18. 128-bit (Hexadeca-UI1) floating-point number.
  kUIX,      //< 19. 2^(6+X)-bit unsigned integer, where 0 <= X <= 7.
  kOBJ,      //< 20. N-UI1 object.
  kADR,      //< 21. UTF-8 Operand stack address.
  kSTR,      //< 22. A UTF-8 string.
  kTKN,      //< 23. A UTF-8 string token without whitespace.
  kBSQ,      //< 24. B-Sequence.
  kLOM,      //< 25. A loom of UTF-8, UTF-16, or UTF-32 strings.
  kTBL,      //< 26. A hash table.
  kEXP,      //< 27. Script^2 Expression.
  kLST,      //< 28. Set or multiset of Type-Value tuples.
  kMAP,      //< 29. One-to-one map of Integer-{Type-Value} records.
  kBOK,      //< 30. Many-to-one multimap of Key-{Type-Value} records.
  kDIC,      //< 31. One-to-one map of Key-{Type-Value} records.
} AsciiType;

/* Checks if the given type is valid.
    @return False if the given type is an 8-bit kLST, kMAP, kBOK, or kDIC. */
inline BOL TypeIsValid(type_t type);

/* Aligns the given pointer to the correct word boundary for the type. */
API void* TypeAlign(type_t type, void* value);

enum {
  kTypeCount = 32,  //< The starting index of invalid types.
};

/* Returns a pointer to an array of pointers to the type names.*/
API const char** TypeStrings();

/* Returns the name of the given type. */
API inline const char* TypeString(type_t type);

/* Returns the name of the given type. */
API inline const char* TypeString(UIT type);

/* Masks off the lower 5-LSb to get the type. */
API inline UI1 TypeMask(UI1 value);

/* Returns true if the given type is an Array type. */
API inline BOL TypeIsArray(UIT type);

/* Returns true if the given type is a kBOK type. */
API inline BOL TypeIsSet(UIT type);

/* Returns the size or max size of the given type. */
API UIT TypeFixedSize(UIT type);

/* Gets the next address that a data type may be stored at. */
API void* TypeAlign(type_t type, void* value);

/* Writes the given value to the socket. */
API char* Write(char* begin, char* end, type_t type, const void* source);

/* Returns true if the given type is an ASCII OBJ. */
API inline BOL TypeIsObj(type_t type);

/* Returns true if the given type is a string type. */
API inline BOL TypeIsString(type_t type);

/* Checks if the given type is UTF-16.
    @param  type The type to check.
    @return True if the given type is UTF-16. */
API inline BOL TypeIsUtf16(type_t type);

API inline int TypeSizeWidthCode(type_t type);
}  // namespace _

#if USING_UTF8
namespace _ {
/* Prints th given type or type-value.
@return Returns a pointer to the next char after the end of the read number or
nil upon failure.
@param utf The utf to print to.
@param type    The type to print.
@param value   The value to print or nil. */
API char* Print(char* begin, char* end, type_t type, const void* value);
}  // namespace _

/* Writes the given value to the print justified right.
@return The utf.
@param  utf The utf.
@param  item The item to print. */
API _::UTF8& operator<<(_::UTF8& utf, const _::TypeValue& type_value);
#endif

#if USING_UTF16
namespace _ {
/* Prints th given type or type-value.
@return Returns a pointer to the next char after the end of the read number or
nil upon failure.
@param utf The utf to print to.
@param type    The type to print.
@param value   The value to print or nil. */
API char16_t* Print(char16_t* begin, char16_t* end, type_t type,
                    const void* value);
}  // namespace _
/* Writes the given value to the print justified right.
@return The utf.
@param  utf The utf.
@param  item The item to print. */
API _::UTF2& operator<<(_::UTF2& utf, const _::TypeValue& type_value);
#endif
#if USING_UTF32

namespace _ {
/* Prints th given type or type-value.
@return Returns a pointer to the next char after the end
of the read number or nil upon failure.
@param printer The printer to print to.
@param type    The type to print.
@param value   The value to print or nil. */
API char16_t* Print(char16_t* begin, char16_t* end, type_t type,
                    const void* value);
}  // namespace _
/* Writes the given value to the print justified right.
@return The utf.
@param  utf The utf.
@param  item The item to print. */
API _::UTF4& operator<<(_::UTF4& utf, const _::TypeValue& type_value);
#endif

#endif  //< INCLUDED_SCRIPT_CASCIIDATA
#endif  //< #if SEAM >= _0_0_0__12

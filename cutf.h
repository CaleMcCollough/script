/* Script^2 @version 0.x
@link    https://github.com/kabuki-starship/script2.git
@file    /cutf.h
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

#if SEAM >= _0_0_0__02
#ifndef INCLUDED_SCRIPTUTF
#define INCLUDED_SCRIPTUTF

#ifndef USING_UTF8
#define USING_UTF8 1
#endif

#if USING_UTF8
#include "cutf1.h"
#endif
#if USING_UTF16
#include "cutf2.h"
#endif
#if USING_UTF32
#include "cutf4.h"
#endif

namespace _ {
#if USING_UTF == UTF8
using Utf = UTF1;
using Center = Utf8Center;
using Right = Utf8Right;
using Line = Utf8Line;
using LineString = Utf8LineString;
#elif USING_UTF == UTF16
using Utf = UTF2;
using Center = Utf16Center;
using Right = Utf16Right;
using Line = Utf16Line;
using LineString = Utf16LineString;
#elif USING_UTF == UTF32
using Utf = UTF4;
using Center = Utf32Center;
using Right = Utf32Right;
using Line = Utf32Line;
using LineString = Utf32LineString;
#endif
}  // namespace _

#endif  //< #if INCLUDED_SCRIPTUTF
#endif  //< #if SEAM >= _0_0_0__02

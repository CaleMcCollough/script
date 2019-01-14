/* Script^2 @version 0.x
@file    /0_0_0__06_test_ascii_array.h
@author  Cale McCollough <cale.mccollough@gmail.com>
@license Copyright (C) 2014-2019 Cale McCollough <calemccollough.github.io>;
All right reserved (R). Licensed under the Apache License, Version 2.0 (the
"License"); you may not use this file except in compliance with the License.
You may obtain a copy of the License at www.apache.org/licenses/LICENSE-2.0.
Unless required by applicable law or agreed to in writing, software distributed
under the License is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
CONDITIONS OF ANY KIND, either express or implied. See the License for the
specific language governing permissions and limitations under the License. */

#pragma once
#include <pch.h>

#include "tarray.h"

#if SEAM == _0_0_0__07
#include "test_debug.inl"
#else
#include "test_release.inl"
#endif

using namespace _;

static const CH1* _0_0_0__07_ASCII_Array(CH1* seam_log, CH1* seam_end,
                                         const CH1* args) {
#if SEAM >= _0_0_0__07
  TEST_BEGIN;

  static const SI4 array_3d_exected[2][2][2] = {{{0, 1}, {2, 3}},
                                                {{4, 5}, {6, 7}}};
  const SI4* test = Dimensions<2, 2, 2>();
  TArray<SI4> test_array(test);
  *test_array.Elements() = {{{0, 1}, {2, 3}}, {{4, 5}, {6, 7}}};
  i = 0;
  SI4* array_base = test_array.Elements();
  for (SI4 z = 0; z < 2; ++z)
    for (SI4 y = 0; y < 2; ++y)
      for (SI4 x = 0; x < 2; ++x) Compare(i++, array_3d_exected[x][y][z]);

#endif
  return nullptr;
}

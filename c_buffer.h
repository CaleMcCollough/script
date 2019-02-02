/* Script^2 @version 0.x
@link    https://github.com/kabuki-starship/script2.git
@file    /script2/socket.h
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
#include <pch.h>
#if SEAM >= SCRIPT2_14
#ifndef SCRIPT2_BUFFER
#define SCRIPT2_BUFFER
// Dependencies:
#include "c_onfig.h"
// End dependencies.

namespace _ {

/* Creates/Gets a static socket of the specified size. */
template <SIW kBufferSize = kBufferSizeDefault>
inline CH1* Buffer() {
  enum {
    kBufferSizeWords =
        (kBufferSize / sizeof(UIW)) + kBufferSize % sizeof(UIW) ? 1 : 0
  };
  static UIW socket[kBufferSizeWords];
  return reinterpret_cast<CH1*>(socket);
}

}  // namespace _
#endif  //< SCRIPT2_BUFFER
#endif  //< #if SEAM >= SCRIPT2_14

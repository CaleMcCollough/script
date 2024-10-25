/* Script2�
@link    https://github.com/KabukiStarship/Script2.git
@file    /Errors.hpp
@author  Cale McCollough <https://cookingwithcale.org>
@license Copyright Kabuki Starship� <kabukistarship.com>;
This Source Code Form is subject to the terms of the Mozilla Public License,
v. 2.0. If a copy of the MPL was not distributed with this file, You can obtain
one at <https://mozilla.org/MPL/2.0/>. */
#pragma once
#ifndef SCRIPT2_ERROR
#define SCRIPT2_ERROR
#include "Error.h"
#if SEAM >= SCRIPT2_CORE
namespace _ {

/* Human-readable Crabs error strings. */
template<typename CH = CHR>
const CH* TCrabsErrorST() {
  static const CH error_strings[CrabsErrorCount + 1][32] = {
    /*00*/{'S','u','c','k',' ','i','t',0,},
    /*01*/{'I','n','v','a','l','i','d',0,},
    /*02*/{'I','n','v','a','l','i','d',' ','b','o','o','f','e','r',0},
    /*03*/{'I','n','v','a','l','i','d',' ','b','o','u','n','d','s',0},
    /*04*/{'I','n','v','a','l','i','d',' ','d','o','o','r',0},
    /*05*/{'I','n','v','a','l','i','d',' ','h','e','a','d','e','r',0},
    /*06*/{'I','n','v','a','l','i','d',' ','h','a','s','h',0},
    /*07*/{'I','n','v','a','l','i','d',' ','i','n','d','e','x',0},
    //--------------------------------------------------------------------------
    /*08*/{'I','n','v','a','l','i','d',' ','i','n','p','u','t',0},
    /*09*/{'I','n','v','a','l','i','d',' ','e','n','q','u','e','r','y',0},
    /*10*/{'I','n','v','a','l','i','d',' ','o','p',0},
    /*11*/{'I','n','v','a','l','i','d',' ','o','p','e','r','a','n','d',0},
    /*12*/{'I','n','v','a','l','i','d',' ','r','o','o','m',0},
    /*13*/{'I','n','v','a','l','i','d',' ','t','y','p','e',0},
    /*14*/{'I','n','v','a','l','i','d',' ','U','T','F','-','8',0},
    /*15*/{'I','n','v','a','l','i','d',' ','U','T','F','-','1','6',0},
    //--------------------------------------------------------------------------
    /*16*/{'A','r','r','a','y',' ','u','n','d','e','r','f','l','o','w',0},
    /*17*/{'B','o','o','f','e','r',' ','u','n','d','e','r','f','l','o','w',0},
    /*18*/{'K', 'e', 'y', 's', ' ', 'b', 'o', 'o', 'f', 'e', 'r', ' ', 'u','n','d',
           'e', 'r', 'f', 'l', 'o', 'w', 0, },
    /*19*/{'P','a','r','a','m',' ','u','n','d','e','r','f','l','o','w',0},
    /*20*/{'S','t','a','c','k',' ','u','n','d','e','r','f','l','o','w',0},
    /*21*/{'T','e','x','t',' ','u','n','d','e','r','f','l','o','w',0},
    /*22*/{'V','a','r','i','n','t',' ','u','n','d','e','r','f','l','o','w',0},
    /*23*/{'Y','o','u','r',' ','m','o','m',' ','u','n','d','e','r','f','l','o','w',
           0},
    //--------------------------------------------------------------------------
    /*24*/{'A','r','r','a','y',' ','o','v','e','r','f','l','o','w',0},
    /*25*/{'B','o','o','f','e','r',' ','o','v','e','r','f','l','o','w',0},
    /*26*/{'K', 'e', 'y', 's', ' ', 'b', 'o', 'o', 'f', 'e', 'r', ' ', 'o', 'v',
           'e', 'r', 'f', 'l', 'o', 'w', 0 },
    /*27*/{'P','a','r','a','m',' ','o','v','e','r','f','l','o','w',0},
    /*28*/{'S','t','a','c','k',' ','o','v','e','r','f','l','o','w',0},
    /*29*/{'T','e','x','t',' ','o','v','e','r','f','l','o','w',0},
    /*30*/{'V','a','r','i','n','t',' ','o','v','e','r','f','l','o','w',0},
    /*31*/{'Y','o','u','r',' ','m','o','m',' ','o','v','e','r','f','l','o','w',
           0},
    //--------------------------------------------------------------------------
    /*32*/{'P','a','r','a','m',' ','n','i','l',0},
    /*33*/{'P','a','r','a','m',' ','i','s',' ','e','r','r','o','r',' ','c','o',
           'd','e',0},
    /*34*/{'P','a','r','a','m',' ','i','n','v','a','l','i','d',0},
    /*35*/{'P','a','r','a','m',' ','e','r','o','n','e','o','u','s',0},
    /*36*/{'R', 'e', 'a', 'd', ' ', 'o', 'n', 'l', 'y', 0},
    /*37*/{'W', 'r', 'i', 't', 'e', ' ', 'o', 'n', 'l', 'y', 0},
    /*38*/{'U','n','a','u','t','h','e','r','i','z', 'e','d',0},
    /*39*/{'U','n','a','u','t','h','e','r','i','z', 'e','d',0},
    //--------------------------------------------------------------------------
    /*40*/{'U','n','a','v','a','i','l','a','b','l','e',0},
    /*41*/{'U','n','a','v','a','i','l','a','b','l','e',' ','k','e','y',0},
    /*42*/{'I','m','p','l','e','m','e','n','t','a','t','i','o','n',0}
  };
  return &error_strings[0][0];
}

template<typename CH = CHR, typename IS = ISN>
const CH* TCrabsErrorST(IS index) {
  if (index < 0) index *= -1;
  if (index >= CrabsErrorCount) index = CrabsErrorCount;
  return &TCrabsErrorST<CH>()[index << 5];
}
}  //< namespace _
#endif
#endif

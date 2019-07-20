/* SCRIPT Script @version 0.x
@link    https://github.com/kabuki-starship/script2.git
@file    /script2/test_tree.cc
@author  Cale McCollough <https://calemccollough.github.io>
@license Copyright (C) 2014-2019 Cale McCollough <cale@astartup.net>;
All right reserved (R). This Source Code Form is subject to the terms of the
Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with
this file, You can obtain one at https://mozilla.org/MPL/2.0/. */

#pragma once
#include <pch.h>

#ifndef INCLUDED_SEAM_TREE
#define INCLUDED_SEAM_TREE 1

#include "module_tests.h"
#include "t_test.h"

SI4 main(SI4 arg_count, CH1** args) {
  return ::_::TTestTree<script2::TestNode>(arg_count, args);
}
#endif

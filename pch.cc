// pch.cpp: source file corresponding to pre-compiled header; necessary for
// compilation to succeed

#include "pch.h"

#if SCRIPT2_RUN_TESTS == YES_0

#include <module_tests.h>

SIN main(SIN arg_count, CH1 **args) {
  return _::TTestTree<script2::TestNode>(arg_count, args);
}
#endif

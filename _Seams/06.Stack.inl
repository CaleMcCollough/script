/* Script2 (TM) @version 0.x
@link    https://github.com/KabukiStarship/Script2.git
@file    /_Seams/06.Stack.inl
@author  Cale McCollough <https://cookingwithcale.org>
@license Copyright (C) 2015-2023 Kabuki Starship (TM) <kabukistarship.com>;
This Source Code Form is subject to the terms of the Mozilla Public License,
v. 2.0. If a copy of the MPL was not distributed with this file, You can obtain
one at <https://mozilla.org/MPL/2.0/>. */
#if SEAM >= SCRIPT2_STACK
#include "../Stack.hpp"
using namespace _; 
#if SEAM == SCRIPT2_STACK
#include "../_Debug.inl"
#else
#include "../_Release.inl"
#endif
#endif
namespace Script2 {

#if SEAM >= SCRIPT2_STACK
template <typename T, typename ISZ>
void TestStack(const CHA* args) {
  D_COUT("Testing AStack<IS" << CHA('@' + sizeof(T)) << ",IS" << CHA('@' + sizeof(ISZ)) << ">...\n");

  AStack<T, ISZ, 8> stack;

  D_COUT(Linef("\n+---\n| TBUF: size:")
         << stack.AJT().Buffer().Size() << " expected_size_bytes:"
         << stack.AJT().Buffer().Size() * sizeof(T) + sizeof(TStack<ISZ>)
         << " size_bytes:" << stack.AJT().Buffer().SizeBytes()
         << " size_words:" << stack.AJT().Buffer().SizeWords());
  D_COUT_OBJ(stack);

  enum { cTestCount = 32 };
  D_COUT("\n\nPushing " << cTestCount << " items on to the Stack...\n");
  T i;
  for (i = 0; i < cTestCount; ++i) {
    D_COUT("\n| " << i << ".) count:" <<
           stack.Count());
    //D_COUT("\n| Before calling push:" << 
    //       Charsf(stack.AJT().Origin(), stack.AJT().SizeBytes()) << 
    //       Linef("\n\n+---\n| ") << i << ".) ");
    stack.Push('0' + i);
    //D_COUT("\n| Result:");
    //D_COUT_OBJ(stack);
  }

  D_COUT(Headingf("\n\nPopping items off the Stack... ") << "i:" << i << 'n');
  for (i=i-1; i >= 0; --i) {
    //D_COUT_OBJ(stack);
    A_AVOW_INDEX(i, stack.Pop() - '0', i);
    D_COUT("\n| " << i << ".) Popping count:" << stack.Count());
  }
  D_COUT("\n\nEnding stack.Count(): " << stack.Count() << " i: " << 
         i << '\n');
  D_COUT_OBJ(stack);
  A_ASSERT(stack.Count() == 0);
}
#endif

static const CHA* Stack(const CHA* args) {
#if SEAM >= SCRIPT2_STACK
  A_TEST_BEGIN;

  D_COUT(Headingf("Testing ArrayCopy with offset sequential arrays..."));

  enum {
    cOffset = 2 * sizeof(IUW),
    cBufferSizeBytes = 256 + 2 * cOffset,
    cBufferSizeWords = cBufferSizeBytes >> cWordBitCount,
  };
  for (ISN i = 0; i < cOffset; ++i) {
    // Create an array of bytes valued sequentially 0 through 255.
    IUW source[cBufferSizeWords];
    IUA* cursor = TPtr<IUA>(source), * end = cursor + cBufferSizeBytes;
    for (ISN j = i; j > 0; --j) *cursor++ = 0;
    for (ISN j = 0; j < 256; ++j) *cursor++ = ISA(j);
    while (cursor < end) *cursor++ = 0;
    //D_COUT(Charsf(source, cBufferSizeBytes));
    // Copy those bytes into a buffer with an offset to exaustly test each 
    // memory layout variation modulo the word size.
    IUW destination[cBufferSizeWords];
    for (ISN j = 0; j < cOffset; ++j) {
      D_COUT("\n\ni:" << i << "j:" << j);
      ArrayFill(destination, cBufferSizeBytes, 0);
      IUA* source_start = TPtr<IUA>(source) + j, 
         * destination_start = TPtr<IUA>(destination) + j;
      auto result = ArrayCopy(destination_start, cBufferSizeBytes,
                              TPtr<IUA>(source) + i, 256);
      if (!result) {
        D_COUT("\n\nArrayCopy failed!\nsource:\n" << 
               Charsf(source, 256));
        D_COUT("\ndestination:\n" << Charsf(destination, 256));
      }
      result =
        ArrayCompareSlow(source_start, 256, destination_start, 256);
      D_ASSERT(result > 0);
      if (result <= 0) {
        D_COUT("\n\nArrayCompareSlow failed with code " << result);
        result *= -1;
        D_COUT("\nsource_start[" << result - 1 << "]:0x" <<
               Hexf(*(source_start + result - 1)) <<
               " destination_start[" << result - 1 << "]:0x" <<
               Hexf(*(destination_start + result - 1)) <<
                
               "\nsource_start[" << result << "]:0x" <<
               Hexf(*(source_start + result)) <<
               " destination_start[" << result << "]:0x" <<
               Hexf(*(destination_start + result)) <<

               "\nsource_start[" << result + 1 << "]:0x" <<
               Hexf(*(source_start + result + 1)) <<
               " destination_start[" << result + 1 << "]:0x" <<
               Hexf(*(destination_start + result + 1)));
        A_ASSERT(result > 0);
      }

      result = 
        ArrayCompareFast(source_start, 256, destination_start, 256);
      if (result <= 0) {
        D_COUT("\n\nArrayCompareFast failed with result " << result);
        result *= -1;
        D_COUT("\nsource_start[" << result - 1 << "]:0x" <<
                Hexf(*(source_start + result - 1)) <<
                " destination_start[" << result - 1 << "]:0x" <<
                Hexf(*(destination_start + result - 1)) <<

                "\nsource_start[" << result << "]:0x" <<
                Hexf(*(source_start + result)) <<
                " destination_start[" << result << "]:0x" <<
                Hexf(*(destination_start + result)) <<

                "\nsource_start[" << result + 1 << "]:0x" <<
                Hexf(*(source_start + result + 1)) <<
                " destination_start[" << result + 1 << "]:0x" <<
                Hexf(*(destination_start + result + 1)));

        D_COUT("\n\nsource:" << Charsf(source, cBufferSizeBytes) << 
          "\n\ndestination:" << Charsf(destination, cBufferSizeBytes));
        A_ASSERT(result > 0);
      }
    }
  }

  D_COUT(Headingf("Test ArrayCopy and MemoryCompare"));

  enum {
    cTestCharsCount = 1024,
    cTestCharsOffsetCount = 16,
  };
  CHA test_chars[cTestCharsCount];
  CHA test_chars_result[cTestCharsCount + cTestCharsOffsetCount];

  D_COUT("\ntest_chars[0]:0x" << Hexf(test_chars) << " test_chars_result[n]:0x"
                              << Hexf(test_chars_result));

  for (ISC i = 0; i < cTestCharsOffsetCount; ++i) {
    for (ISC j = 0; j < cTestCharsCount; ++j)
      test_chars[j] = CHA(j); // (CHA)(j % 256);
    ISW result = ArrayCopy(test_chars_result + i, cTestCharsCount, test_chars,
                            cTestCharsCount);
    A_ASSERT(result == cTestCharsCount);
    A_ASSERT(ArrayCompare(test_chars + i, cTestCharsCount, test_chars_result,
                           cTestCharsCount) >= 0);
  }

  // TestStack<ISC, ISD>(args); is illegal
  TestStack<ISC, ISC>(args);
  TestStack<ISD, ISD>(args);
  TestStack<ISD, ISC>(args);
#endif
  return nullptr;
}
}  //< namespace Script2

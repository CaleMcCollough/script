/* SCRIPT Script @version 0.x
@link    https://github.com/kabuki-starship/script2.git
@file    /script2/t_stack.h
@author  Cale McCollough <https://calemccollough.github.io>
@license Copyright (C) 2014-2019 Cale McCollough <cale@astartup.net>;
All right reserved (R). This Source Code Form is subject to the terms of the
Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with
this file, You can obtain one at <https://mozilla.org/MPL/2.0/>. */

#pragma once
#include <pch.h>
#if SEAM >= SEAM_SCRIPT2_STACK
#ifndef SCRIPT2_TSTACK
#define SCRIPT2_TSTACK 1

#include "c_socket.h"
#include "t_strand.h"

#if SEAM == SEAM_SCRIPT2_STACK
#include "module_debug.inl"
#else
#include "module_release.inl"
#endif

namespace _ {

/* @ingroup AsciiStack
Please see the ASCII Data Types Specificaiton for DRY documentation.
@link ./spec/data/vector_types/stack.md */

/* An array obj of homogeneous-sized plain-old-data (POD) types.
Please see the ASCII Data Types Specificaiton for DRY documentation.
@link ./spec/data/vector_types/stack.md

# Stack Memory Layout

@code
    +---------------+
    |    Buffer     |
    |---------------|
    | C-Style Array |
 ^  |---------------|
 |  |    Header     |
0xN +---------------+
@endcode
*/
template <typename SIZ = SIN>
struct TStack {
  SIZ size,   //< Size of the Array in elements.
      count;  //< Element count.
};

/* Gets the size of a Stack with the given count_max. */
template <typename T = SIN, typename SIZ = SIN>
inline SIZ TStackSize(SIZ count_max) {
  enum { kCountMaxMin = sizeof(UI8) / sizeof(T) };
  if (count_max < kCountMaxMin) count_max = kCountMaxMin;
  return sizeof(TStack<SIZ>) + sizeof(T) * count_max;
}

/* Gets the min size of a Stack with zero elements. */
template <typename T = SIN, typename SIZ = SIN>
inline SIZ TStackSizeMin() {
  enum {
    kStackCountMin = sizeof(T) > 8 ? 1 : 8 / sizeof(T),
    kStackCountMaxMin = sizeof(TStack<SIZ>) + sizeof(T) * kStackCountMin,
  };
  return kStackCountMaxMin;
}

/* Gets the max number_ of elements in an obj with the specific index
width. */
template <typename T = SIN, typename SIZ = SIN>
inline SIZ TStackSizeMax() {
  return (SIZ)((((~(SIZ)0) - 7) - (SIZ)sizeof(TStack<SIZ>)) / (SIZ)sizeof(T));
}

/*
template<typename T = SIN, typename SIZ = SIN>
SIZ StackCountMax () {
    return (SIZ)((UnsignedMax<SIZ> () - (SIZ)sizeof (TStack<T, SIZ,
SIZ>)) / (SIZ)sizeof (T));
}*/

/* The minimum obj size. */
template <typename T = SIN, typename SIZ = SIN>
inline SIZ TStackSizeMin(SIZ count_max) {
  SIZ count_upper_bounds = TStackSizeMax<T, SIZ>();
  if (count_max > count_upper_bounds) count_max = count_upper_bounds;
  return (SIZ)(sizeof(TStack<SIZ>) + count_max * sizeof(T));
}

template <typename T = SIN, typename SIZ = SIN>
inline SIZ TStackSizeOf(SIZ count) {
  return count * sizeof(T) + sizeof(TStack<SIZ>);
}

/* Initializes an obj from a preallocated socket who's size is a multiple of
8 bytes.
@param socket An obj of bytes large enough to fit the obj.
@return A dynamically allocated socket. */
template <typename T = SIN, typename SIZ = SIN>
TStack<SIZ>* TStackInit(TStack<SIZ>* stack, SIZ size) {
  if (!stack || size < 0) return nullptr;
  D_SOCKET_WIPE(stack, SIW(TStackSizeOf<T, SIZ>(size)));
  stack->size = size;
  stack->count = 0;
  return stack;
}

/* Initializes an obj from a preallocated socket who's size is a multiple of
8 bytes.
@param socket An obj of bytes large enough to fit the obj.
@return A dynamically allocated socket. */
template <typename T = SIN, typename SIZ = SIN>
TStack<SIZ>* TStackInit(TStack<SIZ>* stack, SIZ size, const T* items,
                        SIZ count) {
  if (!stack || !items || size <= 0 || count < 0) return nullptr;
  D_SOCKET_WIPE(stack, SIW(TStackSizeOf<T, SIZ>(size)));

  stack->size = size;
  stack->count = 0;
  return stack;
}

template <typename T = SIN, typename SIZ = SIN>
UIW* TStackClone(TStack<SIZ>* stack) {
  A_ASSERT(stack);
  SIZ size = stack->size;
  UIW* other_buffer = new UIW[size];
  UIW *source = reinterpret_cast<UIW*>(stack),  //
      *destination = other_buffer;
  SIZ data_amount =
      (stack->count * sizeof(T) + sizeof(TStack<SIZ>)) >> kWordBitCount;
  size -= data_amount;
  while (data_amount-- > 0) *destination++ = *source++;
  return destination;
}

/* Clones the other ASCII Autoject including possibly unused object space.
@return Nil upon failure or a pointer to the cloned object upon success.
@param socket A raw ASCII Socket to clone. */
template <typename T = UI1, typename SIZ = SIN>
UIW* TStackClone(Autoject& obj) {
  RamFactory factory = obj.ram_factory;
  UIW* begin = obj.begin;
  if (!factory || !begin) return nullptr;

  TStack<SIZ>* o = reinterpret_cast<TStack<SIZ>*>(begin);
  SIZ count = o->count;
  UIW* clone = TArrayNew<T, SIZ, TStack<SIZ>>(count);
  SIW size_bytes = (SIW)TStackSizeOf<T, SIZ>(count);
  if (!SocketCopy(clone, count, begin, size_bytes)) return nullptr;
  TSizeSet<SIZ>(begin, count);
  return clone;
}

/* Returns the first element in the Stack TMatrix. */
template <typename T = SIN, typename SIZ = SIN>
T* TStackStart(TStack<SIZ>* stack) {
  return TArrayStart<TStack<SIZ>, T>(stack);
}

/* Returns the last element of the stack. */
template <typename T = SIN, typename SIZ = SIN, typename Type = T>
inline Type TStackEnd(TStack<SIZ>* stack) {
  return reinterpret_cast<Type>(TStackStart<T, SIZ>(stack) + stack->count);
}

/* Returns the first empty element of the stack. */
template <typename T = SIN, typename SIZ = SIN>
inline T* TStackTop(TStack<SIZ>* stack) {
  return &TStackStart<T, SIZ>(stack)[stack->count];
}

/* Prints the given obj to the console. */
template <typename Printer, typename T = SIN, typename SIZ = SIN>
Printer& TStackPrint(Printer& o, TStack<SIZ>* stack) {
  D_ASSERT(stack);
  SIZ size = stack->size, count = stack->count;
  o << Linef("\n+---\n| TStack<T") << sizeof(T) << ",SI"
    << (CH1)('0' + sizeof(SIZ))
    << ">: size_bytes:" << TStackSizeOf<T, SIZ>(size) << " size: " << size
    << " count:" << count << Linef("\n+---");

  T* elements = TStackStart<T, SIZ>(stack);
  for (SI4 i = 0; i < count; ++i) o << "\n| " << i << ".) " << elements[i];
  if (count == 0) o << "\n| Empty";
#if DEBUG_THIS
  SIZ size_bytes = TStackSizeOf<T, SIZ>(stack->size);
  return o << Linef("\n+---") << Charsf(stack, size_bytes) << '\n';
#else
  return o;
#endif
}

/* Doubles the size of the stack.
@return Returns nil if the size is greater than the amount of memory that
can fit in type SIW, the unaltered socket pointer if the Stack has grown to the
size upper bounds, or a new dynamically allocated socket upon failure. */
template <typename T = SIN, typename SIZ = SIN>
BOL TStackGrow(Autoject& obj) {
  TStack<SIZ>* stack = reinterpret_cast<TStack<SIZ>*>(obj.begin);
  A_ASSERT(stack);
#if DEBUG_THIS
  D_COUT("\nAuto-growing Stack...\nBefore:");
  TStackPrint<COut, T, SIZ>(COut().Star(), stack);
#endif
  SIZ size = stack->size;
  if (!TCanGrow<SIZ>(size)) return false;
  SIW size_bytes = TStackSizeOf<T, SIZ>(stack->count);
  size = size << 1;
  SIZ new_size_bytes = TStackSizeOf<T, SIZ>(size);
  UIW* new_begin = obj.ram_factory(nullptr, new_size_bytes);
  TStack<SIZ>* other = reinterpret_cast<TStack<SIZ>*>(new_begin);
  other->size = size;
  other->count = stack->count;
  D_COUT(" copying data...");
  SocketCopy(TStackStart<T, SIZ>(other), size_bytes, TStackStart<T, SIZ>(stack),
             size_bytes);
  obj.begin = new_begin;
#if DEBUG_THIS
  D_COUT("\nResult:");
  TStackPrint<COut, T, SIZ>(COut().Star(), other);
#endif
  return true;
}

/* Attempts to resize the given Autoject to the new_count.
@return Nil upon failure. */
template <typename T = SIN, typename SIZ = SIN>
BOL TStackResize(Autoject& obj, SIZ new_count) {
  TStack<SIZ> stack = *reinterpret_cast<TStack<SIZ>*>(obj.begin);
  SIZ count = stack.count, count_max = TStackSizeMax<T, SIZ>();
  if (count > count_max || count == new_count) return false;
}

/* Checks if the given index exists in the stack. */
template <typename T = SIN, typename SIZ = SIN>
BOL TStackInBounds(TStack<SIZ>* stack, SIZ index) {
  return index >= 0 && index < stack->size;
}

/* Gets the element at the given index.
@param  obj    The obj.
@param  index The index of the element to get.
@return -1 if a is nil and -2 if the index is out of bounds. */
template <typename T = SIN, typename SIZ = SIN>
T TStackGet(TStack<SIZ>* stack, SIZ index) {
  A_ASSERT(stack);
  if (index < 0 || index >= stack->count) return 0;
  return TStackStart<T, SIZ>(stack)[index];
}

/* Peeks at the top item on the stack without popping it off.
@param  stack The base address of the stack.
@return The item popped off the obj. */
template <typename T = SIN, typename SIZ = SIN>
T TStackPeek(TStack<SIZ>* stack) {
  A_ASSERT(stack);
  SIZ count = stack->count;
  if (count == 0) return 0;
  T* items = TStackStart<T, SIZ>(stack);
  T item = items[stack->count - 1];
  return item;
}

/* Inserts the item into the obj at the given index.
@warning Function does not check for bounds and pushing to the top
if the Stack (@see SIZ TStackInsert<SIZ, SIZ> (T*, SIZ, T, SIZ)).
@param items Pointer to element 0 of the array.
@param item  The item to insert.
@param index The index to insert at.
@return -1 if a is nil and -2 if the obj is full. */
template <typename T = SIW, typename SIZ = SIN>
inline SIZ TStackInsert(T* items, SIZ count, T item, SIZ index) {
  T *target = items + index,  //
      *stop = items + count;
  // Shift the elements up.
  while (target < stop) *stop-- = *stop;
  *target = item;
  return count + 1;
}

/* Inserts the item into the obj at the given index.
@param items Pointer to element 0 of the array.
@param item  The item to insert.
@param index The index to insert at.
@return -1 if a is nil and -2 if the obj is full. */
template <typename T = SIW, typename SIZ = SIN>
inline SIZ TStackAdd(T* items, SIZ count, T item, SIZ index) {
  A_ASSERT(items);
  if (index < 0 || index > count) return -1;
  if (index == count) {
    items[count] = item;
    return count + 1;
  }
  if (count == 1) {
    items[1] = items[0];
    items[0] = item;
    return 1;
  }
  return TStackInsert<T, SIZ>(T, count, item, index);
}

/* Adds the given item to the stop of the obj.
@return The index of the newly stacked item or -1 upon failure.
@param  stack The Ascii Object base poiner.
@param  item  The item to push onto the obj. */
template <typename T = SIN, typename SIZ = SIN>
SIZ TStackPush(TStack<SIZ>* stack, const T& item) {
  D_ASSERT(stack);
  SIZ size = stack->size, count = stack->count;
  if (count >= size) return -1;
  D_COUT(" Pushing:" << item << " size:" << size << " count:" << count);
  D_COUT("\n| Before:" << Charsf(stack, TStackSizeOf<T, SIZ>(size)));

  T* elements = TStackStart<T, SIZ>(stack);
  elements[count++] = item;
  stack->count = count;
  D_COUT("\n| After:" << Charsf(stack, TStackSizeOf<T, SIZ>(size)));
  return count - 1;
}

/* Adds the given item to the stop of the obj.
@return The index of the newly stacked item or -1 upon failure.
@param  stack The Ascii Object base poiner.
@param  item  The item to push onto the obj. */
template <typename T = SIN, typename SIZ = SIN, typename BUF = Nil>
SIZ TStackPush(AArray<T, SIZ, BUF>& obj, const T& item) {
  TStack<SIZ>* stack = obj.BeginAs<TStack<SIZ>>();
  SIZ index = TStackPush<T, SIZ>(stack, item);
  if (index < 0) {
    D_COUT("\nStack overflow! Autogrowing...");
    TStackGrow<T, SIZ>(obj.Auto());
    stack = obj.BeginAs<TStack<SIZ>>();
    T* items = TStackStart<T, SIZ>(stack);
    SIZ count = stack->count;
    items[count++] = item;
    stack->count = count;
    return count - 1;
  }
  return index;
}

/* Adds the given items to the stop of the obj.
@return The index of the newly stacked item or -1 upon failure.
@param  stack The Ascii Object base poiner.
@param  items  The  items to push onto the obj.
@param  items_count The number of items to push. */
template <typename T = SIN, typename SIZ = SIN, typename BUF = Nil>
SIZ TStackPush(AArray<T, SIZ, BUF>& obj, const T* items, SIZ items_count) {
  D_ASSERT(items);
  D_ASSERT(items_count >= 0);
  D_PRINTF("\nPushing %i items:", (SIN)items_count);
  SIZ count = obj->count;
  for (SIN i = 0; i < count; ++i) TStackPush<T, SIZ>(obj, items[i]);
  return 0;
}

/* Pops the top item off of the obj.
@note We do not delete the item at the
@param  a The obj.
@return The item popped off the obj. */
template <typename T = SIN, typename SIZ = SIN>
T TStackPop(TStack<SIZ>* stack) {
  A_ASSERT(stack);
  SIZ count = stack->count;
  if (count == 0) return 0;
  T* items = TStackStart<T, SIZ>(stack);
  stack->count = count - 1;
  T item = items[count - 1];
  return item;
}

/* Removes an element from the given array.
@return The new count of the stack. */
template <typename T = SIW, typename SIZ = SIW>
inline SIZ TStackRemove(T* elements, SIZ count, SIZ index) {
  A_ASSERT(elements);
  if (index < 0 || index >= count) return -1;
  elements += index;
  T* elements_end = elements + --count;
  while (elements <= elements_end) *elements++ = *elements;
  return count;
}

/* Removes the given index from the obj.
@param  stack The Ascii Object base poiner.
@param  index The index the item to remove.
@return True if the index is out of bounds. */
template <typename T = SIN, typename SIZ = SIN>
SIZ TStackRemove(TStack<SIZ>* stack, SIZ index) {
  A_ASSERT(stack);
  SIZ result =
      TStackRemove<T, SIZ>(TStackStart<T, SIZ>(stack), stack->count, index);
  if (result < 0) return result;
  stack->count = result;
  return result;
}

/* Returns true if the given obj contains the given address.
@return false upon failure. */
template <typename T = SIN, typename SIZ = SIN>
BOL TStackContains(TStack<SIZ>* stack, void* address) {
  A_ASSERT(stack);
  CH1 *ptr = reinterpret_cast<CH1*>(stack),
      *adr = reinterpret_cast<CH1*>(address);
  if (adr < ptr) return false;
  if (adr >= ptr + stack->size_array) return false;
  return true;
}

/* The obj size in words. */
template <typename T = SIN, typename SIZ = SIN>
inline SIZ TStackSizeWords(SIZ count) {
  return TStackSizeMin<T, SIZ>(count) / sizeof(UIW);
}

/* An ASCII Stack Autoject.

# Stack Memory Map

@code
+----------------+
|  Packed Stack  |  <-- Only if header_size = 0
|----------------|
| 64-bit Aligned |
|     Buffer     |
|----------------|
| Stack Elements |
|----------------|  +
|  Stack struct  |  |
+----------------+ 0x0
@endcode
*/
template <typename T = SIN, typename SIZ = SIN,
          SIZ kSize_ = kStackCountMaxDefault,
          typename BUF = TSocket<kSize_, T, SIZ, TStack<SIZ>>>
class AStack {
  AArray<T, SIZ, BUF> obj_;  //< An Auto-Array.

 public:
  /* Initializes a stack of n elements to whatever can fit in the BUF. */
  AStack() {
    D_SOCKET_WIPE(Start(), SizeBytes() - sizeof(TStack<SIZ>));
    This()->count = 0;
  }

  /* Attempts to down-size the BUF or creates a dynamically allocated stack.
  @param size The number of elements in the Array. */
  AStack(SIZ stack_height) : obj_(TStackSize<T, SIZ>(stack_height)) {
    SIZ size_bytes = TStack<SIZ>(stack_height) - sizeof(SIZ);
    D_SOCKET_WIPE(Start(), SizeBytes() - sizeof(TStack<SIZ>));
  }

  /* Copies the items into the obj_.Buffer () with some additional
  empty_elements. */
  AStack(SIZ count_max, const T* items, SIZ items_count)
      : obj_(TStackSize<T, SIZ>(items_count)) {
    TStackPush<T, SIZ>(This().Auto(), items, items_count);
  }

  /* Copies the items into the obj_.Buffer () with some additional
  empty_elements. */
  AStack(const T* items, SIZ items_count)
      : obj_(TStackSize<T, SIZ>(items_count)) {
    TStackPush<T, SIZ>(obj_.Auto(), items, items_count);
  }

  /* Destructs nothing. */
  ~AStack() {}

  /* Creates a dynamically allocated clone. */
  inline UIW* TClone() { TStackClone<T, SIZ>(Auto()); }

  /* Clones the other object.
  @return true upon success and false upon failure. */
  inline BOL Clone(TStack<SIZ>* other) { TStackClone<T, SIZ>(Auto(), other); }

  /* Checks if the given index is a valid element.
  @return true if the index is in bounds. */
  inline BOL InBounds(SIZ index) {
    return TStackInBounds<T, SIZ>(obj_.OBJ(), index);
  }

  /* Gets the max number_ of elements in an obj with the specific index
  width. */
  inline SIZ SizeMax() { return TStackSizeMax<T, SIZ>(); }

  /* Gets the min size of the entire Stack, including header, in bytes. */
  inline SIZ SizeMin() { return TStackSizeMin<T, SIZ>(); }

  /* Gets the max elements that can fit in the stack buffer. */
  inline SIZ Height() { return This()->size; }

  /* Gets the count of the items on the obj. */
  inline SIZ Count() { return This()->count; }

  /* Gets the size of the entire Stack, including header, in bytes. */
  inline SIZ SizeBytes() { return TStackSizeOf<T, SIZ>(Height()); }

  /* Gets a pointer to the first element in the obj. */
  inline T* Start() { return TStackStart<T, SIZ>(This()); }

  /* Gets a pointer to the first element in the obj. */
  inline T* Stop() { return Start() + Count(); }

  /* Inserts the item into the obj at the given index.
  @return -1 if a is nil and -2 if the obj is full.
  @param item  The item to insert.
  @param index The index to insert at. */
  inline T Insert(T item, T index) {
    return AStack<T, SIZ>(Auto(), item, index);
  }
  /* Adds the given item to the stop of the obj.
  @return The index of the newly stacked item.
  @param  item The item to push onto the obj. */
  inline SIZ Push(const T& item) { return TStackPush<T, SIZ>(Auto(), item); }

  /* Adds the given item to the stop of the obj.
  @return The index of the newly stacked item.
  @param  item The item to push onto the obj. */
  inline SIZ Push(T* item, SIZ item_count) {
    return TStackPush<T, SIZ>(Auto(), item, item_count);
  }

  /* Pops the top item off of the obj.
  @return The item popped off the obj. */
  inline T Pop() { return TStackPop<T, SIZ>(This()); }

  /* Removes the given index from the obj.
  @return True if the index is out of bounds.
  @param  index The index the item to remove. */
  inline BOL Remove(SIZ index) { return TStackRemove<T, SIZ>(This(), index); }

  /* Peeks the top item off of the obj without popping it.
  @return The item popped off the obj. */
  inline T Peek() { return TStackPeek<T, SIZ>(Auto()); }

  /* Gets the element at the given index.
  @return -1 if a is nil and -2 if the index is out of bounds.
  @param  index The index of the element to get. */
  inline T Get(SIZ index) { return TStackGet<T, SIZ>(Auto(), index); }

  /* Returns true if the given obj contains the given address.
  @return false upon failure. */
  inline BOL Contains(void* address) {
    return TStackContains<T, SIZ>(Auto(), address);
  }

  /* Resizes the obj to the new_count.
  @return False upon failure. */
  inline BOL Resize(SIZ new_count) {
    return TStackResize<T, SIZ>(obj_, new_count);
  }

  /* Doubles the size of the obj.
  @return False upon failure. */
  inline BOL Grow() { return TStackGrow<T, SIZ>(obj_.Auto()); }

  /* Gets this ASCII Object. */
  inline TStack<SIZ>* This() {
    return reinterpret_cast<TStack<SIZ>*>(obj_.Begin());
  }

  /* Gets this AArray. */
  inline AArray<T, SIZ, BUF>& Auto() { return obj_; }

  /* Prints this object to a Printer. */
  template <typename Printer>
  inline Printer& PrintTo(Printer& o) {
    return TStackPrint<Printer, T, SIZ>(o, This());
  }

  /* Prints this object to the given UTF. */
  inline void COut() { PrintTo<_::COut>(_::COut().Star()); }

  /* Gets a reference to the given element index. */
  inline T& operator[](SIW index) { return Start()[index]; }

  /* Gets a const reference to the given element index. */
  inline const T& operator[](SIW index) const { return Start()[index]; }
};  // namespace _

}  // namespace _

template <typename T = SIN, typename SIZ = SIN, typename BUF = _::Nil>
_::AArray<T, SIZ, BUF>& operator<<(_::AArray<T, SIZ, BUF>& obj, T item) {
  obj.Push(item);
  return obj;
}

template <typename T = SIN, typename SIZ = SIN, typename BUF = _::Nil>
_::AArray<T, SIZ, BUF>& operator>>(T& item, _::AArray<T, SIZ, BUF>& obj) {
  item = obj.Pop();
  return obj;
}

#endif
#endif

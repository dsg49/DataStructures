// FILE: Sequence.cpp
// CLASS IMPLEMENTED: sequence (see sequence.h for documentation)
// INVARIANT for the sequence ADT:
//   1. The number of items in the sequence is in the member variable
//      used;
//   2. The actual items of the sequence are stored in a partially
//      filled array. The array is a dynamic array, pointed to by
//      the member variable data. For an empty sequence, we do not
//      care what is stored in any of data; for a non-empty sequence
//      the items in the sequence are stored in data[0] through
//      data[used-1], and we don't care what's in the rest of data.
//   3. The size of the dynamic array is in the member variable
//      capacity.
//   4. The index of the current item is in the member variable
//      current_index. If there is no valid current item, then
//      current_index will be set to the same number as used.
//      NOTE: Setting current_index to be the same as used to
//            indicate "no current item exists" is a good choice
//            for at least the following reasons:
//            (a) For a non-empty sequence, used is non-zero and
//                a current_index equal to used indexes an element
//                that is (just) outside the valid range. This
//                gives us a simple and useful way to indicate
//                whether the sequence has a current item or not:
//                a current_index in the valid range indicates
//                that there's a current item, and a current_index
//                outside the valid range indicates otherwise.
//            (b) The rule remains applicable for an empty sequence,
//                where used is zero: there can't be any current
//                item in an empty sequence, so we set current_index
//                to zero (= used), which is (sort of just) outside
//                the valid range (no index is valid in this case).
//            (c) It simplifies the logic for implementing the
//                advance function: when the precondition is met
//                (sequence has a current item), simply incrementing
//                the current_index takes care of fulfilling the
//                postcondition for the function for both of the two
//                possible scenarios (current item is and is not the
//                last item in the sequence).

#include <cassert>
#include "Sequence.h"
#include <iostream>
#include <cstdlib>

using namespace std;

namespace CS3358_SSII_2015
{
   sequence::sequence(size_type initial_capacity)
      : used(0),
        current_index(used),
        capacity(initial_capacity)
   {
      if (capacity == 0)
         capacity = 1;

      data = new value_type[capacity];
   }

   sequence::sequence(const sequence& source)
      : used(source.used),
        current_index(source.current_index),
        capacity(source.capacity)
   {
      data = new value_type[source.capacity];

      for (size_type i = 0; i < used; i++)
         data[i] = source.data[i];
   }

   sequence::~sequence()
   {
      delete [] data;
   }

   void sequence::resize(size_type new_capacity)
   {
      // Set new_capacity to used in this case, in order to
      // preserve existing data
      if (new_capacity < used)
         new_capacity = used;

      if (new_capacity <= 0)
         new_capacity = 1;

      capacity = new_capacity;

      value_type *temp;

      temp = new value_type[capacity];

      // Copy existing relevant elements in data[] to temp[]
      for (size_type i = 0; i < used; i++)
         temp[i] = data[i];

      delete [] data;

      data = temp;
   }

   void sequence::start()
   {
      current_index = 0;
   }

   void sequence::advance()
   {
      if (!is_item())
         current_index = used;
      else
         current_index++;
   }

   void sequence::insert(const value_type& entry)
   {
      // Resize if full
      if (used == capacity)
         resize(size_type ((1.25 * capacity) + 1));

      // If no current item
      if (current_index == used)
         current_index = 0;

      // Shift elements
      size_type i = used;

      while (i > current_index)
      {
         data[i] = data[i - 1];

         i--;
      }

      used++;

      // Add entry to front of sequence
      data[current_index] = entry;
   }

   void sequence::attach(const value_type& entry)
   {
      // Resize if full
      if (used == capacity)
         resize(size_type ((1.25 * capacity) + 1));

      if (current_index == used)
      {
         data[current_index] = entry;

         used++;

         return;
      }

      if (current_index == used - 1)
      {
         current_index++;

         used++;

         data[current_index] = entry;

         return;
      }

      // Shift elements
      size_type i = used;

      while (i > current_index)
      {
         data[i] = data[i - 1];

         i--;
      }

      current_index++;

      used++;

      data[current_index] = entry;
   }

   void sequence::remove_current()
   {
      assert (is_item());

      // Attempting to remove in the case that no relevant elements
      // exist after the current_index
      if (current_index == used - 1)
      {
         used--;

         current_index = used;

         return;
      }

      // Shift elements
      for (size_type i = current_index; i < used; i++)
         data[i] = data[i + 1];

      used--;
   }

   sequence& sequence::operator=(const sequence& source)
   {
      this->used = source.used;

      this->current_index = source.current_index;

      // If source.capacity > object's capacity, then
      // set capacity of array to match source
      if (this->capacity < source.capacity)
      {
         this->capacity = source.capacity;

         delete [] data;

         this->data = new value_type[source.capacity];
      }

      // Copy contents of source.data[] to data[]
      for (size_type i = 0; i < source.used; i++)
         data[i] = source.data[i];

      return *this;
   }

   sequence::size_type sequence::size() const
   {
      return used;
   }

   bool sequence::is_item() const
   {
      bool validItem = true;

      if (current_index == used)
         validItem = false; // no valid current item

      return validItem;
   }

   sequence::value_type sequence::current() const
   {
      assert(is_item());

      return data[current_index];
   }

}

// FILE: IntSet.cpp - header file for IntSet class
//       Implementation file for the IntStore class
//       (See IntSet.h for documentation.)
// INVARIANT for the IntSet class:
// (1) Distinct int values of the IntSet are stored in a 1-D,
//     dynamic array whose size is stored in member variable
//     capacity; the member variable data references the array.
// (2) The distinct int value with earliest membership is stored
//     in data[0], the distinct int value with the 2nd-earliest
//     membership is stored in data[1], and so on.
//     Note: No "prior membership" information is tracked; i.e.,
//           if an int value that was previously a member (but its
//           earlier membership ended due to removal) becomes a
//           member again, the timing of its membership (relative
//           to other existing members) is the same as if that int
//           value was never a member before.
//     Note: Re-introduction of an int value that is already an
//           existing member (such as through the add operation)
//           has no effect on the "membership timing" of that int
//           value.
// (4) The # of distinct int values the IntSet currently contains
//     is stored in the member variable used.
// (5) Except when the IntSet is empty (used == 0), ALL elements
//     of data from data[0] until data[used - 1] contain relevant
//     distinct int values; i.e., all relevant distinct int values
//     appear together (no "holes" among them) starting from the
//     beginning of the data array.
// (6) We DON'T care what is stored in any of the array elements
//     from data[used] through data[capacity - 1].
//     Note: This applies also when the IntSet is empty (used == 0)
//           in which case we DON'T care what is stored in any of
//           the data array elements.
//     Note: A distinct int value in the IntSet can be any of the
//           values an int can represent (from the most negative
//           through 0 to the most positive), so there is no
//           particular int value that can be used to indicate an
//           irrelevant value. But there's no need for such an
//           "indicator value" since all relevant distinct int
//           values appear together starting from the beginning of
//           the data array and used (if properly initialized and
//           maintained) should tell which elements of the data
//           array are actually relevant.
//
// DOCUMENTATION for private member (helper) function:
//   void resize(int new_capacity)
//     Pre:  (none)
//           Note: Recall that one of the things a constructor
//                 has to do is to make sure that the object
//                 created BEGINS to be consistent with the
//                 class invariant. Thus, resize() should not
//                 be used within constructors unless it is at
//                 a point where the class invariant has already
//                 been made to hold true.
//     Post: The capacity (size of the dynamic array) of the
//           invoking IntSet is changed to new_capacity...
//           ...EXCEPT when new_capacity would not allow the
//           invoking IntSet to preserve current contents (i.e.,
//           value for new_capacity is invalid or too low for the
//           IntSet to represent the existing collection),...
//           ...IN WHICH CASE the capacity of the invoking IntSet
//           is set to "the minimum that is needed" (which is the
//           same as "exactly what is needed") to preserve current
//           contents...
//           ...BUT if "exactly what is needed" is 0 (i.e. existing
//           collection is empty) then the capacity should be
//           further adjusted to 1 or DEFAULT_CAPACITY (since we
//           don't want to request dynamic arrays of size 0).
//           The collection represented by the invoking IntSet
//           remains unchanged.
//           If reallocation of dynamic array is unsuccessful, an
//           error message to the effect is displayed and the
//           program unconditionally terminated.

#include "IntSet.h"
#include <iostream>
#include <cassert>
#include <algorithm>
#include <cstdlib>

using namespace std;

void IntSet::resize(int new_capacity)
{
   if (new_capacity < used)
      new_capacity = used;

   if (new_capacity < DEFAULT_CAPACITY)
      new_capacity = DEFAULT_CAPACITY;

   capacity = new_capacity;

   int * newData = new int[capacity];

   for (int i = 0; i < used; i++)
      newData[i] = data[i];

   delete [] data;

   data = newData;
}

IntSet::IntSet(int initial_capacity) : capacity(initial_capacity), used(0)
{
   if (capacity < 1)
      capacity = DEFAULT_CAPACITY;

   data = new int[capacity];
}

IntSet::IntSet(const IntSet& src) : capacity(src.capacity), used(src.used)
{
   data = new int[capacity];

   for (int i = 0; i < used; ++i)
         data[i] = src.data[i];
}

IntSet::~IntSet()
{
   delete [] data;
}

IntSet& IntSet::operator=(const IntSet& rhs)
{
   if (this != &rhs)
   {
      int* newData = new int[rhs.capacity];

      for (int i = 0; i < rhs.used; ++i)
         newData[i] = rhs.data[i];

      delete [] data;

      data = newData;

      capacity = rhs.capacity;

      used = rhs.used;
   }

   return *this;
}

int IntSet::size() const
{
   return used;
}

bool IntSet::isEmpty() const
{
   if (size() == 0)
      return true;
   else
      return false;
}

bool IntSet::contains(int anInt) const
{
   bool found;

   // Immediately return if data[] is empty
   if (isEmpty())
      found = false;
   else //Otherwise search data[] for anInt
   {
      int index = 0;

      while (found != true && index < used)
      {
         if (data[index] == anInt)
            found = true;
         else
            found = false;

         index++;
      }
   }

   return found;
}

bool IntSet::isSubsetOf(const IntSet& otherIntSet) const
{
   bool isSubset;

   if (isEmpty())
      isSubset = true;
   else if (used > otherIntSet.used)
      isSubset = false;
   else
   {
      bool found;

      for (int i = 0; i < used; i++)
      {
         found = otherIntSet.contains(data[i]);

         if (found == true)
         {
            isSubset = true;
         }
         else
         {
            isSubset = false;
            break;
         }
      }
   }

   return isSubset;
}

void IntSet::DumpData(ostream& out) const
{  // already implemented ... DON'T change anything
   if (used > 0)
   {
      out << data[0];
      for (int i = 1; i < used; ++i)
         out << "  " << data[i];
   }
}

IntSet IntSet::unionWith(const IntSet& otherIntSet) const
{
   // Create IntSet objects for intersection, and both difference sets
   // for invoking and otherIntSet
   IntSet intersectSet;
   intersectSet = intersect(otherIntSet);

   IntSet diffSetA;
   diffSetA = subtract(otherIntSet);

   IntSet diffSetB;
   diffSetB = otherIntSet.subtract(*this);

   // Create IntSet object that will contain all elements
   // of invoking and otherIntSet
   IntSet unionSet;

   unionSet.used = intersectSet.used + diffSetA.used + diffSetB.used;

   // Add all relevant IntSet objects
   int counter = 0;

   for (int i = 0; i < intersectSet.used; i++)
   {
      unionSet.data[counter] = intersectSet.data[i];
      counter++;
   }

   for (int i = 0; i < diffSetA.used; i++)
   {
      unionSet.data[counter] = diffSetA.data[i];
      counter++;
   }

   for (int i = 0; i < diffSetB.used; i++)
   {
      unionSet.data[counter] = diffSetB.data[i];
      counter++;
   }

   return unionSet;
}

IntSet IntSet::intersect(const IntSet& otherIntSet) const
{
   IntSet intersection;

   // Initially, intersection.used is as large as invoking IntSet.used
   intersection.used = used;

   // Return empty set if empty
   if (otherIntSet.isEmpty())
      intersection.used = otherIntSet.used;
   else
   {
      int foundAlike = 0;

      // Remove unlike elements from intersection.data[]
      for (int i = 0; i < used; i++)
      {
         for (int j = 0; j < otherIntSet.used; j++)
         {
            if (data[i] == otherIntSet.data[j])
            {
               intersection.data[foundAlike] = otherIntSet.data[j];
               foundAlike++;
            }
         }
      }

      // Set intersection.used equal to number of like elements found
      intersection.used = foundAlike;
   }

   return intersection;
}

IntSet IntSet::subtract(const IntSet& otherIntSet) const
{
   IntSet diff;

   diff.used = used;

   if (otherIntSet.isEmpty())
   {
      for (int i = 0; i < used; i++)
         diff.data[i] = data[i];
   }
   else
   {
      // Copy data[] to diff.data[]
      for (int i = 0; i < used; i++)
         diff.data[i] = data[i];

      // Remove shared elements from diff.data[]
      for (int i = 0; i < diff.used; i++)
      {
         for (int j = 0; j < otherIntSet.used; j++)
         {
            if (diff.data[i] == otherIntSet.data[j])
               diff.remove(diff.data[i]);
         }
      }
   }

   return diff;
}

void IntSet::reset()
{
   used = 0; // reset integer count
}

bool IntSet::add(int anInt)
{
   bool addSuccessful = true;

   // If array is empty, just add
   if (isEmpty())
   {
      data[used] = anInt;

      used++;

      addSuccessful = true;
   }
   else
   {
      if (contains(anInt) != true)
         addSuccessful = false;

      if (used >= capacity)
         resize(int(1.5*capacity) + 1);

      // Add anInt if the pre conditions are satisfied
      // Note: If user inputs "22world55" for example, the program will still
      // accept "22" as a valid integer input and disregard the rest.
      data[used] = anInt;

      used++;

      addSuccessful = true;
   }

   return addSuccessful;
}

bool IntSet::remove(int anInt)
{
   bool removeSuccess = false;

   // Immediately returns if anInt is not in data[] or
   // if data[] is empty
   if (!contains(anInt) || isEmpty())
      return removeSuccess;

   // Search data[] for anInt and remove
   for (int i = 0; i < used; i++)
   {
      if (data[i] == anInt)
      {
         for (int j = i; j < used - 1; j++)
            data[j] = data[j + 1];

         copy(data + i, data + used, data + i);

         used--;

         removeSuccess = true;

         break;
      }
   }

   return removeSuccess;
}

bool operator==(const IntSet& is1, const IntSet& is2)
{
   bool same;

   if (is1.isEmpty() && is2.isEmpty())
      same = true;
   else if (is1.size() != is2.size())
      same = false;
   else if (is1.size() == is2.size())
   {
      if (is1.isSubsetOf(is2) && is2.isSubsetOf(is1))
         same = true;
   }

   return same;
}

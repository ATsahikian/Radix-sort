#include <vector>
#include <algorithm>
#include <cassert>

using namespace std;

int getDigit(int value, size_t ndigit, size_t base)
{
   while (ndigit > 0)
   {
      value /= base;
      ndigit--;
   }
   return value % base;
}

void countsort(vector<int> & tosort, size_t ndigit, size_t nbuckets)
{
   vector<vector<int>> buckets(nbuckets);
   
   // put values to buckets
   for (auto v : tosort)
   {
      const int digit = getDigit(v, ndigit, nbuckets);
      buckets[digit].push_back(v);
   }

   tosort.clear();

   // join buckets
   for (auto bucket : buckets)
   {
      tosort.insert(tosort.end(), bucket.cbegin(), bucket.cend());
   }
}

void radixsort(vector<int> & tosort)
{
   const size_t base = tosort.size();

   int maxvalue = *max_element(tosort.cbegin(), tosort.cend());

   for (int ndigit = 0; maxvalue > 0; ndigit++, maxvalue /= base)
   {
      countsort(tosort, ndigit, base);
   }
}

int main()
{
   // test cases for getDigit
   assert(3 == getDigit(123, 0, 10));
   assert(2 == getDigit(123, 1, 10));
   assert(1 == getDigit(123, 2, 10));
   assert(0 == getDigit(123, 3, 10));

   // test cases for countsort
   vector<int> tosort = {1, 33, 2, 3, 13, 23};
   countsort(tosort, 0, 10);
   countsort(tosort, 1, 10);
   assert(is_sorted(tosort.cbegin(), tosort.cend()));

   tosort = {23, 33, 2, 3, 1, 923};
   countsort(tosort, 0, 10);
   countsort(tosort, 1, 10);
   countsort(tosort, 2, 10);
   assert(is_sorted(tosort.cbegin(), tosort.cend()));

   // test cases for radixsort
   tosort = {1, 33, 2, 3, 13, 23};
   radixsort(tosort);
   assert(is_sorted(tosort.cbegin(), tosort.cend()));

   tosort = {999, 8888, 55555, 3, 13, 23, 1555};
   radixsort(tosort);
   assert(is_sorted(tosort.cbegin(), tosort.cend()));

   tosort = {9, 8, 7, 6, 5, 4, 3};
   radixsort(tosort);
   assert(is_sorted(tosort.cbegin(), tosort.cend()));

   tosort = {0, 2, 3, 4, 5, 6, 7};
   radixsort(tosort);
   assert(is_sorted(tosort.cbegin(), tosort.cend()));

   return 0;
}

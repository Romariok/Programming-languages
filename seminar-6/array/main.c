#include "array.h"



int main()
{
   struct array a = newArray(15);

   for (size_t i = 0; i <= 100; i++)
   {
      append(&a, i * i);
   }
   printArray(&a, stdout);
   return 0;
}
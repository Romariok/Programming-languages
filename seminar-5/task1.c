#include <stdio.h>

#define print_var(x) printf(#x " is %d", x )

int main() {
   int x = 156;
   const int Y = 6532;



   print_var(42);
   print_var(x);
   print_var(__INT32_MAX__);
   print_var(Y);

   return 0;
}


// gcc -E  -o task1.o task1.c

// # 5 "task1.c"
// int main() {
//    int x = 156;
//    const int Y = 6532;



//    printf("42" " is %d", 42 );
//    printf("x" " is %d", x );
//    printf("__INT32_MAX__" " is %d", 0x7fffffff );
//    printf("Y" " is %d", Y );

//    return 0;
// }


/* hello.c */
#include <stdlib.h>
#include <stdio.h>


void print_file(char *filename);

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <pathname>\n", argv[0]);
        exit(EXIT_FAILURE);
    }
    print_file(argv[1]);
    return 0;

}

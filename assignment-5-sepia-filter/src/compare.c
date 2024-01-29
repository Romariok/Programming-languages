#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main()
{
    char *commands[] = {
        "./bin/main ./img/huge.bmp ./img/output_c.bmp c",
        "./bin/main ./img/huge.bmp ./img/output_asm.bmp asm",
        NULL};


    struct timespec start, end;

    for (int i = 0; commands[i] != NULL; i++)
    {
        printf("Running command: %s\n", commands[i]);

        float sumTime = 0.0;
        for (int j = 0; j < 1; j++)
        {
            clock_gettime(CLOCK_REALTIME, &start);
            int status = system(commands[i]);
            clock_gettime(CLOCK_REALTIME, &end);


            if (status == -1)
            {
                printf("System call failed.\n");
                return 1;
            }

            float time_taken = (end.tv_sec - start.tv_sec) +
                                (end.tv_nsec - start.tv_nsec) / 1000000000.0;
            sumTime += time_taken;
        }

        printf("Execution time: %.15f seconds\n", sumTime / 10.0);
    }

    return 0;
}
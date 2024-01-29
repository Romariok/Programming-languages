#include "bmp.h"
#include "image.h"
#include "transformation.h"
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#define ARGS 4

int main(int argc, char **argv)
{
    const char *argv_angles[] = {"0", "90", "-90", "180", "-180", "270", "-270"};
    if (argc != ARGS)
    {
        fprintf(stderr, "Usage: %s <source-image> <transformed-image> <angle>\n", argv[0]);
        return -1;
    }
    bool is_angle = false;
    for (size_t i = 0; i < 7; i++)
    {
        if (strcmp(argv[3], argv_angles[i]) == 0)
        {
            is_angle = true;
        }
    }
    if (!is_angle)
    {
        fprintf(stderr, "Angle can be only 0, 90, -90, 180, -180, 270, -270\n");
        return -1;
    }

    FILE *f = fopen(argv[1], "r");
    if (!f)
    {
        out_read_status(READ_ERROR);
        return -1;
    }

    struct image source = {0};
    enum read_status read_status = from_bmp(f, &source);
    out_read_status(read_status);
    fclose(f);
    if (read_status != READ_OK)
    {
        image_destroy(&source);
        return -1;
    }

    struct image transformed = rotate(source, argv[3]);

    FILE *f_out = fopen(argv[2], "wb");
    if (!f_out)
    {
        out_read_status(READ_ERROR);
        image_destroy(&source);
        if (strcmp(argv[3], "0") != 0)
            image_destroy(&transformed);
        return -1;
    }

    enum write_status write_status = to_bmp(f_out, &transformed);
    out_write_status(write_status);
    fclose(f_out);
    if (write_status != WRITE_OK)
    {
        image_destroy(&source);
        if (strcmp(argv[3], "0") != 0)
            image_destroy(&transformed);
        return -1;
    }

    if (strcmp(argv[3], "0") != 0)
        image_destroy(&transformed);
    image_destroy(&source);
    return 0;
}

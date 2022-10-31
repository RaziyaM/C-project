#include "my_lib.h"

int main(int argc, char *argv[])
{
    int filesCount = argc - 1;
    int i = 1;
    if (filesCount < 1)
    {
        fprintf(stderr, "\n\nYou did not passed any source files to the assembler!\n\n");
        exit(1);
    }
    while (--argc)
    {
        step1_speard_macro(argv[i]);
        step2_built_symbol_table(argv[i]);
        i++;
    }
    return 0;
}

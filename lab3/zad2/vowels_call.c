#include <sys/stat.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <sysexits.h>
#include <unistd.h>

int
main(int argc, char *argv[])
{
        if(argc >1)
                exit(syscall(210, argv[1]));
        else
                exit(syscall(210, argv[0]));
}

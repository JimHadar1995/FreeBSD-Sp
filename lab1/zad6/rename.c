#include <sys/cdefs.h>

#include <sys/types.h>
#include <sys/acl.h>
#include <sys/param.h>
#include <sys/time.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <sys/mount.h>

#include <err.h>
#include <errno.h>
#include <fcntl.h>
#include <grp.h>
#include <limits.h>
#include <paths.h>
#include <pwd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sysexits.h>
#include <unistd.h>

#define EXEC_FAILED 127

static int      do_move(const char *, const char *);

int
main(int argc, char *argv[])
{
        size_t baselen, len;
        int rval;
        char *p, *endp;
        struct stat sb;
        int ch;
        char path[PATH_MAX];

        if (argc < 2){
                printf("too small args\n");
                return 1;
        }
        argc -= optind;
        argv += optind;
        char *to;
        (void)strcpy(to, argv[1]);


        exit(do_move(argv[0], argv[1]));
}

static int
do_move(const char *from, const char *to)
{
        struct stat sb;
        int ask, ch, first;
        char modep[15];
        if(!rename(from, to)){
                printf("\nrename: %s -> %s\n", from, to);
                return 0;
        }
        else{
                printf("\nerror rename: %s -> %s\n", from, to);
                return 1;
        }
}


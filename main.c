#include <stdio.h>
#include <dlfcn.h>
#include <unistd.h>
#include <sys/stat.h>
#include <time.h>
#include <errno.h>

int main()
{
    unsigned long last_mod = 0;
    void *lib_handle = 0;
    char *libpath = "bin/lib.dylib";

    while (true)
    {
        struct stat info;

        int res = stat(libpath, &info);
        if (res)
        {
            fprintf(stderr, "stat failed %d\n", errno);
        }

        if (!res && info.st_mtime != last_mod)
        {
            last_mod = info.st_mtime;

            if (lib_handle)
            {
                printf("closing %s\n", libpath);
                dlclose(libpath);
                // 1_000_000_000 nanoseconds is 1 second
                nanosleep(&(const struct timespec){0, 1000000}, NULL);
            }

            lib_handle = dlopen(libpath, RTLD_NOW | RTLD_LOCAL);

            if (!lib_handle)
            {
                fprintf(stderr, "could not link lib\n");
                return 1;
            }

            int (*adder)(int, int) = dlsym(lib_handle, "adder");
            printf("hello! %d\n", adder(1300, 37));
        }

        // sleep for 1 ms to not overburden CPU
        nanosleep(&(const struct timespec){0, 1000000}, NULL);
    }

    if (lib_handle)
    {
        printf("closing %s\n", libpath);
        dlclose(libpath);
    }

    printf("done\n");

    return 0;
}
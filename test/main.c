#include <stdio.h>
#include <unistd.h>
#include <time.h>

#include "../hotreload_dll.h"

int main()
{
    unsigned long last_mod = 0;
    void *lib_handle = 0;
    char *libpath = "bin/lib.dylib";

    while (true)
    {
        // result is 1 if it was (re)loaded
        //           0 if no change has happened
        //          -1 on error
        int result = hotreload_dll(libpath, &lib_handle, &last_mod);

        if (result == 1)
        {
            int (*adder)(int, int) = dlsym(lib_handle, "adder");
            printf("hello! %d\n", adder(1300, 37));
        }

        // sleep for 1 ms to not overburden CPU
        nanosleep(&(const struct timespec){0, 1000000}, NULL);
    }

    printf("done\n");

    return 0;
}
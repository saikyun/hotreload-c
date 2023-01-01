#ifndef HOTRELOAD_DLL
#define HOTRELOAD_DLL

#include <stdio.h>
#include <dlfcn.h>
#include <errno.h>
#include <sys/stat.h>


// returns   1 if dll was (re)loaded
//           0 if no change has happened to dll since last load
//          -1 on error
int hotreload_dll(const char *libpath, void **lib_handle, unsigned long *last_mod)
{
    struct stat info;

    int res = stat(libpath, &info);
    if (res)
    {
        fprintf(stderr, "stat failed %d\n", errno);
        return -1;
    }

    if (info.st_mtime != *last_mod)
    {
        *last_mod = info.st_mtime;

        if (*lib_handle)
        {
            printf("closing %s\n", libpath);
            dlclose(*lib_handle);
        }

        *lib_handle = dlopen(libpath, RTLD_NOW | RTLD_LOCAL);

        if (!*lib_handle)
        {
            fprintf(stderr, "could not link lib: %s\n", dlerror());
            return -1;
        }
        else
        {
            return 1;
        }
    }

    return 0;
}

#endif
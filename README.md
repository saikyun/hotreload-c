# hotreload-c
reload dll's while an application is running

# how to use

Look at `test/main.c`. The important parts are:
```
#include "../hotreload_dll.h"

...

unsigned long last_mod = 0;
void *lib_handle = 0;
char *libpath = "bin/lib.dylib";

...
// result is 1 if it was (re)loaded
//           0 if no change has happened
//          -1 on error
int result = hotreload_dll(libpath, &lib_handle, &last_mod);

if (result == 1)
{
    int (*adder)(int, int) = dlsym(lib_handle, "adder");
    printf("hello! %d\n", adder(1300, 37));
}
```

`hotreload_dll` will load the DLL the first time it is run, then on later runs it will dlclose / dlopen the DLL if the modification date of the DLL as reported by `stat` is greater than `last_mod`.
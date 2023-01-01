# hotreload-c
Reload dll's while an application is running.

Only works on MacOS so far.

## how to use

Look at `test/main.c`. The important parts are:

```c
#include "../hotreload_dll.h"

// ...

unsigned long last_mod = 0;
void *lib_handle = 0;
char *libpath = "bin/lib.dylib";

// ...

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

## testing

```
git clonehttps://github.com/saikyun/hotreload-c
cd hotreload-c
chmod u+x scripts/macos/compile-and-run
./scripts/macos/compile-and-run
```

Modify `test/lib.c`.

In another terminal:

```
cc -dynamic test/lib.c -o bin/lib.dylib
```


## license

This project is dual-licensed under the Unlicense and MIT licenses.
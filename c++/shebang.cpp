#!/usr/bin/env cling
#if 0
#endif

/** This is an experiment to test C++ as a scripting language. ie running a
 * 'main.cpp' file directly from a shebang or other file hint.

I haven't figured the nicest way to do this yet. But ideally it wouldn't require
special embeds into non-C++ file types or anything like that **/

int
main()
{
    return 1;
}

int
shebang()
{ return main(); }

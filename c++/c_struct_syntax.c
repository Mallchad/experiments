
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/** This file is a bunch of experiments of the various ways struct syntax can be constructed.
 * in all its archaic forms
 */


int main()
{
    // Unnamed struct, only used once
    struct { int b; } a;
    // Named struct, not a variable
    struct b { int b; };
    a.b = 5;
    // Variable called 'b'
    struct b b;
    b.b = 5;

    char* name = "Mallchad";
    char copy[256];
    // I can easily get the function wrong like this. and it would crash.
    // strcpy( name, copy );

    // its a little silly of an example but I could make it a struct...
    struct strcpy_args {
        char* destination;
        char* source;
    };
    // and then do
    void strcpy_struct( struct strcpy_args args )
    { strcpy( args.destination, args.source ); }
    struct strcpy_args args = {
        .source = name,
        .destination = copy
    };
    strcpy_struct( args );

    printf("%s\n", copy );
    // no confusion here... the name is right there in black and white...
    // Can even get the args the wrong way around because they're named.

    // Safe
    strcpy( copy, name );
    printf( "Safe\n" );
    // Instant Crash
    strcpy( name, copy );
    printf( "Never Reached\n" );
}

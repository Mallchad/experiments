#include <stdio.h>
#include <memory.h>

typedef char byte;

int main(void)
{
    byte memory_arena[100000] = {};
    memset((void*)memory_arena, 't', sizeof(memory_arena));
    char* t_string = (char*)memory_arena;
    {
        // This is stored in the read-only data section of the binary, so it will stay in memory forever
        t_string = "still in scope \n";

    }
    memory_arena[2] = (byte)' ';
    printf("%s", t_string);
    printf("%d \n", sizeof(memory_arena));
    return 1;
}


int c_out_of_scope_string()
{
    main();
    return 1;
}

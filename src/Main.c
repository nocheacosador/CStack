#include <stdio.h>
#include <string.h>
#include "MemoryAllocation.h"
#include "Stack.h"

int* HeapInt(int val)
{
    int* ptr = (int*)Malloc(sizeof(int));
    *ptr = val;
    return ptr;
}

char* IntToString(void* data)
{
    size_t needed = snprintf(NULL, 0, "%d", *(int*)data) + 1;
    char* buffer = Malloc(needed);
    sprintf(buffer, "%d", *(int*)data);
    return buffer;
}

int main()
{
    Stack stack = Stack_Create();

    char buf[1024];
    int run = 1;

    while (run)
    {
        printf("> ");
        scanf("%1023s", buf);

        if (!strcmp("push", buf))
        {
            int data;
            scanf("%d", &data);

            Stack_Push(&stack, HeapInt(data));
        }
        else if (!strcmp("pop", buf))
        {
            int* data = (int*)Stack_Pop(&stack);

            if (data == NULL) 
                puts("NULL");
            else
            {
                printf("%d\n", *data);
                Free(data);
            }
        }
        else if (!strcmp("peek", buf))
        {
            int* data = (int*)Stack_Peek(&stack);

            if (data == NULL) 
                puts("NULL");
            else
                printf("%d\n", *data);
        }
        else if (!strcmp("isEmpty", buf))
        {
            puts( Stack_IsEmpty(&stack) ? "true" : "false" );
        }
        else if (!strcmp("print", buf))
        {
            puts("Stack:");
            Stack_Print(&stack, IntToString, stdout);
        }
        else if (!strcmp("quit", buf))
        {
            puts("Bye.");
            run = 0;
        }
        else
        {
            printf("Unknown command: '%s'\n", buf);
        }
    }

    while (!Stack_IsEmpty(&stack))
        Free(Stack_Pop(&stack));

    PrintMemoryAllocationReport();
}
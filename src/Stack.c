#include "Stack.h"
#include "MemoryAllocation.h"
#include <assert.h>

void Stack_Push(Stack* stack, void* data)
{
    assert(stack != NULL);

    StackItem* new = (StackItem*)Malloc(sizeof(Stack));
    if (new == NULL) 
    {
        perror("Error while creating new stack item");
        return;
    }

    new->data = data;
    new->next = stack->top;

    stack->top = new;
    stack->size++;
}

void* Stack_Pop(Stack* stack)
{
    assert(stack != NULL);

    if (stack->top == NULL)
    {
        return NULL;
    }

    void* data = stack->top->data;
    StackItem* toFree = stack->top;
    stack->top = stack->top->next;
    Free(toFree);
    stack->size--;
    return data;
}

void* Stack_Peek(const Stack* stack)
{
    assert(stack != NULL);
    return stack->top->data;
}

int Stack_IsEmpty(const Stack* stack)
{
    assert(stack != NULL);
    return stack->top == NULL;
}

void Stack_Delete(Stack* stack)
{
    while (!Stack_IsEmpty(&stack))
        Free(Stack_Pop(&stack));
}

static char* defaultToString(void* data) 
{
    size_t needed = snprintf(NULL, 0, "adress: 0x%p", data) + 1;
    char* buffer = Malloc(needed);
    sprintf(buffer, "adress: 0x%p", data);
    return buffer;
}

void Stack_Print(const Stack* stack, ToStringFunc* toStringFunc, FILE* stream)
{
    assert(stack != NULL);

    if (toStringFunc == NULL) toStringFunc = defaultToString;

    for (StackItem* item = stack->top; item != NULL; item = item->next)
    {
        char* data = toStringFunc(item->data);
        fprintf(stream, "data: %s\n", data);
        Free(data);
    }
    fprintf(stream, "Size: %d\n", stack->size);
}
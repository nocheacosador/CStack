#pragma once

#include <stddef.h>
#include <stdio.h>

/**
 * @brief Stack item
 */
typedef struct StackItem {
    void* data;
    struct StackItem* next;
} StackItem;

/**
 * @brief Stack structure
 */
typedef struct Stack {
    StackItem* top;         // top of the stack
    int size;               // number of elements in the stack
} Stack;

/**
 * @brief Creates empty stack
 * 
 * @return empty stack
 */
static inline Stack Stack_Create() 
{
    return (Stack){ NULL, 0 };
}

/**
 * @brief Pushes data to the top of the stack
 * 
 * @param stack pointer to the stack
 * @param data pointer to data
 */
void Stack_Push(Stack* stack, void* data);


/**
 * @brief Pops (deletes) data from the top of the stack and returns it
 * 
 * @param stack pointer to the stack
 * @return pointer to data
 */
void* Stack_Pop(Stack* stack);

/**
 * @brief Returns pointer to data on the top of the stack
 * 
 * @param stack pointer to the stack
 * @return pointer to data
 */
void* Stack_Peek(const Stack* stack);

/**
 * @brief Checks if stack is empty
 * 
 * @param stack pointer to the stack
 * @return 1 if empty, 0 if not empty
 */
int Stack_IsEmpty(const Stack* stack);

/**
 * @brief Function type for data conversion to string.
 *        Takes in pointer to data that needs to be printed.
 * 
 * @return heap allocated string
 */
typedef char* ToStringFunc(void*);

/**
 * @brief Prints stack content to stream
 * 
 * @param stack pointer to the stack to be printed
 * @param toStringFunc pointer to a function of type `ToStringFunc`,
 *                     if NULL default function is used
 * @param stream where to print
 */
void Stack_Print(const Stack* stack, ToStringFunc* toStringFunc, FILE* stream);

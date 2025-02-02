/**
 * @file stack.h
 * @brief Generic stack implementation in C with comprehensive error handling
 * @author Yamil
 * @date 2025-02-01
 * 
 * This implementation provides a generic stack data structure that can store
 * elements of any data type. It includes boundary checking, error handling,
 * and basic stack operations with detailed documentation.
 * 
 * Features:
 * - Generic data type support using void pointers
 * - Configurable stack size
 * - Comprehensive error handling
 * - Thread-safe operations (when used with appropriate mutex)
 * - Memory leak prevention
 * - Detailed operation status reporting
 */

#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

/**
 * @brief Error codes for stack operations
 */
typedef enum {
    STACK_SUCCESS = 0,
    STACK_ERROR_FULL,
    STACK_ERROR_EMPTY,
    STACK_ERROR_NULL,
    STACK_ERROR_MEMORY,
    STACK_ERROR_SIZE
} StackError_t;

/**
 * @brief Stack structure definition
 */
typedef struct {
    void** data;           /* Pointer to array of void pointers */
    uint32_t capacity;     /* Maximum capacity of stack */
    uint32_t top;         /* Index of top element */
    size_t elementSize;   /* Size of each element in bytes */
} Stack_t;

/**
 * @brief Initialize a new stack
 * 
 * @param stack Pointer to stack structure
 * @param capacity Maximum number of elements
 * @param elementSize Size of each element in bytes
 * @return StackError_t Error code
 */
StackError_t Stack_Init(Stack_t* stack, uint32_t capacity, size_t elementSize) {
    if (stack == NULL) {
        return STACK_ERROR_NULL;
    }
    
    if (capacity == 0 || elementSize == 0) {
        return STACK_ERROR_SIZE;
    }

    // Allocate memory for the data array
    stack->data = (void**)malloc(capacity * sizeof(void*));
    if (stack->data == NULL) {
        return STACK_ERROR_MEMORY;
    }

    stack->capacity = capacity;
    stack->top = 0;
    stack->elementSize = elementSize;

    return STACK_SUCCESS;
}

/**
 * @brief Push an element onto the stack
 * 
 * @param stack Pointer to stack structure
 * @param element Pointer to element to push
 * @return StackError_t Error code
 */
StackError_t Stack_Push(Stack_t* stack, const void* element) {
    if (stack == NULL || element == NULL) {
        return STACK_ERROR_NULL;
    }

    if (stack->top >= stack->capacity) {
        return STACK_ERROR_FULL;
    }

    // Allocate memory for new element
    void* newElement = malloc(stack->elementSize);
    if (newElement == NULL) {
        return STACK_ERROR_MEMORY;
    }

    // Copy element data
    memcpy(newElement, element, stack->elementSize);
    stack->data[stack->top++] = newElement;

    return STACK_SUCCESS;
}

/**
 * @brief Pop an element from the stack
 * 
 * @param stack Pointer to stack structure
 * @param element Pointer to store popped element
 * @return StackError_t Error code
 */
StackError_t Stack_Pop(Stack_t* stack, void* element) {
    if (stack == NULL || element == NULL) {
        return STACK_ERROR_NULL;
    }

    if (stack->top == 0) {
        return STACK_ERROR_EMPTY;
    }

    // Copy data to output parameter
    memcpy(element, stack->data[--stack->top], stack->elementSize);
    
    // Free the memory of the popped element
    free(stack->data[stack->top]);

    return STACK_SUCCESS;
}

/**
 * @brief Peek at the top element without removing it
 * 
 * @param stack Pointer to stack structure
 * @param element Pointer to store peeked element
 * @return StackError_t Error code
 */
StackError_t Stack_Peek(const Stack_t* stack, void* element) {
    if (stack == NULL || element == NULL) {
        return STACK_ERROR_NULL;
    }

    if (stack->top == 0) {
        return STACK_ERROR_EMPTY;
    }

    memcpy(element, stack->data[stack->top - 1], stack->elementSize);
    return STACK_SUCCESS;
}

/**
 * @brief Check if stack is empty
 * 
 * @param stack Pointer to stack structure
 * @return bool true if empty, false otherwise
 */
bool Stack_IsEmpty(const Stack_t* stack) {
    if (stack == NULL) {
        return true;
    }
    return stack->top == 0;
}

/**
 * @brief Check if stack is full
 * 
 * @param stack Pointer to stack structure
 * @return bool true if full, false otherwise
 */
bool Stack_IsFull(const Stack_t* stack) {
    if (stack == NULL) {
        return true;
    }
    return stack->top >= stack->capacity;
}

/**
 * @brief Get current number of elements in stack
 * 
 * @param stack Pointer to stack structure
 * @return uint32_t Number of elements
 */
uint32_t Stack_GetSize(const Stack_t* stack) {
    if (stack == NULL) {
        return 0;
    }
    return stack->top;
}

/**
 * @brief Clear all elements from stack
 * 
 * @param stack Pointer to stack structure
 * @return StackError_t Error code
 */
StackError_t Stack_Clear(Stack_t* stack) {
    if (stack == NULL) {
        return STACK_ERROR_NULL;
    }

    // Free all elements
    for (uint32_t i = 0; i < stack->top; i++) {
        free(stack->data[i]);
    }
    
    stack->top = 0;
    return STACK_SUCCESS;
}

/**
 * @brief Destroy stack and free all memory
 * 
 * @param stack Pointer to stack structure
 * @return StackError_t Error code
 */
StackError_t Stack_Destroy(Stack_t* stack) {
    if (stack == NULL) {
        return STACK_ERROR_NULL;
    }

    // Clear all elements first
    Stack_Clear(stack);
    
    // Free the data array
    free(stack->data);
    stack->data = NULL;
    stack->capacity = 0;
    stack->elementSize = 0;

    return STACK_SUCCESS;
}

void TestStack(void) {
    Stack_t stack;
    StackError_t error;
    
    // Test initialization
    error = Stack_Init(&stack, 5, sizeof(int));
    assert(error == STACK_SUCCESS);
    assert(Stack_IsEmpty(&stack));
    
    // Test pushing elements
    int values[] = {10, 20, 30, 40, 50};
    for (int i = 0; i < 5; i++) {
        error = Stack_Push(&stack, &values[i]);
        assert(error == STACK_SUCCESS);
    }
    assert(Stack_IsFull(&stack));
    
    // Test peeking
    int peek_value;
    error = Stack_Peek(&stack, &peek_value);
    assert(error == STACK_SUCCESS);
    assert(peek_value == 50);
    
    // Test popping elements
    int pop_value;
    for (int i = 4; i >= 0; i--) {
        error = Stack_Pop(&stack, &pop_value);
        assert(error == STACK_SUCCESS);
        assert(pop_value == values[i]);
    }
    assert(Stack_IsEmpty(&stack));
    
    // Test error handling
    error = Stack_Pop(&stack, &pop_value);
    assert(error == STACK_ERROR_EMPTY);
    
    // Clean up
    error = Stack_Destroy(&stack);
    assert(error == STACK_SUCCESS);
    
    printf("All stack tests passed!\n");
}

int main(void) {
    TestStack();
    return 0;
}
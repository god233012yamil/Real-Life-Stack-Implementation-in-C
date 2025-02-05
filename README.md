# Stack Implementation in C

A robust, generic stack data structure implementation in C with comprehensive error handling, memory management, and thread-safety considerations. This implementation is designed for embedded systems and general-purpose applications where reliability and efficiency are crucial.

## Features

- 📦 Generic data type support (store any data type)
- 🛡️ Comprehensive error handling
- 💾 Efficient memory management
- 🧪 Built-in test suite
- 📚 Complete documentation
- 🔒 Thread-safety ready
- 💻 Embedded systems friendly

## Table of Contents

- [Installation](#installation)
- [Usage](#usage)
- [API Reference](#api-reference)
- [Testing](#testing)
- [Contributing](#contributing)
- [License](#license)

## Installation

### Prerequisites

- C compiler (GCC, Clang, or any C99 compatible compiler)
- CMake (version 3.10 or higher) for building
- Git for version control

### Building from Source

1. Clone the repository:
```bash
git clone https://github.com/god233012yamil/Real-Life-Stack-Implementation-in-C.git
cd Real-Life-Stack-Implementation-in-C
```

2. Create a build directory:
```bash
mkdir build
cd build
```

3. Build the project:
```bash
cmake ..
make
```
## Usage

### Basic Example

```c
#include <stdio.h>

int main() {
    // Initialize stack
    Stack_t stack;
    if (Stack_Init(&stack, 10, sizeof(int)) != STACK_SUCCESS) {
        printf("Failed to initialize stack\n");
        return 1;
    }

    // Push elements
    int value = 42;
    if (Stack_Push(&stack, &value) != STACK_SUCCESS) {
        printf("Failed to push value\n");
        return 1;
    }

    // Pop elements
    int retrieved;
    if (Stack_Pop(&stack, &retrieved) != STACK_SUCCESS) {
        printf("Failed to pop value\n");
        return 1;
    }
    printf("Popped value: %d\n", retrieved);

    // Clean up
    Stack_Destroy(&stack);
    return 0;
}
```

### Using with Custom Types

```c
typedef struct {
    int id;
    char name[50];
} Person_t;

int main() {
    Stack_t stack;
    Stack_Init(&stack, 5, sizeof(Person_t));

    Person_t person = {1, "John Doe"};
    Stack_Push(&stack, &person);

    Person_t retrieved;
    Stack_Pop(&stack, &retrieved);

    Stack_Destroy(&stack);
    return 0;
}
```

## API Reference

### Stack Structure

```c
typedef struct {
    void** data;          // Array of void pointers
    uint32_t capacity;    // Maximum capacity
    uint32_t top;         // Current top index
    size_t elementSize;   // Size of each element
} Stack_t;
```

### Functions

| Function | Description | Parameters | Return |
|----------|-------------|------------|--------|
| `Stack_Init` | Initialize stack | `Stack_t*, uint32_t capacity, size_t elementSize` | `StackError_t` |
| `Stack_Push` | Push element | `Stack_t*, const void* element` | `StackError_t` |
| `Stack_Pop` | Pop element | `Stack_t*, void* element` | `StackError_t` |
| `Stack_Peek` | View top element | `const Stack_t*, void* element` | `StackError_t` |
| `Stack_IsEmpty` | Check if empty | `const Stack_t*` | `bool` |
| `Stack_IsFull` | Check if full | `const Stack_t*` | `bool` |
| `Stack_Clear` | Remove all elements | `Stack_t*` | `StackError_t` |
| `Stack_Destroy` | Free stack memory | `Stack_t*` | `StackError_t` |

### Error Codes

```c
typedef enum {
    STACK_SUCCESS = 0,
    STACK_ERROR_FULL,
    STACK_ERROR_EMPTY,
    STACK_ERROR_NULL,
    STACK_ERROR_MEMORY,
    STACK_ERROR_SIZE
} StackError_t;
```

## Contributing

Contributions are welcome! Please feel free to submit a Pull Request.

### Guidelines

1. Fork the repository
2. Create your feature branch (`git checkout -b feature/AmazingFeature`)
3. Commit your changes (`git commit -m 'Add some AmazingFeature'`)
4. Push to the branch (`git push origin feature/AmazingFeature`)
5. Open a Pull Request

### Code Style

- Follow the existing code style
- Use meaningful variable and function names
- Add comments for complex logic
- Update documentation for new features
- Include test cases for new functionality

## License

This project is licensed under the GNU GENERAL PUBLIC License - see the [LICENSE](LICENSE) file for details.

## Authors

- Yamil Garcia (@god233012yamil)

## Acknowledgments

- Thanks to all contributors
- Inspired by classic data structure implementations
- Built with best practices from embedded systems development

---

For more information or support, please open an issue on GitHub.

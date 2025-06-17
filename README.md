# MINISHELL

A minimalist shell implemented in C, inspired by Unix shells like `bash` and `zsh`. This project is designed to provide a functional shell environment with essential features, suitable for learning about how shells operate internally and for testing command-line programs.

---

## Table of Contents

- [Overview](#overview)
- [Features](#features)
- [Installation](#installation)
- [Usage](#usage)
- [Built-in Commands](#built-in-commands)
- [Project Structure](#project-structure)
- [Technical Details](#technical-details)
- [Known Limitations](#known-limitations)
- [Contributing](#contributing)
- [License](#license)

---

## Overview

**MINISHELL** is a custom shell program written in C. The goal is to mimic the behavior of popular shells as closely as possible while keeping the codebase simple and educational. This project covers process management, input parsing, environment variable handling, and basic job control.

## Features

- **Prompt:** Displays a customizable prompt.
- **Command Parsing:** Supports single and multiple commands, including simple pipelines.
- **Built-in Commands:** Includes essential built-ins (see [Built-in Commands](#built-in-commands)).
- **Environment Variables:** Full support for setting, unsetting, and expanding environment variables.
- **Redirections:** Supports input `<`, output `>`, and append `>>` redirection.
- **Pipelines:** Allows chaining commands with `|`.
- **Error Handling:** Provides informative error messages for common mistakes.
- **Signal Handling:** Handles `Ctrl+C`, `Ctrl+D`, and other signals gracefully.
- **Exit Status:** Returns correct exit codes for commands and pipelines.

## Installation

### Prerequisites

- **C Compiler:** GCC or Clang
- **Make:** GNU Make

### Steps

1. **Clone the repository:**
    ```sh
    git clone https://github.com/alif-rash/MINISHELL.git
    cd MINISHELL
    ```

2. **Compile the project:**
    ```sh
    make
    ```

    This will produce the `minishell` executable in the project root.

## Usage

Start the shell by running:

```sh
./minishell
```

You will see a prompt. Enter commands as you would in a regular shell. Example commands:

```sh
ls -l
echo "Hello, world!"
export PATH=$PATH:/my/custom/path
cat file.txt | grep "pattern"
```

To exit, press `Ctrl+D` or type `exit`.

## Built-in Commands

MINISHELL includes the following built-in commands:

- `cd [directory]` — Change the current directory.
- `echo [args...]` — Print arguments to standard output.
- `env` — Display environment variables.
- `exit [status]` — Exit the shell with an optional status.
- `export VAR=VALUE` — Set an environment variable.
- `unset VAR` — Remove an environment variable.
- `pwd` — Print the current working directory.

> **Note:** These commands are handled internally and do not spawn new processes.

## Project Structure

```plaintext
MINISHELL/
├── src/            # Source files (.c)
├── include/        # Header files (.h)
├── Makefile        # Build script
├── README.md       # Project documentation
└── minishell       # Compiled binary (after build)
```

- **src/**: Contains the implementation of parsing, execution, built-ins, and utility functions.
- **include/**: Contains header files with function prototypes and struct definitions.
- **Makefile**: Defines build rules for compiling the shell.

## Technical Details

- **Parsing:** Uses a custom parser to tokenize and interpret user input, handling quotes, escapes, and environment variables.
- **Execution:** Forks and executes external programs using `execve()`. Built-ins are dispatched without forking.
- **Signals:** Uses signal handlers for interactive behavior (e.g., `SIGINT` and `SIGQUIT`).
- **Environment:** Manages shell environment as a linked list or array, supporting variable expansion with `$VAR`.

## Known Limitations

- No advanced features like job control (`fg`, `bg`), command history, or scripting support.
- Limited error messages for complex parsing errors.
- No support for subshells `()` or shell functions.
- Some edge cases in quoting or redirection may be unhandled.
- Not POSIX-complete; focuses on core functionality.

## Contributing

Contributions are welcome! Please open issues for bugs or feature requests. To contribute code:

1. Fork the repository.
2. Create a new branch: `git checkout -b feature/YourFeature`
3. Make your changes and add tests.
4. Push your changes and open a pull request.

## License

This project is licensed under the MIT License. See [LICENSE](LICENSE) for details.

---

**Enjoy exploring how shells work with MINISHELL!**

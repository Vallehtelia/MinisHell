# Minishell

Welcome to **Minishell**, a simple yet powerful recreation of a UNIX shell! This project, developed as part of the 42 School curriculum, aims to deepen our understanding of process management, signal handling, and implementing core UNIX shell functionalities.

## 🌟 Features
- **Basic Shell Commands**: Execute commonly used shell commands like `ls`, `echo`, and more.
- **Custom Builtins**:
  - `cd`: Change the working directory.
  - `pwd`: Display the current directory.
  - `env`: Display environment variables.
  - `export`: Set environment variables.
  - `unset`: Remove environment variables.
  - `exit`: Exit the shell gracefully.
- **Pipes (`|`)**: Chain commands together for efficient workflows.
- **Redirections (`>`, `<`, `>>`)**: Handle input and output like a pro.
- **Signal Handling**: Manage signals such as `Ctrl+C`, `Ctrl+D`, and `Ctrl+\` to ensure a smooth user experience.
- **Environment Variable Expansion**: Use `$` to access and expand environment variables.
- **Error Handling**: User-friendly error messages for invalid commands or incorrect usage.

## 🚀 Getting Started

### Prerequisites
- A UNIX-based system (Linux or macOS).
- `gcc` or any C compiler installed.

### Installation
1. Clone the repository:
   ```bash
   git clone https://github.com/yourusername/minishell.git
   cd minishell
2. Build the project:
   ```bash
   make
   ./minishell
### 🛠 Usage
Once you're in the Minishell environment, you can execute commands just like in a standard shell. Here are some examples:
  List files in the current directory
  ```bash
  ls -la
  ```
  
  Navigate to a directory
  ```bash
  cd /path/to/directory
  ```
  
  Display environment variables
  ```bash
  env
  ```
  
  Set a new environment variable
  ```bash
  export MY_VAR="Hello World"
  ```
  
  Use pipes to combine commands
  ```bash
  cat file.txt | grep "pattern"
  ```
  
  Redirect output to a file
  ```bash
  echo "Hello" > output.txt
  ```
### 📚 Learning Outcomes
This project reinforced our understanding of:
- Process creation and management with `fork()`, `execve()`, and `waitpid()`.
- Building a custom command parser.
- Signal handling for an interactive shell.
- The nuances of UNIX redirections and pipes.
- Effective debugging and error handling in C.

## 🖼 Project Structure
- **sources/**: Contains the source code for Minishell.
- **includes/**: Header files.
- **Makefile**: Build configuration.

## 🙌 Acknowledgments
- The 42 School for the incredible curriculum.

---

Happy Shelling! 🎉

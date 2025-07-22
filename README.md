
## Minishell (msh$)
![minishell](https://github.com/eschencode/minishell/blob/main/minishell%20.png)

Welcome to our Minishell project, developed as part of the curriculum at 42 Berlin. This project aims to build a simple shell (command interpreter) in C, mirroring the basic functionalities of bash. By implementing Minishell, we delved deep into the workings of a Unix shell, processes, file descriptors, and environment variables, enhancing our understanding of system calls and C programming.

### Features
-   **Command Execution:** Executes commands found in the PATH.
-   **Builtin Commands:** Includes `echo`, `cd`, `pwd`, `export`, `unset`, `env`, and `exit` as built-in functions.
-   **Redirections and Pipes:** Handles input/output redirections (`<`, `>`, `>>`) and pipes (`|`).
-   **Environment Variables:** Supports setting and expanding environment variables (`$VAR_NAME`).
-   **Error Handling:** Provides meaningful error messages, mirroring those from bash.
-   **Signal Handling:** Manages signals like `CTRL-C` to interrupt commands, `CTRL-D` to exit the shell, and `CTRL-\` to ignore.



## Installation and Usage
Clone the repository and build the Minishell executable:
```bash
git clone https://github.com/eschencode/minishell.git
cd Minishell
make
``` 
To run Minishell, execute:
```bash
./minishell
```

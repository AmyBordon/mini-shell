# Mini Shell

A Unix-like shell written in C.

## Features

- Execute commands
- Built-in commands
- Pipes
- Redirection
- Background jobs

## Build

## What I learned
- Process creation with fork(): A child process is created as a copy of the parent process. After the fork, both processes execute independently.

- Program execution with execvp(): The child process replaces its program image with a new executable while keeping the same process ID.

- Process synchronization with waitpid(): The parent shell waits for foreground commands to finish before displaying a new prompt.

- Command parsing: User input must be tokenized into arguments before it can be executed.

- Built-in commands: If a command needs to modify the shell process itself, it must be implemented as a built-in. For example, cd changes the shell's current working directory using chdir(). If cd were executed in a child process created by fork(), only the child would change directories, and the parent shell would remain in the original location.

- Error handling: A child process must terminate if execvp() fails. Otherwise, it continues executing the shell code, unintentionally creating another shell instance.
```bash
make

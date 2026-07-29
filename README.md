# Mini Shell

A Unix-like shell written in C as a learning project to explore Unix process management, file descriptors, pipes, and command parsing.

## Features

- Execute commands
- Built-in commands
- Pipes
- Redirection

## Current limitations

- Environment variable expansion is not implemented.
- Job control (&, fg, bg) is not implemented.
- No command history available.

## What I learned

- Process creation with fork(): A child process is created as a copy of the parent process. After the fork, both processes execute independently.

- Program execution with execvp(): The child process replaces its program image with a new executable while keeping the same process ID.

- Process synchronization with waitpid(): The parent shell waits for foreground commands to finish before displaying a new prompt.

- Command parsing: User input must be tokenized into arguments before it can be executed.

- Built-in commands: If a command needs to modify the shell process itself, it must be implemented as a built-in. For example, cd changes the shell's current working directory using chdir(). If cd were executed in a child process created by fork(), only the child would change directories, and the parent shell would remain in the original location.

- Error handling: A child process must terminate if execvp() fails. Otherwise, it continues executing the shell code, unintentionally creating another shell instance.

- strtok() uses global internal state: Consecutive calls to strtok() share the same parsing state, which makes nested tokenization impossible. This became important when parsing both pipelines (|) and command arguments. Replacing it with a custom tokenizer removed this limitation and made the parser easier to extend.

- Pipes and redirection interact in subtle ways: Implementing pipelines required understanding how pipe(), dup2(), and file redirection work together. Comparing the shell's behavior with Bash using strace also showed that shell behavior in edge cases can be more subtle than expected, and that tracing system calls is an invaluable debugging technique for systems programming.

## Notes

This project was implemented as a learning exercise. I used AI as a mentor to discuss Unix concepts, debug issues, and review design decisions. All code was written, tested, and modified by me while ensuring I understood the underlying concepts before integrating any suggested changes.

##Build
```bash
make
./myshell
```

# Minishell

`Minishell` is a simple shell implementation in C, designed to mimic the functionality of a basic Unix shell. It allows the user to execute commands, handle pipes, redirections, and process signals, among other basic shell features.

This project aims to understand how a shell works, manage processes, interact with the system using system calls, and implement basic command parsing and execution.

## Features

- **Command Execution**: Executes commands entered by the user, either with or without pipes.
- **Pipes**: Supports piping between multiple commands (e.g., `command1 | command2`).
- **Signal Handling**: Proper handling of `SIGQUIT` and other signals to control child processes.
- **History**: Stores previously executed commands for easy reuse.
- **Memory Management**: Handles dynamic memory allocation for arguments, paths, and process IDs, ensuring no memory leaks.

# mini-shell

A minimal interactive Unix shell written in C. Supports pipelines, I/O redirection, background jobs, and signal handling.

## Features

- **REPL loop** with command history
- **Pipes**: multi-stage pipelines (`ls -l | grep foo | wc -l`)
- **Redirection**: `<` (input), `>` (output overwrite), `>>` (output append)
- **Background execution**: `sleep 10 &`
- **Signal handling**: Ctrl+C kills foreground process without killing the shell, SIGCHLD reaps background zombies
- **Built-in commands**: `cd`, `pwd`, `exit`, `export`, `history`

## Build

```bash
make
```

## Run

```bash
./mini-shell
```

## Architecture

```
user input
  │
  ▼
readline.c    read a line, strip newline, store in history
  │
  ▼
parser.c      tokenize by whitespace, recognize | > < >> &,
  │            fill struct command[]
  ▼
main.c        dispatch to builtin or executor
  │
  ├── builtin.c    cd / pwd / exit / export / history
  └── executor.c   fork + execvp + pipe + dup2 + redirect
```

## Tech Stack

`fork` `execvp` `pipe` `dup2` `waitpid` `sigaction` `open` `close` `chdir` `getcwd` `setenv` `strtok`

## File Overview

| File | Purpose |
|------|---------|
| `main.c` | REPL loop, signal registration, dispatch |
| `readline.c` | line input, history storage |
| `parser.c` | tokenizer, struct command builder |
| `builtin.c` | built-in command execution |
| `executor.c` | process creation, pipe/redirect wiring |

~420 lines of C across 5 source files and 5 headers.

## License

MIT

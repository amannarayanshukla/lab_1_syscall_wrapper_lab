# C Wrapper Lab - Development Container

This repository is a hands-on lab to create a C wrapper and practice low-level development, linking, and debugging inside a Linux/amd64 container.

## Goals
- Implement a simple C wrapper around a library or API to understand calling conventions, headers, and linking.
- Build and debug inside a consistent container environment (`Dockerfile` provided).
- Practice building shared libraries, static binaries, and using `gdb`.

## Prerequisites
- Docker installed on macOS.
- Source files placed in the repo root (container `WORKDIR` is `/my_lab`).
- Files edited on the host and mounted into the container for iterative development.

## Build inside the container
1. Build the Docker image:

    docker build -t syscall-wrapper-lab .

2. Run an interactive container with the repo mounted:

    docker run --rm -it -v $(pwd):/my_lab syscall-wrapper-lab


## Run and test
     gcc main.c wrappers.s -o lab
     ./lab 

## Debugging with `gdb` (inside the container)
- Start `gdb` on the binary:

    gdb ./bin/wrapper

- Useful `gdb` commands: `run`, `break`, `next`, `step`, `continue`, `backtrace`, `print`.

## Notes about the `Dockerfile`
- The `Dockerfile` uses `FROM --platform=linux/amd64 ubuntu:latest` and installs `build-essential` and `gdb`.
- Mount the repo root into the container to edit on the host and build/debug inside the container.

## Contributing
- Open issues or PRs for fixes and improvements.

## License
- Add a license file as needed (e.g., `LICENSE`).

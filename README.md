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

    docker build -t my_lab_image .

2. Run an interactive container with the repo mounted:

    docker run --rm -it -v $(pwd):/my_lab --platform=linux/amd64 my_lab_image bash

3. Inside the container, example compile commands:

- Build a simple wrapper executable:

    mkdir -p bin
    gcc -Wall -Wextra -g -O0 -Iinclude -o bin/wrapper src/wrapper.c src/main.c

- Build a shared library (example):

    mkdir -p lib
    gcc -shared -fPIC -Iinclude -o lib/libexample.so src/lib.c

Notes:
- Use `-g -O0` for easier debugging.
- Add `-fPIC` and `-shared` to create shared libraries.

## Run and test
- Run the built executable inside the container:

    ./bin/wrapper

- When using shared libraries, set `LD_LIBRARY_PATH` or install to standard paths:

    LD_LIBRARY_PATH=./lib ./bin/wrapper

## Debugging with `gdb` (inside the container)
- Start `gdb` on the binary:

    gdb ./bin/wrapper

- Useful `gdb` commands: `run`, `break`, `next`, `step`, `continue`, `backtrace`, `print`.

## Suggested exercises
- Implement `wrapper.c` that forwards calls to `lib.c` and validates parameters.
- Create `wrapper.h` and practice proper header guards and API design.
- Build both static and shared versions of `lib.c` and observe linking differences.
- Introduce intentional bugs and debug with `gdb`.
- (Optional) Install `valgrind` in the `Dockerfile` to practice memory debugging.

## Notes about the `Dockerfile`
- The `Dockerfile` uses `FROM --platform=linux/amd64 ubuntu:latest` and installs `build-essential` and `gdb`.
- Mount the repo root into the container to edit on the host and build/debug inside the container.

## Contributing
- Open issues or PRs for fixes and improvements.

## License
- Add a license file as needed (e.g., `LICENSE`).

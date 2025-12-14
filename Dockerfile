# we tell docker to download a linux x86 system for me
FROM --platform=linux/amd64 ubuntu:latest

# install C compliler and debugger
RUN apt-get update && apt-get install -y build-essential gdb

# make a folder inside this to hold my code
# we still to need to create a tunnel to tell it about projecting my machine code to this folder
WORKDIR /my_lab


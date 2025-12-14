#global is used for exporting the function
.global my_write #we are exposing it to other files
.global my_exit
.global my_read
.global my_open
.global my_close

#we have defined a my_write function and mentioned the signature C and kernel has agreed on
# int fd =>  RDI, const char *buf =>  RSI, size_t count =>  RDX
#my_write(int fd, const char *buf, size_t count)
my_write:
    #RDI is set to 1, i.e. via FD which tell the to have output on a screen or terminal
    mov $1, %rax # this tells the kernel that we are in WRITE mode

    # after running this the Kernel return the control to this file
    # since the next instruction is save in a register called RAX
    syscall # this gives control to the kernel, kernel will read the RDI, RSI, and RDX

    # this gives the control back to the C code, however this uses STACK and not Registers
    ret # after the control from the wrapper back to the C code

# unsigned int fd =>  RDI, char *buf =>  RSI, size_t count =>  RDX
#my_read(unsigned int fd, char *buf, size_t count)
my_read:
    mov $0, %rax # this tells the kernel that we are in READ mode
    syscall
    ret

# const char *filename => RDI, int flags => RSI, umode_t mode => RDX
#my_open(const char *filename, int flags, umode_t mode)
my_open:
    mov $2, %rax
    syscall
    ret


# unsigned int fd => RDI
#my_close(unsigned int fd)
my_close:
    mov $3, %rax
    syscall
    ret

#my_exit(int error_code)
my_exit:
    mov $60, %rax
    syscall
    ret

.section .note.GNU-stack,"",@progbits

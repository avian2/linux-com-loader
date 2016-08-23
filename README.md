# Linux COM loader

This is a (very) simple loader for Linux that loads and executes a binary file
in much the same way CP/M and DOS loaded .COM executables.

0x10000 bytes are allocated, starting at 0x0000. Binary files, up to 0xff00
bytes in length, are loaded starting at 0x100. Stack top is set to 0x10000 and
loader jumps to instruction at 0x100.

What would be the program segment prefix (0x0000 - 0x0100) is left unused.

**You can't run DOS .COM executables with this. Code is executed as a
normal Linux process using the current architecture. No attempt is made to
simulate x86 real mode or DOS services.**

## Usage

Disable the security feature that prevents us from mmaping the zero page (as
root):

    # sysctl vm.mmap_min_addr=0

Run `make` to build the loader, build a "Hello World" .COM binary and execute
it:

    $ make
    Hello, World!

To make kernel aware of the loader (as root):

    # update-binfmts --install com /path/to/loader --extension com

Now you can run .COM binaries directly!

    $ ./hello.com
    Hello, world!

## License

               DO WHAT THE FUCK YOU WANT TO PUBLIC LICENSE
                       Version 2, December 2004

    Copyright (C) 2004 Sam Hocevar <sam@hocevar.net>

    Everyone is permitted to copy and distribute verbatim or modified
    copies of this license document, and changing it is allowed as long
    as the name is changed.

               DO WHAT THE FUCK YOU WANT TO PUBLIC LICENSE
      TERMS AND CONDITIONS FOR COPYING, DISTRIBUTION AND MODIFICATION

     0. You just DO WHAT THE FUCK YOU WANT TO.

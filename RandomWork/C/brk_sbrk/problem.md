# C program to manage memory using brk/sbrk system calls.
In this program, brk and sbrk functions are used instead of malloc and free to manage memory. Also, the allocated memory is sum of header and an empty, usable, space of **size** bytes which is given as per required at run time.

The header is a structure which comprises of the following:

size: integer - size of the extre, empty, allocated space
isFree: boolean - defines if the structure is free or not ( empty memory being used somewhere or not )
left: structure pointer - defines the left side of the binary tree
right: structure pointer - defines the right side of the binary tree


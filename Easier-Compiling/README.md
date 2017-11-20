# Compile C/C++ code using a single program/command.

Compile C/C++ code using a command:

Assuming the executable name of the compiled code is generator,

	Prompt> generator <flags...> <source file>

	Example:

		Prompt> generator -pthread -lm test.c


Note that number of flags is not set.

Also, the program will generate the executable (-o <file>) automatically
as per the name of first source file (source file minus the extension).

Requisites:

C11 is used to compile this code.

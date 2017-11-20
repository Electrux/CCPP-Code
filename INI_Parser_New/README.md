# Electrux-Codes

This is an INI parser which is capable of fetching, modifying and saving INI style files.
It supports Sections using Square Brackets ( [] ).

I had originally written an INI Parser in C but scrapped it in favor of this C++ Parser.
Not to mention, the C INI Parser didn't have any Section capabilities.


To use the INI Parser, only the header "INI_Parser.hpp" is required to be included. It includes the other headers by itself in order.

A sample code is written as Main.cpp.

As far as working goes, you can parse the INI data from a file and then modify/add on it. Or you can put your own data as well.

Finally, to save the data, pass it through the SaveFile function.
Also, you can use the DisplayAll function to show all the content present in the INI object. (Parsed from file or self generated.)

The INI_Parser is in "Electrux" namespace.
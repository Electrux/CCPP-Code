# eXtreme Integers v0.1

This is the extreme integer library to evaluate huge integers (as long as memory permits).

Factorial is made for example. (You NEED C++11 compatible compiler to compile the code).

It uses unsigned char arry to implement that. (Integer would take 4 bytes and I am storing just one digit per element.)

You can currently:

    1. Put a value into the object (of type "xint") using std::string or std::vector array using "=" (assignment) operator.

            If any value entered is non integer, assignment will return false.

    2. function - int addnum(int a, int b, int &carry) :-

            Add 2 numbers (made for single digit) to give a digit as answer, and it will also take third parameter to store the carry over ().

    3. function - int getqnr(int a, int &quo) :-

            Get quotient and remainder of a number "a", divided by 10.

    4. Operator "*=" :-

            Multiplying the xint object with an unsigned long long number, or a vector array (overloaded operator).

    5. Operator "*" :-

            Multiplying xint object with another xint object. Returns xint object, so it can be used to write complete multiplicative expressions and assigned to another xint object.

    6. Operator "+" :-

            Adding xint object with another xint object. Returns xint object, so it can be used to write complete additive expressions and assigned to another xint object.

    7. Operators "++" and "--" :-
            Incrementing and decrementing xint objects respectively. Returns true or false depending on if a positive number or zero was present in the object (in decrementing).

    8. Function - std::vector<unsigned char> getVector() :-

            Gets the digit vector of the object.

    9. Function - std::vector<unsigned char> getNumVector(<Types list below>) :-

            Fetches all individual digits int the form of a vector array from <type>.

            Type list :-

                std::string

                unsigned int

                unsigned long

                unsigned long long

    10. Function - unsigned long getVecSize() :-

            Fetches the number of digits in xint's internal vector array of digits.

    11. Function - friend std::ostream & operator <<(std::ostream &os, const xint &xi) :-

            Used to overload the << operator in outputstream systems (cout, fstreams, etc).

    12. Function - bool isNum(std::string &str) :-

            Used to check if the string contains all numeric digits. True - if the string is all digits, false - if not.

    13. Function - getInteger(char c) :-

            Convert the character to integer using _atoi() function.

Notes:

    1. Previous points 2, 3, 9, 10, 12, and 13 are used for internal computations. NOT intended for explicit usage.

    2. This library is not made for heavy usage. It is EXTREMELY slow compared to inbuilt (primitive) datatypes (int, long, etc.).

    3. Additions/modifications are welcome but please do tell what has been changed/added.

Changelog:

    28-04-15

        Uploaded first version.

        Changed some crucial code to increase performance by approximately 20%. (Data duplication).

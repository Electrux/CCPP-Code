# Electrux-Codes

This is a C++ code to convert a string of binary characters to Hamming code (Error detecting and correcting).
	Defines a struct required to use this library and a class with all static members. Just two of them are needed for using this library though.
	
	Struct:
	
		StringWithParityCount:
	
			This structure defines an integer and a string object in it. Use this to get the encoded (hamming code) string from the Encode Function.
			The "arr" object is used by the user. "pbits" is used for internal calculations.
	
	Functions:
		
		static StringWithParityCount encode(std::string &arr);
		
			This function returns the struct object which contains encoded string (Hamming code) from the given "arr" argument.
			
			
		static std::string decode(StringWithParityCount paritystr);
			
			This function takes the struct object as argument and returns a decoded (normal binary) string which was the original string.
			Basically, the counter of encode.
			
	
	
	NOTE:-
		Both these functions are static, just like all the internal functions of the class. Hence, no need to make an object of the class.
		It will work by directly calling functions from class, without the need of any object.
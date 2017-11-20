# All custom classes and functions for C/C++

Currently contains:

	C++
	
		Number manipulation functions for C++ (CPP/Numbers/Display.hpp)
		
			
			std::string dispnumwithcomma(int num);
			
				Returns a comma separated string of the given number.
		
		

		Delimiter functions for C++ (CPP/Strings/delims.hpp)
	
	
			std::vector<std::string> delimitfromargv(int argc, char **argv);
	
				For use with the command line args.
		

			std::vector<std::string> delimiter(std::string str, char delim);
		
				To cleave a string using a character as delimiter.
		
			
			void getnameextfromfile(std::string file, std::string &name, std::string &ext);
			
				To bifurcate file into its name and extension.
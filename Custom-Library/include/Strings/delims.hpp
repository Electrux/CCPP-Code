#if !defined(_DELIMS_HPP) && defined(_GLIBCXX_VECTOR)

#define _DELIMS_HPP


std::vector<std::string> delimitfromargv(int argc, char **argv);
std::vector<std::string> delimiter(std::string str, char delim);
void getnameextfromfile(std::string file, std::string &name, std::string &ext);

std::vector<std::string> delimitfromargv(int argc, char **argv)
{
	std::vector<std::string> delimstr;
	delimstr.clear();
	
	if(argc < 1) return delimstr;
	
	for(int i = 0; i < argc; ++i)
	{
		delimstr.push_back(argv[i]);
	}
	return delimstr;
}

std::vector<std::string> delimiter(std::string str, char delim)
{
	std::vector<std::string> delimstr;
	delimstr.clear();
	
	if(str.empty()) return delimstr;

	std::string temp;
	temp.clear();

	for(auto it = str.begin(); it != str.end(); ++it)
	{
		if( *it == delim || it == str.end() - 1 )
		{
			delimstr.push_back(temp);
			temp.clear();
		}
		else
		{
			temp += *it;
		}
	}
	return delimstr;
}

void getnameextfromfile(std::string file, std::string &name, std::string &ext)
{
	std::string::iterator pos;

	name.clear();
	ext.clear();

	for(auto it = file.begin(); it != file.end(); ++it)
	{
		if( *it == '.' && it != file.end() - 1)
		{
			pos = it;
		}
	}

	for(auto it = file.begin(); it != pos; ++it)
	{
		name += *it;
	}

	for(pos = pos + 1; pos != file.end(); ++pos) //Increment first so that it dont count period.
	{
		ext += *pos;
	}
}

#endif
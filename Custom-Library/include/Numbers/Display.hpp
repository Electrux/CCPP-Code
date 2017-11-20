std::string dispnumwithcomma(int num)
{
	std::string str = std::to_string(num);
	int digits = str.length();
	int pos;
	
	pos = digits % 3;
	
	while( digits > 3 )
	{
		str.insert(pos, std::string(","));
		pos += 3 + 1;
		digits -= 3;
	}
	
	return str;
}